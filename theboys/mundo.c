#include <stdio.h>

#include "mundo.h"
#include "entidades.h"
#include "utils.h"

#include "fprio.h"

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
  m->total_eventos = 0;

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

int encontra_prox_base(struct mundo *m, struct missao *mi, struct fprio_t *dists)
{
  int bmp = -1;
  struct cjto_t *total_habilidades = cjto_cria(m->n_habilidades);
  if (!total_habilidades)
    return -1;

  while (fprio_tamanho(dists) > 0)
  {
    int id_base;
    int prioridade;

    fprio_retira(dists, &id_base, &prioridade);

    // recria total_habilidades
    cjto_destroi(total_habilidades);
    total_habilidades = cjto_cria(m->n_habilidades);

    if (!total_habilidades)
      return -1; 

    for (int h = 0; h < m->n_herois; h++)
    {
      if (cjto_pertence(m->bases[id_base].presentes, h))
      {
        struct cjto_t *novo_total = cjto_uniao(total_habilidades, m->herois[h].habilidades);
        if (novo_total)
        {
          cjto_destroi(total_habilidades);
          total_habilidades = novo_total;  // atualiza para o novo conjunto
        }
      }
    }

    if (cjto_contem(total_habilidades, mi->habilidades))
    {
      bmp = id_base;
      break;
    }
  }

  cjto_destroi(total_habilidades);
  return bmp;
}
