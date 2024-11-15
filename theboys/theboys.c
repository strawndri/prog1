// programa principal do projeto "The Boys - 2024/2"
// Autor: Andrieli Luci Gonçalves, GRR 202449003

#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"
#include "fprio.h"
#include "lista.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 5
#define N_MISSOES T_FIM_DO_MUNDO / 10

// Estrutura que implementa um par de valores (x, y), representando
// a coordenada de uma localização
struct Coordenada {
  int x; // Coordenada horizontal (eixo x)
  int y; // Coordenada vertical (eixo y)
};

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
  struct Coordenada *local;
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

  struct Coordenada *tamanho_mundo;
  int relogio;
};

// Retorna um número aleatório entre min e max, inclusive
// (max - min + 1) gera um número entre 0 e (max - min)
// Somando min, temos o deslocamento do resultado para o intervalo [min, max] 
long aleat(long min, long max)
{
  return rand() % (max - min + 1) + min;
}

void inicializa_herois(struct Heroi herois[])
{
  for (int i = 0; i < N_HEROIS; i++) {
    herois[i].id_heroi = i;
    herois[i].experiencia = 0;
    herois[i].paciencia = aleat(0, 100);
    herois[i].velocidade = aleat(50, 5000);

    // Organização das habilidades do herói
    int qtd_hab_heroi = aleat(1, N_HABILIDADES);
    herois[i].habilidades = cjto_aleat(qtd_hab_heroi, N_HABILIDADES);
  }
}

// programa principal
int main()
{
  // iniciar o mundo

  // executar o laço de simulação

  // destruir o mundo

  return (0);
}
