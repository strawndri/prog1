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
  // for (int i = 0; i < m->n_missoes; i++)
  // {
  //   int tempo = aleat(0, 4320);

  //   struct evento_t *evento = cria_evento(tempo, CHEGA, i, 0);
  //   fprio_insere(lef, evento, MISSAO, tempo);
  // }

  // // Agendando o fim do mundo
  // int tempo = T_FIM_DO_MUNDO;
  // struct evento_t *evento = cria_evento(tempo, FIM, 0, 0);
  // fprio_insere(lef, evento, FIM, tempo);
}

// Funções dos eventos ---------------------------------------------------------

// Chega: heroi H chegando na ba B no instante T
int chega(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
{
  h->id_base = b->id_base;
  int espera;

  if (cjto_card(b->presentes) < b->lotacao && lista_tamanho(b->espera) == 0)
    espera = 1;
  else
    espera = (h->paciencia) > (10 * lista_tamanho(b->espera));

  if (espera)
  {
    struct evento_t *evento = cria_evento(
        t,
        ESPERA,
        h->id_heroi,
        b->id_base);
    fprio_insere(lef, evento, ESPERA, t);
    return 1;
  }
  else
  {
    struct evento_t *evento = cria_evento(
        m->relogio,
        DESISTE,
        h->id_heroi,
        b->id_base);

    fprio_insere(lef, evento, DESISTE, m->relogio);
    return 0;
  }
}

// Espera
void espera(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
{
  lista_insere(b->espera, h->id_heroi, -1);

  struct evento_t *evento = cria_evento(
      t,
      AVISA,
      h->id_heroi,
      b->id_base);

  fprio_insere(lef, evento, AVISA, m->relogio);
}

// // Desiste
// void desiste(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
// {
// }

// // Avisa
// void avisa(struct mundo *m, int t, struct base *b, struct fprio_t *lef)
// {
// }

// // Entra
// void entra(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
// {
// }

// // Sai
// void sai(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
// {
// }

// // Viaja
// void viaja(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
// {
// }

// // Morre
// void morre(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
// {
// }

// // Missao
// void missao(struct mundo *m, int t, struct missao *mi, struct fprio_t *lef)
// {
// }

// // Fim
// void fim(struct mundo *m, int t, struct fprio_t *lef)
// {
// }