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

int chega(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void espera(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void desiste(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void avisa(struct mundo *m, int t, struct base *b, struct fprio_t *lef);

void entra(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void sai(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void viaja(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void morre(struct mundo *m, int t, struct heroi *h, struct base *b, struct fprio_t *lef);

void missao(struct mundo *m, int t, struct missao *mi, struct fprio_t *lef);

void fim(struct mundo *m, int t, struct fprio_t *lef);

#endif