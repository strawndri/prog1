/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define N 100

/* Imprime os elementos de um vetor separando-os por um espaço em branco
 * O último elemento é impresso separadamente para evitar que um
 * espaço em branco extra seja printado. 
*/
void imprime_vetor(struct racional vetor[], int n)
{ 
  printf("VETOR = ");

  if (!n)
    return;

  for (int i = 0; i < n - 1; i++) {
    imprime_r(vetor[i]);
    printf(" ");
  }

  imprime_r(vetor[n-1]);
}

/* Remoção de elementos x/0 presentes no vetor de racionais */
void elimina_invalidos(struct racional vetor[], int *n)
{ 
  int i = 0;
  /* Sempre que um elemento inválido é encontrado, ele é substituído
   * pelo último elemento do vetor. Toda vez que isso ocorre o tamanho do
   * vetor é diminuído em uma unidade.
  */
  while (i < *n) {
    if (!valido_r(vetor[i])) {
      vetor[i] = vetor[*n - 1];
      (*n)--;
    } else {
      i++; /* Só avançamos a posição se a atual contém um racional válido */
    }
  }
}

/* Algoritmo Bubble Sort recursivo */
void ordena_vetor(struct racional vetor[], int n)
{  
  if (n == 1)
    return;

  int trocas = 0;
  struct racional aux;

  /* Compara elementos do vetor e troca-os se o atual é maior que o próximo */
  for (int i = 0; i < n - 1; i++) {
    if (compara_r(vetor[i], vetor[i + 1]) > 0) {
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
int main ()
{ 
  int n;
  long numerador, denominador;
  struct racional racional;

  struct racional vetor[N];

  /* Certifica que o usuário informou o número no intervalo esperado:
   * 0 < n < 100 
  */
  do {
    scanf("%d", &n);
  } while (n <= 0 || n >= 100);

  for (int i = 0; i < n; i++) {
    scanf("%ld %ld", &numerador, &denominador);
    racional = cria_r(numerador, denominador);
    vetor[i] = racional;
  }

  imprime_vetor(vetor, n);
  printf("\n");

  elimina_invalidos(vetor, &n);
  imprime_vetor(vetor, n);
  printf("\n");

  ordena_vetor(vetor, n);
  imprime_vetor(vetor, n);
  printf("\n");

  struct racional soma;
  soma = cria_r(0, 1);

  for (int i = 0; i < n; i++) {
    soma_r(soma, vetor[i], &soma);
  }

  printf("SOMA = ");
  imprime_r(soma);
  printf("\n");

  return 0;
}
