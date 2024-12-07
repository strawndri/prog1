#include <stdio.h>
#include <stdlib.h>

#include "fprio.h"
#include "lista.h"
#include "utils.h"
#include "eventos.h"
#include "mundo.h"

// Função de criação dos eventos
struct evento_t *cria_evento(int tempo, int tipo, int d1, int d2)
{
  struct evento_t *evento;

  // Aloca o evento e verifica se ele é válido
  evento = malloc(sizeof(struct evento_t));
  if (!evento)
    return NULL;

  evento->tempo = tempo;
  evento->tipo = tipo;
  evento->d1 = d1;
  evento->d2 = d2;

  return evento;
}

// Chega: herói H chegando na base B no instante T
void trata_ev_chega(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef)
{
  // Dados do evento atual
  struct heroi_t *h = &m->herois[ev->d1];
  struct base_t *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int espera;
  int tipo_evento;
  char *msg;

  int status;

  // Se herói está morto, sai da função
  if (h->morto)
    return;

  h->id_base = b->id_base;

  if (cjto_card(b->presentes) < b->lotacao && lista_tamanho(b->espera) == 0)
    espera = 1;
  else
    espera = (h->paciencia) > (10 * lista_tamanho(b->espera));

  tipo_evento = espera ? ESPERA : DESISTE;
  msg = espera ? "ESPERA" : "DESISTE";

  struct evento_t *evento = cria_evento(
      t,
      tipo_evento,
      h->id_heroi,
      b->id_base);

  printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) %s\n",
         evento->tempo,
         evento->d1,
         evento->d2,
         cjto_card(b->presentes),
         b->lotacao,
         msg);

  // Insere evento na LEF e verifica se deu certo
  status = fprio_insere(lef, evento, tipo_evento, evento->tempo);
  if (status < 0)
    return;
}

// Espera: herói H entra na fila de espera da base B
void trata_ev_espera(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef)
{
  // Dados do evento atual
  struct heroi_t *h = &m->herois[ev->d1];
  struct base_t *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int status;

  struct evento_t *evento = cria_evento(
      t,
      AVISA,
      h->id_heroi,
      b->id_base);

  printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
         evento->tempo,
         evento->d1,
         evento->d2,
         lista_tamanho(b->espera));

  lista_insere(b->espera, h->id_heroi, -1);

  // Atualiza a quantidade máxima de pessoas na fila de espera
  if (lista_tamanho(b->espera) >= b->espera_max)
    b->espera_max = lista_tamanho(b->espera);

  // Insere evento na LEF e verifica se deu certo
  status = fprio_insere(lef, evento, AVISA, evento->tempo);
  if (status < 0)
    return;
}

// Desiste: herói H desiste de entrar na base B
void trata_ev_desiste(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef)
{
  // Dados do evento atual
  struct heroi_t *h = &m->herois[ev->d1];
  struct base_t *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int destino = aleat(0, m->n_bases - 1);

  int status;

  struct evento_t *evento = cria_evento(
      t,
      VIAJA,
      h->id_heroi,
      destino);

  printf("%6d: DESIST HEROI %2d BASE %d\n",
         t,
         evento->d1,
         b->id_base);

  // Insere evento na LEF e verifica se deu certo
  status = fprio_insere(lef, evento, VIAJA, evento->tempo);
  if (status < 0)
    return;
}

// Avisa: porteiro trata da base B
void trata_ev_avisa(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef)
{
  // Dados do evento atual
  struct base_t *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int status;

  printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ",
         t,
         b->id_base,
         cjto_card(b->presentes),
         b->lotacao);
  lista_imprime(b->espera);
  printf(" ]\n");

  // Enquanto for possível admitir heróis dentro da base, retira-os da fila
  // de espera e os insere na base
  while (cjto_card(b->presentes) < b->lotacao && lista_tamanho(b->espera) > 0)
  {
    int heroi;

    // Consulta evento da lista e verifica se deu certo
    status = lista_consulta(b->espera, &heroi, 0);
    if (status < 0)
      return;

    // Retira evento da lista e verifica se deu certo
    status = lista_retira(b->espera, &heroi, 0);
    if (status < 0)
      return;

    // Insere evento no conjunto e verifica se deu certo
    status = cjto_insere(b->presentes, heroi);
    if (status < 0)
      return;

    struct evento_t *evento = cria_evento(
        t,
        ENTRA,
        heroi,
        b->id_base);

    // Insere evento na LEF e verifica se deu certo
    status = fprio_insere(lef, evento, ENTRA, evento->tempo);
    if (status < 0)
      return;

    printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n",
           evento->tempo,
           evento->d2,
           evento->d1);
  }
}

// Entra: herói H entra na base B
void trata_ev_entra(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef)
{
  // Dados do evento atual
  struct heroi_t *h = &m->herois[ev->d1];
  struct base_t *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int status;

  // Tempo de permanência na base
  int tpb = 15 + (h->paciencia * aleat(1, 20));

  struct evento_t *evento = cria_evento(
      t + tpb,
      SAI,
      h->id_heroi,
      b->id_base);

  // Insere evento na LEF e verifica se deu certo
  status = fprio_insere(lef, evento, SAI, evento->tempo);
  if (status < 0)
    return;

  printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
         t,
         h->id_heroi,
         b->id_base,
         cjto_card(b->presentes),
         b->lotacao,
         t + tpb);
}

// Sai: herói H sai da base B
void trata_ev_sai(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef)
{
  // Dados do evento atual
  struct heroi_t *h = &m->herois[ev->d1];
  struct base_t *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int destino;
  int status;

  // Se herói está morto, sai da função
  if (h->morto)
    return;

  // Retira evento do conjunto e verifica se deu certo
  status = cjto_retira(b->presentes, h->id_heroi);
  if (status < 0)
    return;

  destino = aleat(0, m->n_bases - 1);

  struct evento_t *ev_viaja = cria_evento(
      t,
      VIAJA,
      h->id_heroi,
      destino);

  // Insere evento na LEF e verifica se deu certo
  status = fprio_insere(lef, ev_viaja, VIAJA, ev_viaja->tempo);
  if (status < 0)
    return;

  struct evento_t *ev_avisa = cria_evento(
      t,
      AVISA,
      h->id_heroi,
      b->id_base);

  // Insere evento na LEF e verifica se deu certo
  status = fprio_insere(lef, ev_avisa, AVISA, ev_avisa->tempo);
  if (status < 0)
    return;
  
  printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
         t,
         h->id_heroi,
         b->id_base,
         cjto_card(b->presentes),
         b->lotacao);
}

// Viaja: herói B se desloca para uma base D
void trata_ev_viaja(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef)
{
  // Dados do evento atual
  struct heroi_t *h = &m->herois[ev->d1];
  struct base_t *d = &m->bases[ev->d2];
  int t = ev->tempo;

  int status;

  // Se herói está morto, sai da função
  if (h->morto)
    return;

  struct base_t b = m->bases[h->id_base];
  int dist = calcula_distancia(b.local, d->local);
  int duracao = dist / h->velocidade;

  struct evento_t *evento = cria_evento(
      t + duracao,
      CHEGA,
      h->id_heroi,
      d->id_base);

  // Insere evento na LEF e verifica se deu certo
  status = fprio_insere(lef, evento, CHEGA, evento->tempo);
  if (status < 0)
    return;

  printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
         t,
         evento->d1,
         b.id_base,
         evento->d2,
         dist,
         h->velocidade,
         evento->tempo);
}

// Morre: herói H morre no instante T
void trata_ev_morre(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef)
{
  // Dados do evento atual
  struct heroi_t *h = &m->herois[ev->d1];
  struct base_t *b = &m->bases[m->herois[ev->d1].id_base];
  struct missao_t *mi = &m->missoes[ev->d2];
  int t = ev->tempo;

  int status;

  if (!b->presentes)
    return;

  printf("%6d: MORRE  HEROI %2d MISSAO %d\n",
         t,
         h->id_heroi,
         mi->id_missao);

  // Retira herói do conjunto e verifica se deu certo
  status = cjto_retira(b->presentes, h->id_heroi);
  if (!status)
    return;

  h->morto = true;

  struct evento_t *evento = cria_evento(
      t,
      AVISA,
      h->id_heroi,
      b->id_base);

  // Insere evento na LEF e verifica se deu certo
  status = fprio_insere(lef, evento, AVISA, evento->tempo);
  if (status < 0)
    return;
}

// Missão: missão M é disparada no instante T
void trata_ev_missao(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef)
{
  // Dados do evento atual
  struct missao_t *mi = &m->missoes[ev->d1];
  int t = ev->tempo;

  int n = m->n_bases;
  int dist;
  int bmp;
  int risco;
  struct heroi_t *h;

  int tipo;
  int prio;

  int status;

  struct fprio_t *dists_bases = fprio_cria();

  mi->tentativas++;

  printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", t, mi->id_missao, mi->tentativas);
  cjto_imprime(mi->habilidades);
  printf(" ]\n");

  for (int i = 0; i < n; i++)
  {
    dist = calcula_distancia(m->bases[i].local, mi->local);

    // Insere evento na fila e verifica se deu certo
    status = fprio_insere(dists_bases, &m->bases[i], m->bases[i].id_base, dist);
    if (status < 0)
      return;
  }

  bmp = encontra_prox_base(m, mi, dists_bases);

  if (bmp >= 0)
  {
    mi->cumprida = true;
    struct base_t *b = &m->bases[bmp];

    b->missoes++;

    for (int i = 0; i < m->n_herois; i++)
    {
      // Se o herói h está na bmp, analisa o risco de realizar a função
      if (cjto_pertence(m->bases[bmp].presentes, i))
      {
        h = &m->herois[i];
        risco = mi->perigo / (h->paciencia + h->experiencia + 1.0);

        if (risco > aleat(0, 30))
        {
          struct evento_t *evento = cria_evento(
              t,
              MORRE,
              h->id_heroi,
              mi->id_missao);

          // Insere evento na fila e verifica se deu certo
          status = fprio_insere(lef, evento, MORRE, evento->tempo);
          if (status < 0)
            return;
        }
        else
        {
          h->experiencia++;
        }
      }
    }

    printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ",
           t,
           mi->id_missao,
           m->bases[bmp].id_base);
    cjto_imprime(mi->habilidades);
    printf(" ]\n");
  }
  else
  {
    struct evento_t *evento = cria_evento(
        t + 24 * 60,
        MISSAO,
        mi->id_missao,
        -1);
    
    // Insere evento na LEF e verifica se deu certo
    status = fprio_insere(lef, evento, MISSAO, evento->tempo);
    if (status < 0)
      return;

    printf("%6d: MISSAO %d IMPOSSIVEL\n", t, mi->id_missao);
  }

  // Removendo as bases ainda presentes na fila de prioridade
  while (fprio_tamanho(dists_bases) > 0)
    fprio_retira(dists_bases, &tipo, &prio);

  fprio_destroi(dists_bases);
}

// Fim: encerramento da simulação
void trata_ev_fim(struct mundo_t *m, struct evento_t *ev)
{
  struct heroi_t heroi;
  struct base_t base;
  int t = ev->tempo;

  int missoes_cumpridas = 0;
  int total_mortos = 0;
  int soma_tentativas = 0;
  int max_tentativas = m->missoes[0].tentativas;
  int min_tentativas = m->missoes[0].tentativas;
  char *msg;

  printf("%6d: FIM\n\n", t);

  // Estatísticas dos heróis
  for (int h = 0; h < m->n_herois; h++)
  {
    heroi = m->herois[h];
    msg = heroi.morto ? "MORTO" : "VIVO";

    printf("HEROI %2d %5s PAC %3d VEL %4d EXP %4d HABS [ ",
           heroi.id_heroi,
           msg,
           heroi.paciencia,
           heroi.velocidade,
           heroi.experiencia);

    if (heroi.morto)
      total_mortos++;

    cjto_imprime(heroi.habilidades);
    printf(" ]\n");
  }

  // Estatísticas das bases
  for (int b = 0; b < m->n_bases; b++)
  {
    base = m->bases[b];
    printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",
           base.id_base,
           base.lotacao,
           base.espera_max,
           base.missoes);
  }

  printf("EVENTOS TRATADOS: %d\n", m->total_eventos);

  for (int mi = 0; mi < m->n_missoes; mi++)
  {
    if (m->missoes[mi].cumprida)
      missoes_cumpridas++;

    soma_tentativas += m->missoes[mi].tentativas;

    if (m->missoes[mi].tentativas > max_tentativas)
      max_tentativas = m->missoes[mi].tentativas;

    if (m->missoes[mi].tentativas < min_tentativas)
      min_tentativas = m->missoes[mi].tentativas;
  }

  if (m->n_missoes > 0)
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n",
           missoes_cumpridas,
           m->n_missoes,
           (float)(missoes_cumpridas * 100) / m->n_missoes);
  else
    printf("MISSOES CUMPRIDAS: 0/%d (0.0%%)\n", m->n_missoes);

  printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n",
         min_tentativas,
         max_tentativas,
         soma_tentativas / (float)m->n_missoes);
  printf("TAXA MORTALIDADE: %.1f%%\n", 100 * (total_mortos) / (float)m->n_herois);
}
