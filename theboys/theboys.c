// programa principal do projeto "The Boys - 2024/2"
// Autor: Andrieli Luci Gonçalves, GRR 202449003

#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"
#include "fprio.h"
#include "lista.h"
#include "mundo.h"
#include "entidades.h"
#include "eventos.h"

int executa_eventos(struct mundo *m, struct fprio_t *lef)
{
  struct evento_t *evento;
  int tipo, prio;

  while (fprio_tamanho(lef) > 0)
  {
    evento = fprio_retira(lef, &tipo, &prio);
    switch (evento->tipo)
    {
    case CHEGA:

      // (!) tenho a sensação de estar violando algo
      int resultado = chega(
          m,
          evento->tempo,
          &m->herois[evento->d1],
          &m->bases[evento->d2],
          lef);

      if (resultado)
        printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA",
               evento->tempo,
               evento->d1,
               evento->d2,
               cjto_card(m->bases[evento->d2].presentes),
               m->bases[evento->d2].lotacao);
      else
        printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE",
               evento->tempo,
               evento->d1,
               evento->d2,
               cjto_card(m->bases[evento->d2].presentes),
               m->bases[evento->d2].lotacao);
      break;
    case ESPERA:
      printf("%6d: ESPERA HEROI %2d BASE %d (%2d)",
             evento->tempo,
             evento->d1,
             evento->d2,
             cjto_card(m->bases[evento->d2].presentes));
    }

    printf("\n");
  }

  return 0;
}

int main()
{
  srand(0);

  // Inicialização do mundo
  struct mundo *m;
  m = malloc(sizeof(struct mundo));

  if (!m)
    return -1;

  inicia_mundo(m);

  // Criação da fila de eventos futuros
  struct fprio_t *lef;
  lef = fprio_cria();
  executa_eventos_iniciais(m, lef);
  executa_eventos(m, lef);

  // fprio_imprime(lef);
  // for (int i = 0; i < m->n_herois; i++) {
  //   printf("%d: %d - %d \n", i, m->herois[i].id_heroi, m->herois[i].id_base);
  // }
  return 0;
}
