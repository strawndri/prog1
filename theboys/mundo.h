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

  int total_eventos;
};

void inicia_mundo(struct mundo *m);

int encontra_prox_base(struct mundo *m, struct missao *mi, struct fprio_t *dists);

void executa_eventos_iniciais(struct mundo *m, struct fprio_t *lef);

int executa_eventos(struct mundo *m, struct fprio_t *lef);

void destroi_mundo(struct mundo *m);

#endif