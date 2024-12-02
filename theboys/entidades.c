#include <stdio.h>

#include "conjunto.h"
#include "fprio.h"
#include "lista.h"
#include "utils.h"
#include "mundo.h"
#include "entidades.h"

// Funções do Herói -----------------------------------------------------------

struct heroi_t cria_heroi(int id)
{
  struct heroi_t h;

  h.id_heroi = id;
  h.id_base = -1;
  h.experiencia = 0;
  h.paciencia = aleat(0, 100);
  h.velocidade = aleat(50, 5000);
  h.morto = false;

  // Organização das habilidades do herói
  int qtd_hab_heroi = aleat(1, 3);
  h.habilidades = cjto_aleat(qtd_hab_heroi, N_HABILIDADES);

  return h;
}

// (!) não sei se precisa fazer algo a mais
void destroi_heroi(struct heroi_t *h)
{
  if (h->habilidades)
    cjto_destroi(h->habilidades);
}

// Funções da Base -----------------------------------------------------------

struct base_t cria_base(int id)
{
  struct base_t b;

  b.id_base = id;

  // Coordenadas
  b.local.x = aleat(0, N_TAMANHO_MUNDO - 1);
  b.local.y = aleat(0, N_TAMANHO_MUNDO - 1);

  b.espera_max = 0;
  b.missoes = 0;
  b.lotacao = aleat(3, 10);
  b.presentes = cjto_cria(N_HEROIS);
  b.espera = lista_cria();

  return b;
}

void destroi_base(struct base_t *b)
{
  if (b->presentes)
    cjto_destroi(b->presentes);

  if (b->espera)
    lista_destroi(b->espera);
}

// Funções da Missão ---------------------------------------------------------

struct missao_t cria_missao(int id)
{
  struct missao_t m;

  m.id_missao = id;
  m.local.x = aleat(0, N_TAMANHO_MUNDO - 1);
  m.local.y = aleat(0, N_TAMANHO_MUNDO - 1);

  // Organização das habilidades necessárias para a missão
  int qtd_hab_missao = aleat(3, 6);
  m.habilidades = cjto_aleat(qtd_hab_missao, N_HABILIDADES);
  m.perigo = aleat(0, 100);
  m.tentativas = 0;
  m.cumprida = false;

  return m;
}

void destroi_missao(struct missao_t *m)
{
  if (m->habilidades)
    cjto_destroi(m->habilidades);
}