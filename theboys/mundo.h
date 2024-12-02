#ifndef MUNDO
#define MUNDO

#include "entidades.h"
#include "utils.h"

// Estrutura que implementa um mundo
struct mundo_t
{
  int n_herois;                       // Quantidade de heróis
  struct heroi_t herois[N_HEROIS];      // Vetor contendo os heróis

  int n_bases;                        // Quantidade de bases
  struct base_t bases[N_BASES];         // Vetor contendo as bases

  int n_missoes;                      // Quantidade de missões
  struct missao_t missoes[N_MISSOES];   // Vetor contendo as missões

  int n_habilidades;                  // Quantidade de habilidades

  struct coordenadas_t tamanho_mundo; // Dimensões do mundo
  int relogio;                        // Tempo atual

  int total_eventos;                  // Quantidade de eventos processados
};

void inicia_mundo(struct mundo_t *m);

int encontra_prox_base(struct mundo_t *m, struct missao_t *mi, struct fprio_t *dists);

void executa_eventos_iniciais(struct mundo_t *m, struct fprio_t *lef);

int executa_eventos(struct mundo_t *m, struct fprio_t *lef);

void destroi_mundo(struct mundo_t *m);

#endif