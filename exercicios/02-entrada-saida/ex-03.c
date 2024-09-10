/*
Ler um texto da entrada padrão e produzir o mesmo texto na saída
padrão, mas com as letras convertidas em maiúsculas. Sugestão: usar
a função getchar() para ler caracteres da entrada (até encontrar um EOF), 
a função putchar() para escrever caracteres na saída e uma estrutura switch
(ou uma tabela) para converter os caracteres.
Sugestão: em C, caracteres são tratados como números inteiros; consulte uma
tabela ASCII para ver seus valores respectivos. 
*/

#include <stdio.h>
#include <string.h>

int main() {
    int c;

    c = getchar();

    while (c != EOF) {
        if (c >= 97 && c <= 122) {
            c = c - 32;
        }

        putchar(c);
        c = getchar();
    }

    return(0);
}
