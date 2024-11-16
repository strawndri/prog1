// programa principal do projeto "The Boys - 2024/2"
// Autor: Andrieli Luci Gonçalves, GRR 202449003

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
struct Coordenada
{
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
  bool morto; // false se estiver vivo; true se morreu em missão
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
  struct Coordenada *local;
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

// Funções do Herói -----------------------------------------------------------

void cria_heroi(struct Heroi heroi, int id)
{
  heroi.id_heroi = id;
  heroi.experiencia = 0;
  heroi.paciencia = aleat(0, 100);
  heroi.velocidade = aleat(50, 5000);
  heroi.morto = false;

  // Organização das habilidades do herói
  int qtd_hab_heroi = aleat(1, 3);
  heroi.habilidades = cjto_aleat(qtd_hab_heroi, N_HABILIDADES);
}

// não sei se precisa fazer algo a mais
void destroi_heroi(struct Heroi heroi, int id)
{
  cjto_destroi(heroi.habilidades);
}

// Funções da Base -----------------------------------------------------------

void cria_base(struct Base base, int id)
{
  base.id_base = id;

  // Coordenadas
  base.local->x = aleat(0, N_TAMANHO_MUNDO);
  base.local->y = aleat(0, N_TAMANHO_MUNDO);

  base.lotacao = aleat(3, 10);
  base.presentes = cjto_cria(base.lotacao);
  base.espera = fprio_cria();
}

void destroi_base(struct Base base, int id)
{
  cjto_destroi(base.presentes);
  cjto_destroi(base.espera);
}

// Funções da Missão ---------------------------------------------------------

void cria_missao(struct Missao missao, int id)
{
  missao.id_missao = id;
  missao.local->x = aleat(0, N_TAMANHO_MUNDO);
  missao.local->y = aleat(0, N_TAMANHO_MUNDO);

  // Organização das habilidades necessárias para a missão
  int qtd_hab_missao = aleat(6, 10);
  missao.habilidades = cjto_aleat(qtd_hab_missao, N_HABILIDADES);
  missao.perigo = aleat(0, 100);
}

void destroi_missoes(struct Missao missao, int id)
{
  cjto_destroi(missao.habilidades);
}

// Função para iniciar o mundo

void inicia_mundo(struct Mundo *mundo)
{
  mundo->n_bases = N_BASES;
  mundo->n_herois = N_HEROIS;
  mundo->n_habilidades = N_HABILIDADES;
  mundo->n_missoes = N_MISSOES;
  mundo->tamanho_mundo->x = N_TAMANHO_MUNDO;
  mundo->tamanho_mundo->y = N_TAMANHO_MUNDO;
  mundo->relogio = T_INICIO;

  // Inicialização dos heróis
  for (int i = 0; i < mundo->n_herois; i++)
  {
    cria_heroi(*mundo->herois, i);

    // evento de chegada 
  }

  // Inicialização das bases
  for (int i = 0; i < mundo->n_bases; i++)
  {
    cria_base(*mundo->bases, i);

  }

  // Inicialização das missões
  for (int i = 0; i < mundo->n_missoes; i++)
  {
    cria_missao(*mundo->missoes, i);

    // evento de missao agendada
  }
}

// programa principal
int main()
{
  // Iniciando o mundo
  struct Mundo mundo;

  inicializa_herois(mundo.herois);
  inicializa_herois(mundo.bases);
  inicializa_herois(mundo.missoes);

  // Criando a fila de eventos futuros
  struct fprio_t *lef;
  lef = fprio_cria();

  // Eventos iniciais

  // executar o laço de simulação

  // destruir o mundo

  return (0);
}
