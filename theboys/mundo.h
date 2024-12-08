// Declarações e configurações do mundo
// Autora: Andrieli Luci Gonçalves, GRR 202449003
// Dez 2024

#ifndef MUNDO
#define MUNDO

#include "utils.h"
#include "entidades.h"

// Estrutura que implementa um mundo
struct mundo_t
{
  int n_herois;                        // Quantidade de heróis
  struct heroi_t *herois[N_HEROIS];    // Vetor contendo os heróis

  int n_bases;                         // Quantidade de bases
  struct base_t *bases[N_BASES];       // Vetor contendo as bases

  int n_missoes;                       // Quantidade de missões
  struct missao_t *missoes[N_MISSOES]; // Vetor contendo as missões

  int n_habilidades;                   // Quantidade de habilidades

  struct coordenadas_t tamanho_mundo;  // Dimensões do mundo
  int relogio;                         // Tempo atual

  int total_eventos;                   // Quantidade de eventos processados
};

// Inicializa as propriedades do mundo e cria bases, heróis e missões
// Retorno: ponteiro para o mundo ou NULL se erro
struct mundo_t *cria_mundo();

// Agenda os eventos essenciais (CHEGA, MISSAO e FIM) para iniciar
// a simulação, criando-os e adicionandos à LEF
// Retorno: void
void agenda_eventos_iniciais(struct mundo_t *m, struct fprio_t *lef);

// Percorre a LEF e executa as funções que tratam os eventos da simulação
// Retorno: void
void executa_eventos(struct mundo_t *m, struct fprio_t *lef);

// Busca a base mais próxima (BMP) que com todas as habilidades 
// necessárias para completar a missão
// Retorno: id da BMP ou -1 em caso de erro
int encontra_prox_base(struct mundo_t *m, struct missao_t *mi, struct fprio_t *dists);

// Libera o mundo e as estruturas presentes nele
// Retorno: NULL
struct mundo_t *destroi_mundo(struct mundo_t *m);

#endif