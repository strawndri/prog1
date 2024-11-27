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
#include "utils.h"

int main()
{
  srand(1);

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

  return 0;
}
