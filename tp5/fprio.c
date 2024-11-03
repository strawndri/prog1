// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com fila de prioridade

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria()
{
  struct fprio_t *f;

  // Aloca struct referente à fila
  f = malloc(sizeof(struct fprio_t));
  if (!f)
    return NULL;

  f->prim = NULL;
  f->num = 0;

  return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi(struct fprio_t *f)
{
  int elemento;

  // Verifica se a fila é válida
  if (!f)
    return NULL;

  // Remove sempre o primeiro elemento até que a fila esteja vazia
  while (f->num > 0)
    fprio_retira(f, &elemento, 0);

  free(f);

  return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio)
{

  struct fpnodo_t *aux;

  if (!f)
    return -1;

  aux = malloc(sizeof(struct fpnodo_t));
  if (!aux)
    return -1;

  aux = f->prim;

  while (aux)
  {
    if (aux->item == item)
      return -1;
    aux = aux->prox;
  }

  // if (!f->prim)
  // {
  //   f->prim->item = item;
  //   f->prim->prio = prio;
  //   f->prim->tipo = tipo;
  //   f->prim->prox = NULL;
  // }
  // else
  // {

  //   while (aux && aux->prio <= prio)
  //   {
  //     if (aux->item == item)
  //       return -1;
  //   }

  //   aux->item = item;
  //   aux->prio = prio;
  //   aux->tipo = tipo;
  // }

  return f->num;
}