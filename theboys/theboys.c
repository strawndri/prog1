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

  // Laço de simulação

  // Destruição do mundo

  return 0;
}
