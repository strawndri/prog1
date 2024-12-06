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
  int tempo; // MOmento atual do evento
  int tipo;  // Categoria
  int d1;    // Dado 1
  int d2;    // Dado 2
};

// Retorno: ponteiro para a struct evento_t
struct evento_t *cria_evento(int tempo, int tipo, int d1, int d2);

// Trata o evento CHEGA
// Retorno: NULL
void trata_ev_chega(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento ESPERA
// Retorno: NULL
void trata_ev_espera(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento DESISTE
// Retorno: NULL
void trata_ev_desiste(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento AVISA
// Retorno: NULL
void trata_ev_avisa(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento ENTRA
// Retorno: NULL
void trata_ev_entra(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento SAI
// Retorno: NULL
void trata_ev_sai(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento VIAJA
// Retorno: NULL
void trata_ev_viaja(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento MORRE
// Retorno: NULL
void trata_ev_morre(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento MISSAO
// Retorno: NULL
void trata_ev_missao(struct mundo_t *m, struct evento_t *ev, struct fprio_t *lef);

// Trata o evento FIM
// Retorno: NULL
void trata_ev_fim(struct mundo_t *m, struct evento_t *ev);

#endif