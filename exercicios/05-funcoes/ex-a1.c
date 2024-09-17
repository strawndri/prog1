/*
Passagem de funções em C para:

1. Escrever funções em C para:
    - calcular ab, com b inteiro e a e o retorno de tipo double.
    - trocar duas variáveis inteiras entre si.
    - comparar dois números inteiros a e b; a função retorna -1 se a<b, 0 se a=b e +1 se a>b.
    - retornar o maior valor em um vetor de inteiros.
*/

#include <stdio.h>

double multiplicar(double a, int b)
{
    return a * b;
}

void trocar_variaveis(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

int comparar_numeros(int a, int b)
{
    if (a < b){
        return -1;
    } else if (a > b) {
        return 1;
    } else {
        return 0;
    }
}

int max_vetor(int n, int v[n])
{
    int max = v[0];

    for (int i = 1; i < n; i++)
    {
        if (v[i] > max) {
            max = v[i];
        }
    }

    return max;
}

int main()
{   
    int a = 2, b = 5;
    int n = 5;
    int v[5] = {0, 2, 3, 9, -8};

    printf("Multplicação: %f\n", multiplicar(1.4567, 8));
    
    trocar_variaveis(&a, &b);
    printf("Números trocados: %d %d\n", a, b);

    printf("Comparação: %d\n", comparar_numeros(2, -3));
    printf("Maior do vetor: %d\n", max_vetor(n, v));

    return 0;
}