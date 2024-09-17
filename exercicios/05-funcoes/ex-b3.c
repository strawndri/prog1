/*
Passagem de parâmetros vetoriais

Escreva um programa para transpor matrizes, com as seguintes funções:
    - le_matriz (matriz, M, N): ler uma matriz de MxN inteiros;
    - transpoe_matriz (matriz, M, N): transpor uma matriz;
    - escreve_matriz (matriz, M, N): imprimir uma matriz.
*/


#include <stdio.h>
#define M 3
#define N 2

void le_matriz(int m, int n, int matriz[m][n])
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
}

void transpoe_matriz(int m, int n, int matriz[m][n], int transposta[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            transposta[i][j] = matriz[j][i];
        }
    }
}

void escreve_matriz(int m, int n, int matriz[m][n])
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main()
{   
    int matriz[M][N];
    int transposta[N][M];

    le_matriz(M, N, matriz);
    transpoe_matriz(M, N, matriz, transposta);
    escreve_matriz(N, M, transposta);

    return 0;
}