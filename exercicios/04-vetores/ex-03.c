/*
Ordenação I:

- ler um número N e um vetor de N inteiros
- ordenar o vetor lido usando a técnica de ordenação da bolha
- imprimir os elementos do vetor ordenado
*/

#include <stdio.h>

int main()
{   
    int n, aux;
    scanf("%d", &n);
    int vetor[n];

    // leitura do vetor
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                // inverte elementos de lugar
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }

    // imprime vetor ordenado
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");

    return 0;
}