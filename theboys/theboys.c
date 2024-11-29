// programa principal do projeto "The Boys - 2024/2"
// Autor: Andrieli Luci Gonçalves, GRR 202449003

#include <stdlib.h>

#include "fprio.h"
#include "lista.h"
#include "mundo.h"

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

  // Eventos iniciais e simulação do mundo
  executa_eventos_iniciais(m, lef);
  executa_eventos(m, lef);

  // Destruição de tudo que o mundo contempla
  fprio_destroi(lef);
  destroi_mundo(m);
  free(m);

  return 0;
}
