/*
Escreva um programa que imprima as raízes quadradas e os logaritmos
(base 10) de todos os números inteiros entre 1 e 1000. Os valores 
devem ser impressos com 4 casas decimais, da seguinte forma:

     1   1.0000  0.0000
   ...
   500  22.3606  2.6989
   ...
   999  31.6069  2.9999
  1000  31.6227  3.0000
*/

#include <stdio.h>
#include <math.h>

int main() {
    int n = 1000;

    for (int i = 1; i <= n; i++) {
        printf("%d %.4f %.4f\n", i, sqrt(i), log10(i));
    }

    return (0);
}