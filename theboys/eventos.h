#ifndef EVENTOS
#define EVENTOS

#include <stdio.h>
#include "utils.h"
#include "mundo.h"

// d1 e d2 representam dados que podem ser (ou não) usados na estrutura
struct evento_t
{
  int tempo;
  int d1, d2;
};

void executa_eventos_iniciais(struct mundo *m, struct fprio_t *lef);

void chega(int t, struct heroi *h, struct base *b);;

void espera(int t, struct heroi *h, struct base *b);

void desiste(int t, struct heroi *h, struct base *b);

void avisa(int t, struct base *b);

void entra(int t, struct heroi *h, struct base *b);

void sai(int t, struct heroi *h, struct base *b);

void viaja(int t, struct heroi *h, struct base *b);

void morre(int t, struct heroi *h, struct base *b);

void missao(int t, struct missao *m);

void fim(int t);

#endif