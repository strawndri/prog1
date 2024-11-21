#include "entidades.h"
#include "utils.h"
#include "mundo.h"

// Função para iniciar o mundo
void inicia_mundo(struct mundo *m)
{
  m->n_bases = N_BASES;
  m->n_herois = N_HEROIS;
  m->n_habilidades = N_HABILIDADES;
  m->n_missoes = N_MISSOES;
  m->tamanho_mundo.x = N_TAMANHO_MUNDO;
  m->tamanho_mundo.y = N_TAMANHO_MUNDO;
  m->relogio = T_INICIO;

  // Inicialização das bases
  for (int i = 0; i < m->n_bases; i++)
    m->bases[i] = cria_base(i);

  // Inicialização dos heróis
  for (int i = 0; i < m->n_herois; i++)
    m->herois[i] = cria_heroi(i);

  // Inicialização das missões
  for (int i = 0; i < m->n_missoes; i++)
    m->missoes[i] = cria_missao(i);
}