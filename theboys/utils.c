#include <stdlib.h>
#include "utils.h"
#include "math.h"

// Retorna um número aleatório entre min e max, inclusive
// (max - min + 1) gera um número entre 0 e (max - min)
// Somando min, temos o deslocamento do resultado para o intervalo [min, max]
long aleat(long min, long max)
{
  return rand() % (max - min + 1) + min;
}

float calcula_distancia(struct coordenada c1, struct coordenada c2)
{
  return sqrt(((c2.x - c1.x) * (c2.x - c1.x)) + ((c2.y - c1.y) * (c2.y - c1.y)));
}