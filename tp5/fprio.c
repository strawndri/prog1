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

  struct fpnodo_t *aux, *nodo, *anterior;

  if (!f)
    return -1;

  aux = malloc(sizeof(struct fpnodo_t));
  if (!aux)
    return -1;

  // Evita que o mesmo item seja inserido mais de uma vez
  aux = f->prim;
  while (aux)
  { 
    if (aux->item == item)
      return -1;
    
    anterior = aux;
    aux = aux->prox;
  }

  nodo = malloc(sizeof(struct fpnodo_t));
  if (!nodo)
    return -1;

  nodo->item = item;
  nodo->prio = prio;
  nodo->tipo = tipo;
  nodo->prox = NULL;

  // Caso 1: adiciona o nodo no inicio da fila
  if (!anterior)
  {
    nodo->prox = f->prim;
    f->prim = nodo;
  }
  // Caso 2: adiciona o nodo em local específicoelse
  else
  {
    anterior->prox = nodo;
    nodo->prox = aux;
  }

  f->num++;
  return f->num;
}