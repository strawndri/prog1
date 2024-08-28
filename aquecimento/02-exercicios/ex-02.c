/*
Imprimir a seguinte sequência de números, até N=10000:

    1     2     3     4     5     6     7     8
00001 00002 00003 00004 00005 00006 00007 00008
    9    10    11    12    13    14    15    16
00009 00010 00011 00012 00013 00014 00015 00016
...
*/

#include <stdio.h>

int main() {
    int n = 1000;

    for (int i = 1; i <= n; i++) {
        printf("%05d\n", i);
    }

    return(0);
}