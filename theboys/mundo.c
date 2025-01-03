#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "utils.h"
#include "mundo.h"
#include "eventos.h"
#include "entidades.h"

// Função para criar o mundo
struct mundo_t *cria_mundo()
{
  struct mundo_t *m;

  // Aloca struct referente ao mundo
  m = malloc(sizeof(struct mundo_t));
  if (!m)
    return NULL;

  m->n_bases = N_BASES;
  m->n_herois = N_HEROIS;
  m->n_habilidades = N_HABILIDADES;
  m->n_missoes = N_MISSOES;
  m->tamanho_mundo.x = N_TAMANHO_MUNDO;
  m->tamanho_mundo.y = N_TAMANHO_MUNDO;
  m->relogio = T_INICIO;
  m->total_eventos = 0;

  // Cria um vetor de structs para as bases
  for (int i = 0; i < m->n_bases; i++)
  {
    m->bases[i] = cria_base(i);

    // Se a base for inválida, libera o mundo
    if (!m->bases[i])
    {
      destroi_mundo(m);
      return NULL;
    }
  }

  // Cria um vetor de structs para os heróis
  for (int i = 0; i < m->n_herois; i++)
  {
    m->herois[i] = cria_heroi(i);

    // Se o herói for inválido, libera o mundo
    if (!m->herois[i])
    {
      destroi_mundo(m);
      return NULL;
    }
  }

  // Cria um vetor de structs para as missoes
  for (int i = 0; i < m->n_missoes; i++)
  {
    m->missoes[i] = cria_missao(i);

    // Se a missão for inválida, libera o mundo
    if (!m->missoes[i])
    {
      destroi_mundo(m);
      return NULL;
    }
  }

  return m;
}

// Função para realizar os eventos iniciais
void agenda_eventos_iniciais(struct mundo_t *m, struct fprio_t *lef)
{
  int base, tempo, status_fprio;
  struct evento_t *evento;

  // Evento inicial do heróis (chegar às bases)
  for (int i = 0; i < m->n_herois; i++)
  {
    base = aleat(0, m->n_bases - 1); // id da base
    tempo = aleat(0, 4320);

    evento = cria_evento(tempo, CHEGA, i, base);

    // Insere evento na LEF e verifica se deu certo
    status_fprio = fprio_insere(lef, evento, CHEGA, tempo);
    if (status_fprio < 0)
      return;
  }

  // Evento inicial das missões
  for (int i = 0; i < m->n_missoes; i++)
  {
    tempo = aleat(0, T_FIM_DO_MUNDO);

    evento = cria_evento(tempo, MISSAO, i, -1);

    // Insere evento na LEF e verifica se deu certo
    status_fprio = fprio_insere(lef, evento, MISSAO, tempo);
    if (status_fprio < 0)
      return;
  }

  // Agenda o fim do mundo
  tempo = T_FIM_DO_MUNDO;
  evento = cria_evento(tempo, FIM, -1, -1);
  status_fprio = fprio_insere(lef, evento, FIM, tempo);

  if (status_fprio < 0)
    return;
}

// Função para executar os eventos da simulação
void executa_eventos(struct mundo_t *m, struct fprio_t *lef)
{
  struct evento_t *evento;
  int tipo, prio;

  while (m->relogio < T_FIM_DO_MUNDO)
  {
    evento = fprio_retira(lef, &tipo, &prio);

    // Verifica se o evento é válido
    if (!evento)
      return;

    // Atualiza o tempo e os eventos processados
    m->relogio = evento->tempo;
    m->total_eventos++;

    switch (evento->tipo)
    {
    case CHEGA:
      trata_ev_chega(m, evento, lef);
      break;
    case ESPERA:
      trata_ev_espera(m, evento, lef);
      break;
    case DESISTE:
      trata_ev_desiste(m, evento, lef);
      break;
    case AVISA:
      trata_ev_avisa(m, evento, lef);
      break;
    case ENTRA:
      trata_ev_entra(m, evento, lef);
      break;
    case SAI:
      trata_ev_sai(m, evento, lef);
      break;
    case VIAJA:
      trata_ev_viaja(m, evento, lef);
      break;
    case MORRE:
      trata_ev_morre(m, evento, lef);
      break;
    case MISSAO:
      trata_ev_missao(m, evento, lef);
      break;
    case FIM:
      trata_ev_fim(m, evento);
      break;
    }

    // Libera o evento atual
    free(evento);
  }

  // Evita que a LEF permaneça com eventos agendados após o fim do mundo
  while (fprio_tamanho(lef) > 0)
  {
    evento = fprio_retira(lef, &tipo, &prio);
    if (evento)
      free(evento);
  }
}

// Função para encontrar a base mais próxima (BMP)
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
    cjto_imprime(m->bases[id_base]->presentes);
    printf(" ]\n");

    for (int h = 0; h < m->n_herois; h++)
    {
      if (cjto_pertence(m->bases[id_base]->presentes, h))
      {
        printf("%6d: MISSAO %d HAB HEROI %2d: [ ", m->relogio, mi->id_missao, h);
        cjto_imprime(m->herois[h]->habilidades);
        printf(" ]\n");

        novo_total = cjto_uniao(total_habilidades, m->herois[h]->habilidades);
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

    // Verifica se o conjunto de habilidades da função contempla os da missão
    if (cjto_contem(total_habilidades, mi->habilidades))
      bmp = id_base;

    cjto_destroi(total_habilidades);
  }

  return bmp;
}

// Função para destruir bases, heróis e missões
struct mundo_t *destroi_mundo(struct mundo_t *m)
{ 
  if (!m)
    return NULL ;

  for (int i = 0; i < m->n_bases; i++)
    destroi_base(m->bases[i]);

  for (int i = 0; i < m->n_herois; i++)
    destroi_heroi(m->herois[i]);

  for (int i = 0; i < m->n_missoes; i++)
    destroi_missao(m->missoes[i]);

  free(m);
  
  return NULL;
}
