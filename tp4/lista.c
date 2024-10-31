// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Cria uma lista vazia
struct lista_t *lista_cria()
{
  struct lista_t *lst;

  // Aloca struct referente à lista
  lst = malloc(sizeof(struct lista_t));
  if (!lst)
    return NULL;

  lst->prim = NULL;
  lst->ult = NULL;
  lst->tamanho = 0;

  return lst;
}

// Remove todos os itens da lista e libera a memória
struct lista_t *lista_destroi(struct lista_t *lst)
{
  int elemento, i;

  if (!lst)
    return NULL;

  // criar lista_tamanho e lista_retira
  i = 0;
  while (lista_tamanho(lst) > 0)
    lista_retira(lst, &elemento, i);

  free(lst);

  return NULL;
}

// Insere o item na lista na posição indicada
int lista_insere(struct lista_t *lst, int item, int pos)
{
  struct item_t *aux, *atual;

  if (!lst)
    return -1;

  // Cria e inicia novo item
  aux = malloc(sizeof(struct item_t));
  if (!aux)
    return -1;

  aux->valor = item;
  aux->prox = NULL;
  aux->ant = NULL;

  // Caso 1: lista está vazia
  // O novo item é tanto o primeiro quanto o último da lista
  if (!lst->prim)
  {
    lst->prim = aux;
    lst->ult = aux;
  }

  // Caso 2: inserção no início
  else if (pos == 0)
  {
    aux->prox = lst->prim;
    lst->prim->ant = aux;
    lst->prim = aux;
  }

  // Caso 3: inserção no fim
  else if (pos >= lst->tamanho || pos == -1)
  {
    aux->ant = lst->ult;
    lst->ult->prox = aux;
    lst->ult = aux;
  }

  // Caso 4: inserção no meio
  else
  {
    atual = lst->prim;

    for (int i = 0; i < pos - 1 && atual->prox; i++)
      atual = atual->prox;

    aux->prox = atual->prox;
    aux->ant = atual;
    atual->prox->ant = aux;
    atual->prox = aux;
  }

  lst->tamanho++;

  return lst->tamanho;
}

// Retira o item da lista da posição indicada
int lista_retira(struct lista_t *lst, int *item, int pos)
{
  struct item_t *aux;

  if (!lst)
    return -1;

  if (lst->tamanho <= 0)
    return -1;

  // Caso 1: remoção do primeiro item
  if (pos == 0)
  {
    aux = lst->prim;
    *item = aux->valor;

    lst->prim = lst->prim->prox;

    if (lst->prim)
      lst->prim->ant = NULL;
  }

  // Caso 2: remoção do último item
  else if (pos >= lst->tamanho || pos == -1)
  {
    aux = lst->ult;
    *item = aux->valor;
    lst->ult = aux->ant;
    lst->ult->prox = NULL;
  }

  // Caso 3: remoção de item do meio
  else
  {
    aux = lst->prim;

    for (int i = 0; i < pos; i++)
      aux = aux->prox;

    *item = aux->valor;
    aux->ant->prox = aux->prox;

    if (aux->prox)
      aux->prox->ant = aux->ant;
  }

  free(aux);

  lst->tamanho--;

  return lst->tamanho;
}

// Informa o valor do item na posição indicada, sem retirá-lo
int lista_consulta(struct lista_t *lst, int *item, int pos)
{
  struct item_t *aux;

  if (!lst)
    return -1;

  // Caso 1: item está no final da lista
  if (pos == -1)
    aux = lst->ult;

  // Caso 2: consulta de uma posição específica
  else
  {
    aux = lst->prim;
    for (int i = 0; i < pos; i++)
    {
      if (!aux)
        return -1;

      aux = aux->prox;
    }
  }

  if (aux)
  {
    *item = aux->valor;
    return lst->tamanho;
  }

  return -1;
}

// Informa a posição da 1ª ocorrência do valor indicado na lista
int lista_procura(struct lista_t *lst, int valor)
{
  struct item_t *aux;

  if (!lst)
    return -1;

  aux = lst->prim;

  for (int i = 0; i < lst->tamanho; i++)
  {
    if (aux->valor == valor)
      return i;

    aux = aux->prox;
  }

  return -1;
}

// Informa o tamanho da lista (o número de itens presentes nela)
int lista_tamanho(struct lista_t *lst)
{
  if (!lst)
    return -1;

  return lst->tamanho;
}

// Imprime o conteúdo da lista do inicio ao fim
void lista_imprime(struct lista_t *lst)
{
  struct item_t *aux;

  if (!lst)
    return;

  if (lst->tamanho <= 0)
    return;

  aux = lst->prim;
  printf("%d", aux->valor);
  aux = aux->prox;

  while (aux)
  {
    printf(" %d", aux->valor);
    aux = aux->prox;
  }
}
