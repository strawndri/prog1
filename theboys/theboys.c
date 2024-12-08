// Programa principal do projeto "The Boys - 2024/2"
// Autora: Andrieli Luci Gonçalves, GRR 202449003
// Dez 2024

#include <stdlib.h>
#include "fprio.h"
#include "mundo.h"

int main()
{
  srand(0);

  // Inicialização do mundo
  struct mundo_t *m;
  m = malloc(sizeof(struct mundo_t));

  if (!m)
    return -1;

  cria_mundo(m);

  // Criação da fila de eventos futuros
  struct fprio_t *lef;
  lef = fprio_cria();

  if (!lef)
  {
    destroi_mundo(m);
    return -1;
  }

  // Eventos iniciais e simulação do mundo
  agenda_eventos_iniciais(m, lef);
  executa_eventos(m, lef);

  // Destruição de tudo que o mundo contempla
  fprio_destroi(lef);
  destroi_mundo(m);

  return 0;
}
