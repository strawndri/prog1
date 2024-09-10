/* 
Faça um programa em C que leia um valor inteiro n >= 1 do teclado e
em seguida imprima o valor de n!

Observação: a função fatorial cresce muito rapidamente, então para valores
relativamente pequenos de n já pode haver overflow, por isso teste seu
programa para valores não muito grandes.
*/

#include <stdio.h>

int main()
{
    long long int fat = 1;
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n; ++i) {
        fat *= i;
    }

    printf("%lld\n", fat);
    
    return 0;
}
