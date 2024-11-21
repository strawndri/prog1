#ifndef MUNDO
#define MUNDO

#include "entidades.h"
#include "utils.h"

struct mundo
{
  int n_herois;
  struct heroi herois[N_HEROIS];

  int n_bases;
  struct base bases[N_BASES];

  int n_missoes;
  struct missao missoes[N_MISSOES];

  int n_habilidades;

  struct coordenada tamanho_mundo;
  int relogio;
};

void inicia_mundo(struct mundo *m);

#endif