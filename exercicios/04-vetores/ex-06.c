// Ler uma matriz, calcular e imprimir sua transposta

#include <stdio.h>
#define TAMLIN 2
#define TAMCOL 3

int main()
{   
    int matriz [TAMLIN][TAMCOL], transposta[TAMCOL][TAMLIN];

    for (int i = 0; i < TAMLIN; i++) {
        for (int j = 0; j < TAMCOL; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    for (int i = 0; i < TAMCOL; i++) {
        for (int j = 0; j < TAMLIN; j++) {
            transposta[i][j] = matriz[j][i];
        }
    }

    for (int i = 0; i < TAMCOL; i++) {
        for (int j = 0; j < TAMLIN; j++) {
            printf("%d ", transposta[i][j]);
        }

        printf("\n");
    }

    return 0;
}