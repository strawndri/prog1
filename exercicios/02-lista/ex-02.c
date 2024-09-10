/*
A definição de uma série de pares Valor-Quadrado em Matemática é dada 
pela presença de elementos numéricos, organizados em sequências dois-a-dois, 
em que cada número é seguido de seu quadrado exatamente uma vez.

Faça um programa em C que leia do teclado uma sequência com uma 
quantidade arbitrária de valores inteiros positivos. A sequência 
termina com o valor 0, que serve para indicar o final da entrada de 
dados e não deverá ser processado. O programa deve determinar e imprimir 
se a série é ou não do tipo Valor-Quadrado, imprimindo 1 caso seja e 0 
caso não seja.
*/

#include <stdio.h>

int main()
{
    int n_atual, n_anterior;
    int eh_valor_quadrado = 1;

    while (scanf("%d", &n_atual) && n_atual) {
        n_anterior = n_atual;
        scanf("%d", &n_atual);

        if (n_anterior * n_anterior != n_atual) {
            eh_valor_quadrado = 0;
        }
    }

    printf("%d\n", eh_valor_quadrado);

    return 0;
}