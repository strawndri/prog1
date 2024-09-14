/*
Melhorar o programa anterior, percorrendo o vetor nos dois sentidos e 
evitando percorrer as pontas (ou seja, valores já ordenados)
*/

#include <stdio.h>

int main()
{   
    int n, aux;
    scanf("%d", &n);
    
    int trocado = 1, inicio = 0, fim = n - 1;
    int vetor[n];

    // leitura do vetor
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    while (trocado) {
        trocado = 0;

        for (int i = inicio; i < fim; i++) {
            if (vetor[i] > vetor[i + 1]) {
                // inverte elementos de lugar
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
                trocado = 1;
            } 
        }

        if (!trocado) {
            break;
        }

        trocado = 0;

        fim--;

        for (int i = fim - i; i >= inicio; i--) {
            if (vetor[i] > vetor[i + 1]) {
                // inverte elementos de lugar
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
                trocado = 1;
            } 
        }

        inicio++;
    }

    // imprime vetor ordenado
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");

    return 0;
}