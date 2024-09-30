/*
Passagem de parâmetros por referência

Escreva uma função int separa (float r, int *pi, float *pf) que separa um 
número real r em suas partes inteira (pi) e fracionária (pf). Por exemplo: 
37,543 ⇒ 37 e 0,543. A função retorna 1 se deu certo ou 0 se ocorreu algum erro.
*/

#include <stdio.h>

int separa(float r, int *pi, float *pf)
{   
    *pi = (int)r;
    *pf = r - *pi;
    
    return 1;
}

int main()
{   
    float r, pf;
    int pi;

    scanf("%f", &r);
    printf("%d\n", separa(r, &pi, &pf));
    return 0;
}
