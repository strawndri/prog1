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
void chega(int t, struct heroi *h, struct base *b, struct fprio_t *lef)
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

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n",
           evento->tempo,
           evento->d1,
           evento->d2,
           cjto_card(b->presentes),
           b->lotacao);

    fprio_insere(lef, evento, ESPERA, evento->tempo);
  }
  else
  {
    struct evento_t *evento = cria_evento(
        t,
        DESISTE,
        h->id_heroi,
        b->id_base);

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE\n",
           evento->tempo,
           evento->d1,
           evento->d2,
           cjto_card(b->presentes),
           b->lotacao);

    fprio_insere(lef, evento, DESISTE, evento->tempo);
  }
}

// Espera
void espera(int t, struct heroi *h, struct base *b, struct fprio_t *lef)
{
  lista_insere(b->espera, h->id_heroi, -1);
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

    fprio_insere(lef, evento, VIAJA, evento->tempo);

    printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n",
           evento->tempo,
           evento->d2,
           evento->d1);
  }
}

// Entra
// void entra(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef)
// {
//   int tpb = 15 + h->paciencia * aleat(1, 20);

//   struct evento_t *evento = cria_evento(
//       t + tpb,
//       SAI,
//       h->id_heroi,
//       h->id_base);

//   fprio_insere(lef, evento, VIAJA, evento->tempo);
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