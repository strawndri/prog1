/*
Ordenação II:

- ler um número N e um vetor de N inteiros
- ordenar o vetor lido usando a técnica de ordenação por seleção
- imprimir os elementos do vetor ordenado
*/


#include <stdio.h>

int main()
{   
    int n, min, aux;
    scanf("%d", &n);
    int vetor[n];

    // leitura do vetor
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        min = i;

        for (int j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[min]) {
                min = j;
            }
        }

        if (min != i) {
            aux = vetor[min];
            vetor[min] = vetor[i];
            vetor[i] = aux;
        }
    }

    // imprime vetor ordenado
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");

    return 0;
}
