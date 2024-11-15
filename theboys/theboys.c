// programa principal do projeto "The Boys - 2024/2"
// Autor: Andrieli Luci Gonçalves, GRR 202449003

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "lista.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 5
#define N_MISSOES T_FIM_DO_MUNDO / 10

struct Heroi
{
  int id_heroi;
  struct cjto_t *habilidades;
  int paciencia;
  int velocidade;
  int experiencia;
  int id_base;
};

struct Base
{
  int id_base;
  int lotacao;
  struct cjto_t *presentes;
  struct fprio_t *espera;
  struct coordenada_t *local; // criar struct
};

struct Missao
{
  int id_missao;
  struct cjto_t *habilidades;
  int perigo;
  struct coordenada_t *local;
};

struct Mundo
{
  int n_herois;
  struct Heroi herois[N_HEROIS];

  int n_bases;
  struct Base bases[N_BASES];

  int n_missoes;
  struct Missao missoes[N_MISSOES];

  int n_habilidades;

  struct coordenada_t *tamanho_mundo;
  int relogio;
};

// programa principal
int main()
{
  // iniciar o mundo

  // executar o laço de simulação

  // destruir o mundo

  return (0);
}
