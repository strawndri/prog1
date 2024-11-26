#include <stdio.h>

#include "mundo.h"
#include "entidades.h"
#include "utils.h"

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

// (!) procurar outro algoritmo mais eficiente (heap)
int encontra_prox_base(struct mundo *m, struct missao *mi, int dists[])
{
  // (!) apenas teste, trocar depois
  int menor = 100000;
  int bmp = -1;
  int cumpre_missao = 0;
  struct cjto_t *total_habilidades;

  for (int i = 0; i < m->n_bases; i++)
  { 

    for (int h = 0; h < m->n_herois; h++)
    {
      if (cjto_pertence(m->bases[i].presentes, h))
        total_habilidades = cjto_uniao(total_habilidades, m->herois[h].habilidades);

      if (cjto_contem(total_habilidades, mi->habilidades))
        cumpre_missao = 1;
    }

    if (dists[i] < menor && cumpre_missao)
    {
      menor = dists[i];
      bmp = i;
    }
  }

  return bmp;
}