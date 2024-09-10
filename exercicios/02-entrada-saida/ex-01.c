/*
Ler um inteiro N e uma sequência de N inteiros, gerando na saída o 
valor de N, os valores máximo e mínimo observados (inteiros) e a média
(real) dos N valores lidos.
*/

#include <stdio.h>

int main() {
    int n, m, soma = 0, min, max;
    float media;

    scanf("%d", &n);

    if (n > 0) {

        scanf("%d", &m);
        min = max = m;
        soma += m;

        for (int i = 1; i < n; i++) {
            scanf("%d", &m);

            if (m < min) 
                min = m;
            
            if (m > max)
                max = m;

            soma += m;
        }

        media = (float)soma / n; // convertendo a soma em float

        printf("N = %d, Min = %d, Max = %d, Média = %.2f", n, min, max, media); 
    } else {
        printf("O número de elementos é menor ou igual a zeron\n");
    }

    return(0);
}