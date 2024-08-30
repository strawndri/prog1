/*
Faça um programa em C que leia do teclado uma sequência de números inteiros até 
que seja lido um número que seja o dobro ou a metade do anteriormente lido.
O programa deve imprimir na saída três números inteiros que são, respectivamente,
a quantidade de números lidos, a soma dos números lidos e os dois valores
que forçaram a parada do programa.
*/

#include <stdio.h>

int main()
{
    int qtd = 1, soma = 0, anterior = 0, atual;

    scanf("%d", &atual);

    while ((atual != anterior * 2) && (atual * 2 != anterior)) {
        soma += atual;

        anterior = atual;
        scanf("%d", &atual);
        
        qtd += 1;
    }   

    printf("%d %d %d %d\n", qtd, soma, anterior, atual);

    return 0;
}