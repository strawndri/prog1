#ifndef EVENTOS
#define EVENTOS

#include <stdio.h>
#include "fprio.h"
#include "utils.h"
#include "mundo.h"

// d1 e d2 representam dados que podem ser (ou não) usados na estrutura
struct evento_t
{
  int tempo;
  int tipo;
  int d1;
  int d2;
};

struct evento_t *cria_evento(int tempo, int tipo, int d1, int d2);

void executa_eventos_iniciais(struct mundo *m, struct fprio_t *lef);

void chega(struct mundo *m, struct evento_t *ev, struct fprio_t *lef);

void espera(struct mundo *m, struct evento_t *ev, struct fprio_t *lef);

void desiste(struct mundo *m, struct evento_t *ev, struct fprio_t *lef);

void avisa(struct mundo *m, struct evento_t *ev, struct fprio_t *lef);

void entra(struct mundo *m, struct evento_t *ev, struct fprio_t *lef);

void sai(struct mundo *m, struct evento_t *ev, struct fprio_t *lef);

void viaja(struct mundo *m, struct evento_t *ev, struct fprio_t *lef);

void morre(struct mundo *m, struct evento_t *ev, struct fprio_t *lef);

void missao(struct mundo *m, struct evento_t *ev, struct fprio_t *lef);

void fim(struct mundo *m, struct evento_t *ev);

#endif