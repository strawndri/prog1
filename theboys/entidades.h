#ifndef ENTIDADES
#define ENTIDADES

#include <stdbool.h>

#include "conjunto.h"
#include "fprio.h"
#include "utils.h"

#include "mundo.h"

struct heroi_t
{
  int id_heroi;
  struct cjto_t *habilidades;
  int paciencia;
  int velocidade;
  int experiencia;
  int id_base;
  bool morto; // false se estiver vivo; true se morreu em missão
};

struct base_t
{
  int id_base;
  int lotacao;
  int espera_max;
  int missoes;
  struct cjto_t *presentes;
  struct lista_t *espera;
  struct coordenadas_t local;
};

struct missao_t
{
  int id_missao;
  int tentativas;
  struct cjto_t *habilidades;
  int perigo;
  struct coordenadas_t local;
  bool cumprida; // true se cumprida; false caso contrário
};

struct heroi_t cria_heroi(int id);

void destroi_heroi(struct heroi_t *h);

struct base_t cria_base(int id);

void destroi_base(struct base_t *b);

struct missao_t cria_missao(int id);

void destroi_missao(struct missao_t *m);

#endif