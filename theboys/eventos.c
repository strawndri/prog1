#include <stdio.h>
#include <stdlib.h>

#include "fprio.h"
#include "lista.h"
#include "utils.h"
#include "eventos.h"
#include "mundo.h"

struct evento_t *cria_evento(int tempo, int tipo, int d1, int d2)
{
  struct evento_t *evento;

  evento = malloc(sizeof(struct evento_t));

  if (!evento)
    return NULL;

  evento->tempo = tempo;
  evento->tipo = tipo;
  evento->d1 = d1;
  evento->d2 = d2;

  return evento;
}

// Funções dos eventos ---------------------------------------------------------

// Chega: heroi H chegando na ba B no instante T
void chega(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct heroi *h = &m->herois[ev->d1];
  struct base *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int espera;
  int tipo_evento;
  char *msg;

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

  int status_fprio = fprio_insere(lef, evento, tipo_evento, evento->tempo);

  if (status_fprio < 0)
    return;
}

// Espera
void espera(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct heroi *h = &m->herois[ev->d1];
  struct base *b = &m->bases[ev->d2];
  int t = ev->tempo;

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

  // atualiza a quantidade máxima de pessoas na fila de espera
  if (lista_tamanho(b->espera) >= b->espera_max)
    b->espera_max = lista_tamanho(b->espera);

  int status_fprio = fprio_insere(lef, evento, AVISA, evento->tempo);

  if (status_fprio < 0)
    return;
}

// Desiste
void desiste(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct heroi *h = &m->herois[ev->d1];
  struct base *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int destino = aleat(0, m->n_bases - 1);

  struct evento_t *evento = cria_evento(
      t,
      VIAJA,
      h->id_heroi,
      destino);

  printf("%6d: DESIST HEROI %2d BASE %d\n",
         t,
         evento->d1,
         b->id_base);

  int status_fprio = fprio_insere(lef, evento, VIAJA, evento->tempo);

  if (status_fprio < 0)
    return;
}

// Avisa
void avisa(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct base *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int status_consulta;
  int status_retira;
  int status_insere;

  printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ",
         t,
         b->id_base,
         cjto_card(b->presentes),
         b->lotacao);
  lista_imprime(b->espera);
  printf(" ]\n");

  while (cjto_card(b->presentes) < b->lotacao && lista_tamanho(b->espera) > 0)
  {
    int heroi;

    status_consulta = lista_consulta(b->espera, &heroi, 0);
    if (status_consulta < 0)
      return;

    status_retira = lista_retira(b->espera, &heroi, 0);
    if (status_retira < 0)
      return;

    status_insere = cjto_insere(b->presentes, heroi);
    if (status_insere < 0)
      return;

    struct evento_t *evento = cria_evento(
        t,
        ENTRA,
        heroi,
        b->id_base);

    fprio_insere(lef, evento, ENTRA, evento->tempo);

    printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n",
           evento->tempo,
           evento->d2,
           evento->d1);
  }
}

// Entra
void entra(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct heroi *h = &m->herois[ev->d1];
  struct base *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int tpb = 15 + (h->paciencia * aleat(1, 20));

  struct evento_t *evento = cria_evento(
      t + tpb,
      SAI,
      h->id_heroi,
      b->id_base);

  int status_fprio = fprio_insere(lef, evento, SAI, evento->tempo);
  if (status_fprio < 0)
    return;

  printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
         t,
         h->id_heroi,
         b->id_base,
         cjto_card(b->presentes),
         b->lotacao,
         t + tpb);
}

// Sai
void sai(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct heroi *h = &m->herois[ev->d1];
  struct base *b = &m->bases[ev->d2];
  int t = ev->tempo;

  int status_cjto;
  int status_fprio;

  printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
         t,
         h->id_heroi,
         b->id_base,
         cjto_card(b->presentes),
         b->lotacao);

  status_cjto = cjto_retira(b->presentes, h->id_heroi);

  if (status_cjto < 0)
    return;

  int destino = aleat(0, m->n_bases - 1);

  struct evento_t *ev_viaja = cria_evento(
      t,
      VIAJA,
      h->id_heroi,
      destino);

  status_fprio = fprio_insere(lef, ev_viaja, VIAJA, ev_viaja->tempo);
  if (status_fprio < 0)
    return;

  struct evento_t *ev_avisa = cria_evento(
      t,
      AVISA,
      h->id_heroi,
      b->id_base);

  status_fprio = fprio_insere(lef, ev_avisa, AVISA, ev_avisa->tempo);
  if (status_fprio < 0)
    return;
}

// Viaja
void viaja(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct heroi *h = &m->herois[ev->d1];
  struct base *d = &m->bases[ev->d2];
  int t = ev->tempo;

  struct base b = m->bases[h->id_base];
  int dist = calcula_distancia(b.local, d->local);
  int duracao = dist / h->velocidade;

  struct evento_t *evento = cria_evento(
      t + duracao,
      CHEGA,
      h->id_heroi,
      b.id_base);

  int status_fprio = fprio_insere(lef, evento, CHEGA, evento->tempo);
  if (status_fprio < 0)
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

// Morre
void morre(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct heroi *h = &m->herois[ev->d1];
  struct base *b = &m->bases[m->herois[ev->d1].id_base];
  struct missao *mi = &m->missoes[ev->d2];
  int t = ev->tempo;

  if (!b->presentes)
    return;

  printf("%6d: MORRE  HEROI %2d MISSAO %d\n",
         t,
         h->id_heroi,
         mi->id_missao);

  int resultado = cjto_retira(b->presentes, h->id_heroi);

  if (!resultado)
    return;

  h->morto = true;

  struct evento_t *evento = cria_evento(
      t,
      AVISA,
      h->id_heroi,
      b->id_base);

  int status_fprio = fprio_insere(lef, evento, AVISA, evento->tempo);
  if (status_fprio < 0)
    return;
}

// Missao
void missao(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct missao *mi = &m->missoes[ev->d1];
  int t = ev->tempo;

  int n = m->n_bases;
  int dist;
  int bmp;
  int risco;
  struct heroi *h;

  int tipo;
  int prio;

  struct fprio_t *dists_bases = fprio_cria();

  mi->tentativas++;

  printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", t, mi->id_missao, mi->tentativas);
  cjto_imprime(mi->habilidades);
  printf(" ]\n");

  for (int i = 0; i < n; i++)
  {
    dist = calcula_distancia(m->bases[i].local, mi->local);

    int status_fprio = fprio_insere(dists_bases, &m->bases[i], m->bases[i].id_base, dist);
    if (status_fprio < 0)
      return;
  }

  bmp = encontra_prox_base(m, mi, dists_bases);

  if (bmp >= 0)
  {
    mi->cumprida = true;
    struct base *b = &m->bases[bmp];

    b->missoes++;

    for (int i = 0; i < m->n_herois; i++)
    {
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
              -1);

          int status_fprio = fprio_insere(lef, evento, MORRE, evento->tempo);
          if (status_fprio < 0)
            return;
        }
        else
          h->experiencia++;
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

    int status_fprio = fprio_insere(lef, evento, MISSAO, evento->tempo);
    if (status_fprio < 0)
      return;

    printf("%6d: MISSAO %d IMPOSSIVEL\n", t, mi->id_missao);
  }

  // Removendo as bases ainda presentes na fila de prioridade

  while (fprio_tamanho(dists_bases) > 0)
   fprio_retira(dists_bases, &tipo, &prio);

  fprio_destroi(dists_bases);
}

// Fim
void fim(struct mundo *m, struct evento_t *ev)
{
  struct heroi heroi;
  struct base base;
  int t = ev->tempo;

  int missoes_cumpridas = 0;

  int max_tentativas = m->missoes[0].tentativas;
  int min_tentativas = m->missoes[0].tentativas;
  int soma_tentativas = 0;

  int total_mortos = 0;

  printf("%6d: FIM\n\n", t);

  // Estatísticas dos heróis
  for (int h = 0; h < m->n_herois; h++)
  {
    heroi = m->herois[h];

    if (!heroi.morto)
      printf("HEROI %2d VIVO  PAC %3d VEL %4d EXP %4d HABS [ ",
             heroi.id_heroi,
             heroi.paciencia,
             heroi.velocidade,
             heroi.experiencia);
    else
    {
      total_mortos++;

      printf("HEROI %2d MORTO  PAC %3d VEL %4d EXP %4d HABS [ ",
             heroi.id_heroi,
             heroi.paciencia,
             heroi.velocidade,
             heroi.experiencia);
    }

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
  {
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n",
           missoes_cumpridas,
           m->n_missoes,
           (float)(missoes_cumpridas * 100) / m->n_missoes);
  }
  else
    printf("MISSOES CUMPRIDAS: 0/%d (0.0%%)\n", m->n_missoes);

  printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n",
         min_tentativas,
         max_tentativas,
         soma_tentativas / (float)m->n_missoes);
  printf("TAXA MORTALIDADE: %.1f%%\n", 100 * (total_mortos) / (float)m->n_herois);
}
