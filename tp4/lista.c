// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Cria uma lista vazia.
// Retorno: ponteiro p/ a lista ou NULL em erro.
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

// Remove todos os itens da lista e libera a memória.
// Retorno: NULL.
struct lista_t *lista_destroi(struct lista_t *lst)
{
  int elemento;

  if (!lst)
    return NULL;

  // criar lista_tamanho e lista_retira
  while (lista_tamanho(lst) > 0)
    lista_retira(lst, &elemento);

  free(lst);

  return NULL;
}

// Insere o item na lista na posição indicada;
// se a posição for além do fim da lista ou for -1, insere no fim.
// Retorno: número de itens na lista após a operação ou -1 em erro.
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
  else if (pos <= 0)
  {
    aux->prox = lst->prim;
    lst->prim->ant = aux;
    lst->prim = aux;
  }
  else
  { 
    // Caso 3: inserção em posição específica
    atual = lst->prim;
    for (int i = 0; i < pos - 1 && atual->prox; i++)
    {
      atual = atual->prox;
    }

    // Caso 4: inserção no final
    if (atual == lst->ult)
    {
      aux->ant = lst->ult;
      lst->ult->prox = aux;
      lst->ult = aux;
    }

    // Último caso: inserção no meio
    else
    {
      aux->prox = atual->prox;
      aux->ant = atual;
      atual->prox->ant = aux;
      atual->prox = aux;
    }
  }

  lst->tamanho++;

  return (lst->tamanho);
}
