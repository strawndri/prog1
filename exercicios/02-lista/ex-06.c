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
    long int a = 1, b = 1, c;
    int n;
    scanf("%d", &n);
    printf("%ld %ld ", a, b);
    
    for (int i = 2; i < n; ++i) {
        c = a + b;
        printf("%ld ", c);

        a = b;
        b = c;
    }

    printf("\n");

    return 0;
}