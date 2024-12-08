#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "fprio.h"
#include "lista.h"
#include "utils.h"
#include "mundo.h"
#include "entidades.h"

// Funções do Herói -----------------------------------------------------------

struct heroi_t *cria_heroi(int id)
{
  struct heroi_t *h;

  h = malloc(sizeof(struct heroi_t));
  if (!h)
    return NULL;

  h->id_heroi = id;
  h->id_base = -1;
  h->experiencia = 0;
  h->paciencia = aleat(0, 100);
  h->velocidade = aleat(50, 5000);
  h->morto = false;

  // Organização das habilidades do herói
  int qtd_hab_heroi = aleat(1, 3);
  h->habilidades = cjto_aleat(qtd_hab_heroi, N_HABILIDADES);

  return h;
}

struct heroi_t *destroi_heroi(struct heroi_t *h)
{
  if (!h)
    return NULL;

  if (h->habilidades)
    cjto_destroi(h->habilidades);

  free(h);

  return NULL;
}

// Funções da Base -----------------------------------------------------------

struct base_t *cria_base(int id)
{
  struct base_t *b;

  b = malloc(sizeof(struct base_t));
  if (!b)
    return NULL;

  b->id_base = id;

  // Coordenadas
  b->local.x = aleat(0, N_TAMANHO_MUNDO - 1);
  b->local.y = aleat(0, N_TAMANHO_MUNDO - 1);

  b->espera_max = 0;
  b->missoes = 0;
  b->lotacao = aleat(3, 10);
  b->presentes = cjto_cria(N_HEROIS);
  b->espera = lista_cria();

  return b;
}

struct base_t *destroi_base(struct base_t *b)
{
  if (!b)
    return NULL;

  if (b->presentes)
    cjto_destroi(b->presentes);

  if (b->espera)
    lista_destroi(b->espera);

  free(b);

  return NULL;
}

// Funções da Missão ---------------------------------------------------------

struct missao_t *cria_missao(int id)
{
  struct missao_t *mi;

  mi = malloc(sizeof(struct missao_t));
  if (!mi)
    return NULL;

  mi->id_missao = id;
  mi->local.x = aleat(0, N_TAMANHO_MUNDO - 1);
  mi->local.y = aleat(0, N_TAMANHO_MUNDO - 1);

  // Organização das habilidades necessárias para a missão
  int qtd_hab_missao = aleat(3, 6);
  mi->habilidades = cjto_aleat(qtd_hab_missao, N_HABILIDADES);
  mi->perigo = aleat(0, 100);
  mi->tentativas = 0;
  mi->cumprida = false;

  return mi;
}

struct missao_t *destroi_missao(struct missao_t *mi)
{
  if (!mi)
    return NULL;

  if (mi->habilidades)
    cjto_destroi(mi->habilidades);

  free(mi);

  return NULL;
}