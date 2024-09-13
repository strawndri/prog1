/*
Leitura e escrita:

- Ler um número N e um vetor de N inteiros
- Escrever o vetor na saída no formato [n1 n2 n3 …]
- Inverter o vetor e imprimi-lo: [… n3 n2 n1] (inverter antes de imprimir)
*/

#include <stdio.h>

void imprime_vetor(int tam, int *vetor)
{
printf("[");
    for (int i = 0; i < tam; i++) {
        if (i == (tam - 1)) {
            printf("%d", vetor[i]);
        } else {
            printf("%d ", vetor[i]);
        }
    }
printf("]\n");
}

int main()
{   
    int n;
    scanf("%d", &n);

    int vetor[n];
    int vetor_invertido[n];

    // leitura do vetor
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    imprime_vetor(n, vetor);

    // cria vetor invertido
    for (int i = 0; i < n; i++) {
        vetor_invertido[i] = vetor[n - i - 1];
    }

    imprime_vetor(n, vetor_invertido);
    
    return 0;
}