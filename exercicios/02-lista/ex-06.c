/*
Faça um programa em C que leia um número interio n >= 1 do teclado e que
imprima em seguida os n primeiros números da sequência de Fibonacci.

Observação: os valores desta sequência crescem muito rapidamente, então para 
valores relativamentes pequenos de n já pode haver overflows, por isso teste
seu programa para valores não muito grandes.
*/

#include <stdio.h>

int main()
{
    long long anterior = 1, atual = 1;
    int n, proximo;
    scanf("%d", &n);
    printf("%lld %lld ", anterior, atual);
    
    for (int i = 2; i < n; ++i) {
        proximo = anterior + atual;
        printf("%lld ", proximo);

        anterior = atual;
        atual = proximo;
    }

    printf("\n");

    return 0;
}