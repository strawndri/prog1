/*
Passagem de parâmetros vetoriais

Escreva um programa para ordenação de vetores, com as seguintes funções:
    - le_vetor (vetor, N): ler um número N e um vetor de N inteiros;
    - ordena_vetor (vetor, N): ordenar o vetor lido usando a técnica de ordenação da bolha;
    - escreve_vetor (vetor, N): imprimir os elementos de um vetor com N elementos.
*/


#include <stdio.h>
#define N 5

void le_vetor(int vetor[], int n)
{
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }
}

void ordena_vetor(int vetor[], int n)
{   
    int aux;

    for (int i = n - 1; i > 0; i--){
        for (int j = 0; j < i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void escreve_vetor(int vetor[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");
}

int main()
{   
    int v[N];

    le_vetor(v, N);
    ordena_vetor(v, N);
    escreve_vetor(v, N);

    return 0;
}