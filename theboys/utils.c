#include <stdlib.h>
#include "utils.h"
#include "math.h"

// (max - min + 1) gera um número entre 0 e (max - min)
// Somando min, temos o deslocamento do resultado para o intervalo [min, max]
long aleat(long min, long max)
{
  return rand() % (max - min + 1) + min;
}

// c1: local atual
// c2: destino
// x e y representam as coordenadas horizontal e vertical destes locais
int calcula_distancia(struct coordenadas_t c1, struct coordenadas_t c2)
{
  return sqrt(((c2.x - c1.x) * (c2.x - c1.x)) + ((c2.y - c1.y) * (c2.y - c1.y)));
}
