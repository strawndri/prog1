#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// Cria uma fila vazia
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

// Libera todas as estruturas de dados da fila
struct fprio_t *fprio_destroi(struct fprio_t *f)
{
  // Verifica se a fila é válida
  if (!f)
    return NULL;

  free(f);

  return NULL;
}

// Insere itens na fila, mantendo-a ordenada a partir da prioridade
int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio)
{
  struct fpnodo_t *aux, *nodo;
  struct fpnodo_t *anterior = NULL;

  // Verifica se a fila é válida
  if (!f || !item)
    return -1;

  // Evita que o mesmo item seja inserido mais de uma vez
  // aux representa o nodo atual que está sendo verificado
  // anterior representa o nodo anterior ao aux
  aux = f->prim;
  while (aux && aux->prio <= prio)
  {
    if (aux->item == item)
      return -1;

    anterior = aux;
    aux = aux->prox;
  }

  // Aloca na memória um novo nodo
  nodo = malloc(sizeof(struct fpnodo_t));
  if (!nodo)
    return -1;

  nodo->item = item;
  nodo->prio = prio;
  nodo->tipo = tipo;
  nodo->prox = aux;

  // Caso 1: adiciona o nodo no início da fila
  if (!anterior)
    f->prim = nodo;

  // Caso 2: adiciona o nodo em local específico
  else
    anterior->prox = nodo;

  f->num++;
  
  return fprio_tamanho(f);
}

// Retira o primeiro item da fila e o devolve
void *fprio_retira(struct fprio_t *f, int *tipo, int *prio)
{
  struct fpnodo_t *aux;
  void *item;

  // Verifica se a fila, o tipo e a prioridade são válidos
  if (!f || fprio_tamanho(f) <= 0 || !tipo || !prio)
    return NULL;

  aux = f->prim;
  item = aux->item;

  *tipo = aux->tipo;
  *prio = aux->prio;

  // Retira e libera o primeiro item da fila
  f->prim = aux->prox;
  free(aux);

  f->num--;

  return item;
}

// Informa o número de itens na fila
int fprio_tamanho(struct fprio_t *f)
{
  // Verifica se a fila é válida
  if (!f)
    return -1;

  return f->num;
}

// Imprime o conteúdo da fila
void fprio_imprime(struct fprio_t *f)
{
  struct fpnodo_t *aux;

  // Verifica se a fila é válida
  if (!f || f->num <= 0)
    return;

  aux = f->prim;
  printf("(%d %d)", aux->tipo, aux->prio);
  aux = aux->prox;

  while (aux)
  {
    printf(" (%d %d)", aux->tipo, aux->prio);
    aux = aux->prox;
  }
}
