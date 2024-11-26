#ifndef ENTIDADES
#define ENTIDADES

#include <stdbool.h>

#include "conjunto.h"
#include "fprio.h"
#include "utils.h"

#include "mundo.h"

struct heroi
{
  int id_heroi;
  struct cjto_t *habilidades;
  int paciencia;
  int velocidade;
  int experiencia;
  int id_base;
  bool morto; // false se estiver vivo; true se morreu em missão
};

struct base
{
  int id_base;
  int lotacao;
  struct cjto_t *presentes;
  struct lista_t *espera;
  struct coordenada local;
};

struct missao
{
  int id_missao;
  struct cjto_t *habilidades;
  int perigo;
  struct coordenada local;
  bool cumprida; // true se cumprida; false caso contrário
};

struct heroi cria_heroi(int id);

void destroi_heroi(struct heroi *h);

struct base cria_base(int id);

void destroi_base(struct base *b);

struct missao cria_missao(int id);

void destroi_missoes(struct missao *m);

#endif