/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* Retorna um número aleatório entre min e max, inclusive
 * (max - min + 1) gera um número entre 0 e (max - min)
 * Somando min, temos o deslocamento do resultado para o intervalo [min, max] 
*/
long aleat(long min, long max)
{
  return rand() % (max - min + 1) + min;
}

/* Máximo Divisor Comum entre a e b pelo método de Euclides */
long mdc(long a, long b)
{
  if (b == 0) {
    return a;
  }

  return mdc(b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
long mmc(long a, long b)
{
  return (a * b) / mdc(a, b);
}

/* Recebe um número racional e o simplifica */
struct racional simplifica_r(struct racional r)
{
  long resultado_mdc;
  long numerador, denominador;

  /* Verifica e retorna o racional se ele for inválido */
  if (!valido_r(r)) {
    return r;
  } 
  
  resultado_mdc = mdc(r.num, r.den);

  /* Simplifica o numerador e o denominador dividindo-os pelo MDC */
  numerador = r.num / resultado_mdc; 
  denominador = r.den / resultado_mdc; 
  
  /* Ajusta o sinal para garantir que o denominador seja positivo */
  if (denominador < 0) {
    numerador = -numerador;
    denominador = -denominador;
  }

  return cria_r(numerador, denominador);
}

/* implemente as demais funções de racional.h aqui */

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador)
{
  struct racional novo = {numerador, denominador};
  return novo;
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r(struct racional r)
{
  return r.den != 0; // Condição retorna diretamente os valores esperados (0 ou 1)
}

/* Retorna um número racional aleatório na forma simplificada */
struct racional sorteia_r(long min, long max)
{ 
  long numerador = aleat(min, max);
  long denominador = aleat(min, max);

  return simplifica_r(cria_r(numerador, denominador));
}

/* Imprime um racional r */
void imprime_r(struct racional r)
{
  struct racional numero_simplificado = simplifica_r(r);

  if (!valido_r(numero_simplificado)) {
    printf("NaN");
    /* O else-if a seguir resolve tais problemas: 
    * 1. Numerador igual a 0
    * 2. Denominador igual a 1
    * 3. Numerador e denominador iguais 
    * No caso do item 3, possivelmente ele cairá no item 2, já que anteriormente
    * aconteceu a simplificação do número racional, levando à situação 1/1
    */
  } else if (!numero_simplificado.num || numero_simplificado.den == 1) {
      printf("%ld", numero_simplificado.num);
  } else {
      printf("%ld/%ld", numero_simplificado.num, numero_simplificado.den);
  }
}