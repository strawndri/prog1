/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* programa principal */
int main ()
{
  int n, max, min;
  struct racional r1, r2;

  srand (0);

  /* Certifica que o usuário informou os números no intervalo esperado:
   * 0 < n < 100 
   * 0 < max < 30
  */
  do {
    scanf("%d", &n);
    scanf("%d", &max);
  } while ((n <= 0 || n >= 100) || (max <= 0 || max >= 30));

  /* min será o extremo negativo de max */
  min = (-1) * max;

  for (int i = 1; i <= n; i++) {
    printf("%d: ", i);

    r1 = sorteia_r(min, max);
    r2 = sorteia_r(min, max);

    imprime_r(r1);
    
    printf(" ");
    imprime_r(r2);

    /* Evita a realização das operações no caso de números inválidos*/
    if (!valido_r(r1) || !valido_r(r2)) {
      printf(" ");
      printf("NUMERO INVALIDO\n");
      return 1;
    }

    struct racional soma, subtracao, multiplicacao, divisao;
    soma = soma_r(r1, r2);
    subtracao = subtrai_r(r1, r2);
    multiplicacao = multiplica_r(r1, r2);
    divisao = divide_r(r1, r2);

    /* Evita a impressão dos resultados no caso de divisão inválida*/
    if (!valido_r(divisao)) {
      printf(" ");
      printf("DIVISAO INVALIDA\n");
      return 1;
    }

    printf(" ");
    imprime_r(soma);
    
    printf(" ");
    imprime_r(subtracao);
    
    printf(" ");
    imprime_r(multiplicacao);
    
    printf(" ");
    imprime_r(divisao);
    printf("\n");
  }

  return (0);
}
