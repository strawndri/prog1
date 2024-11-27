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

// Função para realizar os eventos iniciais
void executa_eventos_iniciais(struct mundo *m, struct fprio_t *lef)
{
  // Evento inicial (herói)
  for (int i = 0; i < m->n_herois; i++)
  {
    int base = aleat(0, m->n_bases - 1); // id da base
    int tempo = aleat(0, 4320);

    struct evento_t *evento = cria_evento(tempo, CHEGA, i, base);
    fprio_insere(lef, evento, CHEGA, tempo);
  }

  // Evento inicial (missão)
  for (int i = 0; i < m->n_missoes; i++)
  {
    int tempo = aleat(0, T_FIM_DO_MUNDO);

    struct evento_t *evento = cria_evento(tempo, MISSAO, i, -1);
    fprio_insere(lef, evento, MISSAO, tempo);
  }

  // Agendando o fim do mundo
  int tempo = T_FIM_DO_MUNDO;
  struct evento_t *evento = cria_evento(tempo, FIM, 0, 0);
  fprio_insere(lef, evento, FIM, tempo);
}

// Funções dos eventos ---------------------------------------------------------

// Chega: heroi H chegando na ba B no instante T
void chega(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{
  // dados do evento atual
  struct heroi h = m->herois[ev->d1];
  struct base b = m->bases[ev->d2];
  int t = ev->tempo;

  int espera;
  int tipo_evento;
  char *msg;

  h.id_base = b.id_base;

  if (cjto_card(b.presentes) < b.lotacao && lista_tamanho(b.espera) == 0)
    espera = 1;
  else
    espera = (h.paciencia) > (10 * lista_tamanho(b.espera));

  tipo_evento = espera ? ESPERA : DESISTE;
  msg = espera ? "ESPERA" : "DESISTE";

  struct evento_t *evento = cria_evento(
      t,
      tipo_evento,
      h.id_heroi,
      b.id_base);

  printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) %s\n",
         evento->tempo,
         evento->d1,
         evento->d2,
         cjto_card(b.presentes),
         b.lotacao,
         msg);

  fprio_insere(lef, evento, tipo_evento, evento->tempo);
}

// Espera
void espera(struct mundo *m, struct evento_t *ev, struct fprio_t *lef)
{  
  // dados do evento atual
  struct heroi h = m->herois[ev->d1];
  struct base b = m->bases[ev->d2];
  int t = ev->tempo;

  lista_insere(b.espera, h.id_heroi, -1);

  // atualiza a quantidade máxima de pessoas na fila de espera
  if (lista_tamanho(b.espera) > b.espera_max)
    b.espera_max = lista_tamanho(b.espera);

  struct evento_t *evento = cria_evento(
      t,
      AVISA,
      h.id_heroi,
      b.id_base);

  printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
         evento->tempo,
         evento->d1,
         evento->d2,
         lista_tamanho(b.espera));

  fprio_insere(lef, evento, AVISA, evento->tempo);
}

// Desiste
void desiste(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
{
  int destino = aleat(0, m->n_bases - 1);

  struct evento_t *evento = cria_evento(
      t,
      VIAJA,
      h->id_heroi,
      destino);

  printf("%6d: DESIST HEROI %2d BASE %d",
         t,
         evento->d1,
         b->id_base);

  fprio_insere(lef, evento, VIAJA, evento->tempo);
}

// Avisa
void avisa(int t, struct base *b, struct fprio_t *lef)
{
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
    lista_consulta(b->espera, &heroi, 0);
    lista_retira(b->espera, &heroi, 0);
    cjto_insere(b->presentes, heroi);

    struct evento_t *evento = cria_evento(
        t,
        ENTRA,
        heroi,
        b->id_base);

    fprio_insere(lef, evento, ENTRA, evento->tempo);

    printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n",
           evento->tempo,
           evento->d1,
           evento->d2);
  }
}

// Entra
void entra(int t, struct heroi *h, struct base *b, struct fprio_t *lef)
{
  int tpb = 15 + h->paciencia * aleat(1, 20);

  struct evento_t *evento = cria_evento(
      t + tpb,
      SAI,
      h->id_heroi,
      h->id_base);

  fprio_insere(lef, evento, SAI, evento->tempo);

  printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
         t,
         evento->d1,
         evento->d2,
         cjto_card(b->presentes),
         b->lotacao,
         evento->tempo);
}

// Sai
void sai(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
{
  cjto_retira(b->presentes, h->id_heroi);
  int destino = aleat(0, m->n_bases - 1);

  struct evento_t *ev_viaja = cria_evento(
      t,
      VIAJA,
      h->id_heroi,
      destino);

  fprio_insere(lef, ev_viaja, VIAJA, ev_viaja->tempo);

  struct evento_t *ev_avisa = cria_evento(
      t,
      AVISA,
      h->id_heroi,
      b->id_base);

  fprio_insere(lef, ev_avisa, AVISA, ev_avisa->tempo);

  printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
         ev_avisa->tempo,
         ev_avisa->d1,
         ev_avisa->d2,
         cjto_card(b->presentes),
         b->lotacao);
}

// Viaja
void viaja(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
{
  struct base atual = m->bases[h->id_base];
  int dist = calcula_distancia(atual.local, b->local);
  int duracao = dist / h->velocidade;

  struct evento_t *evento = cria_evento(
      t + duracao,
      CHEGA,
      h->id_heroi,
      b->id_base);

  fprio_insere(lef, evento, CHEGA, evento->tempo);

  printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
         t,
         evento->d1,
         atual.id_base,
         evento->d2,
         dist,
         h->velocidade,
         evento->tempo);
}

// Morre
void morre(int t, struct heroi *h, struct base *b, struct fprio_t *lef)
{
  if (!b->presentes)
    return;

  int resultado = cjto_retira(b->presentes, h->id_heroi);

  if (!resultado)
    return;

  h->morto = true;

  struct evento_t *evento = cria_evento(
      t,
      AVISA,
      h->id_heroi,
      b->id_base);

  fprio_insere(lef, evento, AVISA, evento->tempo);

  printf("%6d: MORRE  HEROI %2d MISSAO %d\n",
         evento->tempo,
         evento->d1,
         evento->tempo);
}

// Missao
void missao(struct mundo *m, int t, struct missao *mi, struct fprio_t *lef)
{
  int n = m->n_bases;
  int dist;
  int bmp;
  int risco;
  struct heroi h;

  struct fprio_t *dists_bases = fprio_cria();

  mi->tentativas++;

  printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", t, mi->id_missao, mi->tentativas);
  cjto_imprime(mi->habilidades);
  printf(" ]\n");

  for (int i = 0; i < n; i++)
  {
    dist = calcula_distancia(m->bases[i].local, mi->local);
    fprio_insere(dists_bases, &m->bases[i], m->bases[i].id_base, dist);
  }

  bmp = encontra_prox_base(m, mi, dists_bases);

  if (bmp >= 0)
  {
    mi->cumprida = true;
    m->bases[bmp].missoes++;

    for (int i = 0; i < m->n_herois; i++)
    {
      if (cjto_pertence(m->bases[bmp].presentes, i))
      {
        h = m->herois[i];
        risco = mi->perigo / (h.paciencia + h.experiencia + 1.0);

        if (risco > aleat(0, 30))
        {
          struct evento_t *evento = cria_evento(
              t,
              MORRE,
              h.id_heroi,
              -1);

          fprio_insere(lef, evento, MORRE, evento->tempo);
        }
        else
          h.experiencia++;
      }
    }

    printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", t, mi->id_missao, m->bases[bmp].id_base);
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

    fprio_insere(lef, evento, MISSAO, evento->tempo);

    printf("%6d: MISSAO %d IMPOSSIVEL\n", t, mi->id_missao);
  }
}

// Fim
void fim(struct mundo *m, int t)
{
  struct heroi heroi;
  struct base base;
  int missoes_cumpridas = 0;

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
      printf("HEROI %2d MORTO  PAC %3d VEL %4d EXP %4d HABS [ ",
             heroi.id_heroi,
             heroi.paciencia,
             heroi.velocidade,
             heroi.experiencia);

    cjto_imprime(heroi.habilidades);
    printf(" ]\n");
  }

  // Estatísticas das bases
  for (int b = 0; b < m->n_bases; b++)
  {
    base = m->bases[b];

    printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d",
           base.id_base,
           base.lotacao,
           base.espera_max,
           base.missoes);
  }

  printf("EVENTOS TRATADOS: %d", m->total_eventos);

  for (int mi = 0; mi < m->n_missoes; m++)
    if (m->missoes[mi].cumprida)
      missoes_cumpridas++;

  printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)",
         missoes_cumpridas,
         m->n_missoes,
         (float)(missoes_cumpridas / m->n_missoes));

  printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f", 0, 0, 0.0);
  printf("TAXA MORTALIDADE: %.1f%%", 0.0);
}