/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* programa principal */
int main ()
{
  srand (0); /* use assim, com zero */

  int n, max;
  long r1, r2;

  scanf("%d", &n);
  scanf("%d", &max);

  for (int i = 1; i <= n; i++) {
    printf("%d: ", i);

    r1 = aleat(0, max);
    r2 = aleat(0, max);

    printf("%ld %ld", r1, r2);
    printf("\n");
  }

  return (0);
}
