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
  if (r == NULL || !valido_r(r))
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
  struct racional *novo = (struct racional *)malloc(sizeof(struct racional));

  if (novo == NULL)
    return NULL;

  novo->num = numerador;
  novo->den = denominador;

  return novo;
}

/* Libera a memória alocada para o racional apontado por r */
void destroi_r(struct racional *r)
{
  if (r != NULL)
    free(r);
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. Um racional
 * é inválido se o denominador for zero ou se ele não tiver sido alocado. */
int valido_r(struct racional *r)
{
  return (r->den != 0 && r != NULL);
}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve estar na forma simplificada;
   - não use espacos em branco e não mude de linha;
   - o formato de saída deve ser "num/den", a menos dos casos abaixo;
     - se o ponteiro for nulo, imprime a mensagem "NULL";
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal é impresso antes do número;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r(struct racional *r)
{
  if (r == NULL)
  {
    printf("NULL");
    return;
  }

  simplifica_r(r);

  if (!valido_r(r))
    printf("NaN");
  /* O else-if a seguir resolve tais problemas:
   * 1. Numerador igual a 0
   * 2. Denominador igual a 1
   * 3. Numerador e denominador iguais
   * No caso do item 3, possivelmente ele cairá no item 2, já que anteriormente
   * aconteceu a simplificação do número racional, levando à situação 1/1
   */
  else if (!r->num || r->den == 1)
    printf("%ld", r->num);
  else
    printf("%ld/%ld", r->num, r->den);
}

/* Compara dois números racionais r1 e r2.
 * Retorna -2 se r1 ou r2 for inválido ou se o respectivo ponteiro for nulo.
 * Retorna -1 se r1 < r2; 0 se r1 = r2; 1 se r1 > r2.
 * Atenção: faça a comparação normalizando os denominadores pelo MMC.
 * Fazer a comparação baseado na divisão do numerador pelo denominador
 * pode gerar erro de arredondamento e falsear o resultado. */
int compara_r(struct racional *r1, struct racional *r2)
{
  long resultado_mmc, n1, n2;

  if (!valido_r(r1) || !valido_r(r2) || r1 == NULL || r2 == NULL)
    return -2;

  resultado_mmc = mmc(r1->den, r2->den);

  n1 = resultado_mmc * r1->num / r1->den;
  n2 = resultado_mmc * r2->num / r2->den;

  if (n1 < n2)
    return -1;
  else if (n1 > n2)
    return 1;
  else
    return 0;
}

/* Retorna a soma dos racionais r1 e r2 no parâmetro *r3 */
int soma_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  long resultado_mmc, numerador;

  /* Verifica se r1 ou r2 são inválidos ou r3 é um ponteiro nulo */
  if (!valido_r(r1) || !valido_r(r2) || r3 == NULL)
    return 0;

  resultado_mmc = mmc(r1->den, r2->den);
  numerador = ((resultado_mmc * r1->num / r1->den) +
               (resultado_mmc * r2->num / r2->den));

  r3->num = numerador;
  r3->den = resultado_mmc;

  return 1;
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3 */
int subtrai_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  long resultado_mmc, numerador;

  /* Verifica se r1 ou r2 são inválidos ou r3 é um ponteiro nulo */
  if (!valido_r(r1) || !valido_r(r2) || r3 == NULL)
    return 0;

  resultado_mmc = mmc(r1->den, r2->den);
  numerador = ((resultado_mmc * r1->num / r1->den) -
               (resultado_mmc * r2->num / r2->den));

  r3->num = numerador;
  r3->den = resultado_mmc;

  return 1;
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3 */
int multiplica_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  /* Verifica se r1 ou r2 são inválidos ou r3 é um ponteiro nulo */
  if (!valido_r(r1) || !valido_r(r2) || r3 == NULL)
    return 0;

  r3->num = r1->num * r2->num;
  r3->den = r1->den * r2->den;

  return 1;
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3 */
int divide_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  /* Verifica se r1 ou r2 são inválidos
   * ou o numerador de r2 é zero
   * ou r3 é um ponteiro nulo
   */
  if (!valido_r(r1) || !valido_r(r2) || !r2->num || r3 == NULL)
    return 0;

  r3->num = r1->num * r2->den;
  r3->den = r1->den * r2->num;

  return 1;
}