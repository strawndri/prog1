/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define N 100

/* coloque aqui as funções auxiliares que precisar neste arquivo */

void imprime_vetor(struct racional vetor[], int n)
{ 
  printf("VETOR = ");
  for (int i = 0; i < n; i++) {
    imprime_r(vetor[i]);
    printf(" ");
  }
  printf("\n");
}

void elimina_invalidos(struct racional vetor[], int *n)
{ 
  int i = 0;
  while (i < *n) {
    if (!valido_r(vetor[i])) {
      vetor[i] = vetor[*n - 1];
      (*n)--;
    } else {
      i++;
    }
  }
}

void ordena_vetor(struct racional vetor[], int n)
{ 
  struct racional aux;
  for (int i = n - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
        if (compara_r(vetor[j], vetor[j + 1]) == 1) {
            aux = vetor[j];
            vetor[j] = vetor[j + 1];
            vetor[j + 1] = aux;
        }
    }
  }
}

/* programa principal */
int main ()
{ 
  int n;
  long numerador, denominador;
  struct racional racional;

  struct racional vetor[N];

  do {
    scanf("%d", &n);
  } while (n <= 0 || n >= 100);

  for (int i = 0; i < n; i++) {
    scanf("%ld %ld", &numerador, &denominador);
    racional = cria_r(numerador, denominador);
    vetor[i] = racional;
  }

  imprime_vetor(vetor, n);

  elimina_invalidos(vetor, &n);
  imprime_vetor(vetor, n);

  ordena_vetor(vetor, n);
  imprime_vetor(vetor, n);

  struct racional soma;
  soma = cria_r(0, 1);

  for (int i = 0; i < n; i++) {
    soma_r(soma, vetor[i], &soma);
  }

  printf("SOMA = ");
  imprime_r(soma);
  printf("\n");

  return (0) ;
}
