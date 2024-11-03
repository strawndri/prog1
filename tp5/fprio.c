// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria()
{
  struct fprio_t *fprio;

  // Aloca struct referente à fila
  fprio = malloc(sizeof(struct fprio_t));
  if (!fprio)
    return NULL;

  fprio->prim = NULL;
  fprio->num = 0;

  return fprio;
}