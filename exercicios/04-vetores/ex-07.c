// Ler duas matrizes, calcular e imprimir sua multiplicação

#include <stdio.h>

void ler_matriz(int lin, int col, int matriz[lin][col])
{   
    printf("Informe a matriz: \n");
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
}

int main()
{   
    int l1, c1, l2, c2;

    do {
        printf("Informe l1, c1, l2, c2 (c1 deve ser igual a l2):\n");
        scanf("%d %d %d %d", &l1, &c1, &l2, &c2);
    } while (c1 != l2);

    int matriz_A[l1][c1], matriz_B[l2][c2], matriz_C[l1][c2];

    ler_matriz(l1, c1, matriz_A);
    ler_matriz(l2, c2, matriz_B);

    for (int i = 0; i < l1; i++) {
        for (int j = 0; j < c2; j++) {
            matriz_C[i][j] = 0;
            for (int k = 0; k < l2; k++) {
                matriz_C[i][j] += matriz_A[i][k] * matriz_B[k][j];
            }
        }
    }

    printf("Resultado da multiplicação: \n");
    
    for (int i = 0; i < l1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", matriz_C[i][j]);
        }

        printf("\n");
    }

    return 0;
}