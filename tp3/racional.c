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

/* Máximo Divisor Comum entre a e b pelo método de Euclides */
long mdc(long a, long b)
{
  if (b == 0)
    return a;

  return mdc(b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
long mmc(long a, long b)
{
  return (a * b) / mdc(a, b);
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r(struct racional *r)
{
  long resultado_mdc;
  long numerador, denominador;

  /* Verifica e retorna o racional se ele for inválido */
  if (r == NULL || !invalido_r(*r))
    return 0;

  resultado_mdc = mdc(r->num, r->den);

  /* Simplifica o numerador e o denominador dividindo-os pelo MDC */
  numerador = r->num / resultado_mdc;
  denominador = r->den / resultado_mdc;

  /* Ajusta o sinal para garantir que o denominador seja positivo */
  if (denominador < 0)
  {
    numerador = -numerador;
    denominador = -denominador;
  }

  r->num = numerador;
  r->den = denominador;

  return 1;
}

/* Cria um número racional com o numerador e denominador indicados
 * e retorna um ponteiro que aponta para ele.
 * A memória para o número racional deve ser alocada dinamicamente
 * por esta função. Retorna NULL se não conseguiu alocar a memória. */
struct racional *cria_r(long numerador, long denominador)
{
  struct racional *novo = malloc(sizeof(struct racional));

  if (novo == NULL)
    return NULL;

  novo->num = numerador;
  novo->den = denominador;
}
