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
    int qtd, soma, atual, anterior;

    scanf("%d", &atual);
    soma = atual;
    qtd = 1; // início da contagem dos números

    do {
        anterior = atual;
        scanf("%d", &atual);
        qtd++;
        soma += atual;
    } while ((atual != anterior * 2) && (atual * 2 != anterior));
    
    printf("%d %d %d %d\n", qtd, soma, anterior, atual);

    return 0;
}