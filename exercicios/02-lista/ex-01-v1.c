/* 
Faça um programa em C que leia do teclado um número inteiro positivo
n e verifique se ele é triangular ou não. Se for, imprima 1, e se não
for, imprima 0.
*/

#include <stdio.h>

int main() {
    int n, k = 1, produto;
    int eh_triangular = 0;
    scanf("%d", &n);

    produto = (k * (k + 1) * (k + 2));

    while (n > produto) {
        k += 1;
        produto = (k * (k + 1) * (k + 2));
    }

    if (n == produto)
        eh_triangular = 1;

    printf("%d\n", eh_triangular);

    return 0;
}