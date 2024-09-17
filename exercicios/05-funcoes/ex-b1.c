/*
Passagem de parâmetros vetoriais

Escrever um programa em C para somar dois vetores de inteiros. 
Crie funções separadas para 
    a) ler um vetor; 
    b) somar dois vetores; 
    c) imprimir um vetor.
*/

#include <stdio.h>
#define N 5

void ler_vetor(int n, int v[])
{
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
}

void somar_vetores(int n, int v1[], int v2[], int v3[])
{
    for (int i = 0; i < n; i++) {
        v3[i] = v1[i] + v2[i];
    }
}

void imprimir_vetor(int n, int v[])
{
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }

    printf("\n");
}

int main()
{   
    int v1[N], v2[N], v3[N];

    ler_vetor(N, v1);
    ler_vetor(N, v2);
    somar_vetores(N, v1, v2, v3);
    imprimir_vetor(N, v3);

    return 0;
}