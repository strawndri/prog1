#include <stdio.h>
#include <stdlib.h>

#include "mundo.h"
#include "eventos.h"
#include "entidades.h"
#include "utils.h"

#include "fprio.h"

// Função para iniciar o mundo
void inicia_mundo(struct mundo_t *m)
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

// Função para realizar os eventos iniciais
void executa_eventos_iniciais(struct mundo_t *m, struct fprio_t *lef)
{
  // Evento inicial (herói)
  for (int i = 0; i < m->n_herois; i++)
  {
    int base = aleat(0, m->n_bases - 1); // id da base
    int tempo = aleat(0, 4320);

    struct evento_t *evento = cria_evento(tempo, CHEGA, i, base);
    int status_fprio = fprio_insere(lef, evento, CHEGA, tempo);

    if (status_fprio < 0)
      return;
  }

  // Evento inicial (missão)
  for (int i = 0; i < m->n_missoes; i++)
  {
    int tempo = aleat(0, T_FIM_DO_MUNDO);

    struct evento_t *evento = cria_evento(tempo, MISSAO, i, -1);
    int status_fprio = fprio_insere(lef, evento, MISSAO, tempo);

    if (status_fprio < 0)
      return;
  }

  // Agendando o fim do mundo
  int tempo = T_FIM_DO_MUNDO;
  struct evento_t *evento = cria_evento(tempo, FIM, 0, 0);
  int status_fprio = fprio_insere(lef, evento, FIM, tempo);

  if (status_fprio < 0)
    return;
}

int executa_eventos(struct mundo_t *m, struct fprio_t *lef)
{
  struct evento_t *evento;
  int tipo, prio;

  while (fprio_tamanho(lef) > 0 && m->relogio < T_FIM_DO_MUNDO)
  {
    evento = fprio_retira(lef, &tipo, &prio);

    if (!evento)
      return -1;

    m->relogio = evento->tempo;
    m->total_eventos++;

    // printf("----> %d %d %d\n", evento->tipo, evento->d1, evento->d2);

    switch (evento->tipo)
    {
    case CHEGA:
      chega(m, evento, lef);
      break;
    case ESPERA:
      espera(m, evento, lef);
      break;
    case DESISTE:
      desiste(m, evento, lef);
      break;
    case AVISA:
      avisa(m, evento, lef);
      break;
    case ENTRA:
      entra(m, evento, lef);
      break;
    case SAI:
      sai(m, evento, lef);
      break;
    case VIAJA:
      viaja(m, evento, lef);
      break;
    case MORRE:
      morre(m, evento, lef);
      break;
    case MISSAO:
      missao(m, evento, lef);
      break;
    case FIM:
      fim(m, evento);
      break;
    }
    
    if (evento)
      free(evento);
  }
  
  while (fprio_tamanho(lef) > 0)
  {
    evento = fprio_retira(lef, &tipo, &prio);
    if (evento)
      free(evento);
  }

  return 0;
}

int encontra_prox_base(struct mundo_t *m, struct missao_t *mi, struct fprio_t *dists)
{
  int bmp = -1;
  int id_base, dist;
  struct cjto_t *total_habilidades, *novo_total;

  while (fprio_tamanho(dists) > 0 && bmp < 0)
  {
    id_base = -1;
    dist = 1;

    // Cria e verifica se o conjunto é válido
    total_habilidades = cjto_cria(m->n_habilidades);
    if (!total_habilidades)
      return -1;

    fprio_retira(dists, &id_base, &dist);

    printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", m->relogio, mi->id_missao, id_base, dist);
    cjto_imprime(m->bases[id_base].presentes);
    printf(" ]\n");

    for (int h = 0; h < m->n_herois; h++)
    {
      if (cjto_pertence(m->bases[id_base].presentes, h))
      {
        printf("%6d: MISSAO %d HAB HEROI %2d: [ ", m->relogio, mi->id_missao, h);
        cjto_imprime(m->herois[h].habilidades);
        printf(" ]\n");

        novo_total = cjto_uniao(total_habilidades, m->herois[h].habilidades);
        if (novo_total)
        {
          cjto_destroi(total_habilidades);
          total_habilidades = novo_total; // Atualiza para o novo conjunto
        }
      }
    }

    printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", m->relogio, mi->id_missao, id_base);
    cjto_imprime(total_habilidades);
    printf(" ]\n");

    if (cjto_contem(total_habilidades, mi->habilidades))
      bmp = id_base;

    cjto_destroi(total_habilidades);
  }

  return bmp;
}

void destroi_mundo(struct mundo_t *m)
{
  for (int i = 0; i < m->n_bases; i++)
    destroi_base(&m->bases[i]);

  for (int i = 0; i < m->n_herois; i++)
    destroi_heroi(&m->herois[i]);

  for (int i = 0; i < m->n_missoes; i++)
    destroi_missao(&m->missoes[i]);
}
