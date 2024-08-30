/* 
Se multiplicarmos 37 por alguns números, obteremos números cujos 
algarismos, quando somados, resultam no mesmo número que foi multiplicado
pelo 37. Por exemplo, se tomarmos o número 15, multiplicando-o por 37,
obtemos 555. Somando-se 5 + 5 + 5 resulta em 15.
Faça um programa em C que leia um número inteiro positivo do teclado,
calcule o resultado da multiplicação por 37, some os algarismos do resultado,
compare essa soma com o número lido e imprima ”SIM”se há coincidência
ou ”NAO”se não há coincidência.
*/

#include <stdio.h>

int main()
{
    int n, mult_37, soma = 0;
    scanf("%d", &n);

    mult_37 = n * 37;

    while (mult_37 != 0) {
        soma += mult_37 % 10;
        mult_37 = mult_37 / 10;
    }

    if (soma == n) {
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }

    return 0;
}