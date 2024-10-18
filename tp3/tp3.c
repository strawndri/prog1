/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Imprime os elementos de um vetor separando-os por um espaço em branco
 * O último elemento é impresso separadamente para evitar que um
 * espaço em branco extra seja printado
 */
void imprime_vetor(struct racional **vetor, int n)
{
  if (!n)
    return;

  for (int i = 0; i < n - 1; i++)
  {
    imprime_r(vetor[i]);
    printf(" ");
  }

  imprime_r(vetor[n - 1]);
}

/* Remoção de elementos x/0 (inválidos) presentes no vetor de racionais */
void elimina_invalidos(struct racional **vetor, int *n)
{
  int i = 0;
  /* Sempre que um elemento inválido é encontrado, ele é substituído
   * pelo último elemento do vetor. Toda vez que isso ocorre o tamanho do
   * vetor é diminuído em uma unidade.
   */
  while (i < *n)
  {
    if (!valido_r(vetor[i]))
    { 
      destroi_r(vetor[i]); /* Libera a memória do racional inválido */
      vetor[i] = vetor[*n - 1];
      (*n)--;
    }
    else
    {
      i++; /* Só avançamos a posição se a atual contém um racional válido */
    }
  }
}

/* Algoritmo Bubble Sort recursivo */
void ordena_vetor(struct racional **vetor, int n)
{
  int trocas;
  struct racional *aux;

  if (n == 1)
    return;

  trocas = 0;

  /* Compara elementos do vetor e troca-os se o atual é maior que o próximo */
  for (int i = 0; i < n - 1; i++)
  {
    if (compara_r(vetor[i], vetor[i + 1]) == 1)
    {
      aux = vetor[i];
      vetor[i] = vetor[i + 1];
      vetor[i + 1] = aux;
      trocas++;
    }
  }

  /* Se nenhuma troca ocorreu, o vetor já está ordenado */
  if (!trocas)
    return;

  ordena_vetor(vetor, n - 1);
}

/* programa principal */
int main()
{
  int n;
  long numerador, denominador;
  struct racional *soma;
  struct racional **vetor;

  /* Certifica que o usuário informou o número no intervalo esperado:
   * 0 < n < 100
   */
  do
  {
    scanf("%d", &n);
  } while (n <= 0 || n >= 100);

  /* Aloca memória para o vetor de ponteiros para racionais */
  vetor = (struct racional **)malloc(n * sizeof(struct racional *));
  if (vetor == NULL)
    return 0;

  for (int i = 0; i < n; i++)
  {
    scanf("%ld %ld", &numerador, &denominador);
    vetor[i] = cria_r(numerador, denominador);

    if (vetor[i] == NULL)
      return 0;
  }

  printf("VETOR = ");
  imprime_vetor(vetor, n);
  printf("\n");

  elimina_invalidos(vetor, &n);

  printf("VETOR = ");
  imprime_vetor(vetor, n);
  printf("\n");

  ordena_vetor(vetor, n);

  printf("VETOR = ");
  imprime_vetor(vetor, n);
  printf("\n");

  soma = cria_r(0, 1);
  for (int i = 0; i < n; i++)
    soma_r(soma, vetor[i], soma);

  printf("SOMA = ");
  imprime_r(soma);
  printf("\n");

  /* Liberação da memória dos racionais apontados pelo vetor */
  for (int i = 0; i < n; i++)
  {
    if (vetor[i] != NULL)
    {
      destroi_r(vetor[i]);
      vetor[i] = NULL;
    }
  }

  printf("VETOR = ");
  imprime_vetor(vetor, n);
  printf("\n");

  /* Liberação do vetor de ponteiros */
  free(vetor);
  vetor = NULL;

  /* Libera o espaço utilizado para a soma */
  destroi_r(soma);
  soma = NULL;

  return 0;
}
