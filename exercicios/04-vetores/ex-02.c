/*
Cálculo da média:

- ler um número N e um vetor de N inteiros
- calcular a média dos valores lidos
- imprimir essa média
- imprimir os elementos do vetor que forem maiores que a média calculada
*/

/*
Leitura e escrita:

- Ler um número N e um vetor de N inteiros
- Escrever o vetor na saída no formato [n1 n2 n3 …]
- Inverter o vetor e imprimi-lo: [… n3 n2 n1] (inverter antes de imprimir)
*/

#include <stdio.h>

int main()
{   
    int n;
    int soma = 0;
    float media;

    scanf("%d", &n);
    int vetor[n];

    // leitura do vetor
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
        soma += vetor[i];
    }

    media = soma/(float)n;

    // imprime elementos maiores que a média
    for (int i = 0; i < n; i++) {
        if (vetor[i] > media) {
            printf("%d ", vetor[i]);
        }
    }

    printf("\n");
    
    return 0;
}