/*
Um inteiro positivo N é considerado perfeito se o mesmo for igual 
a soma de seus divisores positivos diferentes de N.

Exemplo: 6 é perfeito pois 1 + 2 + 3 = 6 e 1, 2, e 3 são todos os 
divisores positivos de 6 e que são diferentes de 6.

Faça um programa em C que leia um número inteiro positivo K e mostre os K
primeiros números que são perfeitos.
*/

#include <stdio.h>

int main() 
{
    int i = 1, n = 1;
    int k, soma, divisor;
    scanf("%d", &k);

    while (i <= k) {
        soma = 0;
        divisor = 1;

        while (divisor <= n / 2) {
            if (n % divisor == 0) {
                soma += divisor;
            }

            divisor += 1;
        }

        if (soma == n) {
            printf("%d ", n);
            i += 1;
        }

        n += 1;
    }

    printf("\n");

    return 0;
}