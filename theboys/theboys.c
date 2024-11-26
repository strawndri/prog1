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
      chega(evento->tempo, &m->herois[evento->d1], &m->bases[evento->d2], lef);
      break;
    case ESPERA:
      espera(evento->tempo, &m->herois[evento->d1], &m->bases[evento->d2], lef);
      break;
    case DESISTE:
      desiste(m, evento->tempo, &m->herois[evento->d1], &m->bases[evento->d2], lef);
      break;
    case AVISA:
      avisa(evento->tempo, &m->bases[evento->d2], lef);
      break;
    case ENTRA:
      entra(evento->tempo, &m->herois[evento->d1], &m->bases[evento->d2], lef);
      break;
    case SAI:
      sai(m, evento->tempo, &m->herois[evento->d1], &m->bases[evento->d2], lef);
      break;
    case VIAJA:
      viaja(m, evento->tempo, &m->herois[evento->d1], &m->bases[evento->d2], lef);
      break;
    }
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
