/* 
Faça um programa em C que leia do teclado um número inteiro positivo
n e verifique se ele é triangular ou não. Se for, imprima 1, e se não
for, imprima 0.
*/

#include <stdio.h>
#include <math.h>

int main() 
{
    int n;
    int eh_triangular = 0;

    scanf("%d", &n);

    for (int i = 1; i < sqrt(n); ++i) {
        if (n == (i * (i + 1) * (i + 2))) {
            eh_triangular = 1;
            break;
        }
    }

    printf("%d\n", eh_triangular);

    return 0;
}