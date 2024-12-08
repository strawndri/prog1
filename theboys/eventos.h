// Declarações e configurações dos eventos
// Autora: Andrieli Luci Gonçalves, GRR 202449003
// Dez 2024

#ifndef EVENTOS
#define EVENTOS

#include <stdio.h>
#include "fprio.h"
#include "utils.h"
#include "mundo.h"

// Estrutura que implementa um mundo
// d1 e d2 representam dados que podem ser (ou não) usados na estrutura
struct evento_t
{
  int tempo; // Momento atual do evento
  int tipo;  // Categoria
  int d1;    // Dado 1
  int d2;    // Dado 2
};

// Cria um evento
// Retorno: ponteiro para a struct evento_t
struct evento_t *cria_evento(int tempo, int tipo, int d1, int d2);

// Trata o evento CHEGA
// Herói chega à base e decide permanece ou não, considerando a 
// paciência do herói e a lotação da base atual
// Retorno: void
void trata_ev_chega(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento ESPERA
// Herói entra na fila de espera da base
// Retorno: void
void trata_ev_espera(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento DESISTE
// Herói desiste de entrar na base atual e uma base destino é 
// escolhida aleatoriamente
// Retorno: void
void trata_ev_desiste(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento AVISA
// Porteiro trata a fila de espera da base, tendo a capacidade de
// admitir a entrada de heróis
// Retorno: void
void trata_ev_avisa(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento ENTRA
// Herói entra na base e agenda seu tempo de permanência
// Retorno: void
void trata_ev_entra(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento SAI
// Herói sai da base atual e escolhe uma base destino
// Retorno: void
void trata_ev_sai(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento VIAJA
// Herói se desloca para a base destino
// Retorno: void
void trata_ev_viaja(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento MORRE
// Herói morre e é removido da base em que estava
// Retorno: void
void trata_ev_morre(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento MISSAO
// Procura concluir a função buscando pela base mais apta e
// mata os heróis considerando seus riscos de morte
// Retorno: void
void trata_ev_missao(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento FIM
// Mostra as estatísticas da simulação após o fim do mundo
// Retorno: void
void trata_ev_fim(struct mundo_t *m, struct evento_t *ev);

#endif