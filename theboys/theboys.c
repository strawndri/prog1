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

// Implementação das estruturas que definem os eventos ------------------------

// Categorização dos eventos:

// ev_heroi_base
//  - 1: CHEGA
//  - 2: ESPERA
//  - 3: DESISTE
//  - 4: ENTRA
//  - 5: SAI
//  - 6: VIAJA
//  - 8: MORRE

// ev_base
//  - 9: AVISA

// ev_missao
//  - 10: MISSAO

// fim do mundo (sem estrutura)
//  - 11: FIM

struct ev_heroi_base
{
  int id_heroi;
  int id_base;
};

struct ev_base
{
  int id_base;
};

struct ev_missao
{
  int id_missao;
};

// Estrutura que implementa um par de valores (x, y), representando
// a coordenada de uma localização
struct coordenada
{
  int x; // Coordenada horizontal (eixo x)
  int y; // Coordenada vertical (eixo y)
};

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
  struct fprio_t *espera;
  struct coordenada local;
};

struct missao
{
  int id_missao;
  struct cjto_t *habilidades;
  int perigo;
  struct coordenada local;
};

struct mundo
{
  int n_herois;
  struct heroi herois[N_HEROIS];

  int n_bases;
  struct base bases[N_BASES];

  int n_missoes;
  struct missao missoes[N_MISSOES];

  int n_habilidades;

  struct coordenada tamanho_mundo;
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

struct heroi cria_heroi(int id)
{ 
  struct heroi h;

  h.id_heroi = id;
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
void destroi_heroi(struct heroi *h)
{
  if (h->habilidades)
    cjto_destroi(h->habilidades);
}

// Funções da Base -----------------------------------------------------------

struct base cria_base(int id)
{ 
  struct base b;

  b.id_base = id;

  // Coordenadas
  b.local.x = aleat(0, N_TAMANHO_MUNDO);
  b.local.y = aleat(0, N_TAMANHO_MUNDO);

  b.lotacao = aleat(3, 10);
  b.presentes = cjto_cria(b.lotacao);
  b.espera = fprio_cria();

  return b;
}

void destroi_base(struct base *b)
{
  if (b->presentes)
    cjto_destroi(b->presentes);
  
  if (b->espera)
    fprio_destroi(b->espera);
}

// Funções da Missão ---------------------------------------------------------

struct missao cria_missao(int id)
{ 
  struct missao m;
  
  m.id_missao = id;
  m.local.x = aleat(0, N_TAMANHO_MUNDO);
  m.local.y = aleat(0, N_TAMANHO_MUNDO);

  // Organização das habilidades necessárias para a missão
  int qtd_hab_missao = aleat(6, 10);
  m.habilidades = cjto_aleat(qtd_hab_missao, N_HABILIDADES);
  m.perigo = aleat(0, 100);

  return m;
}

void destroi_missoes(struct missao *m)
{
  if (m->habilidades)
    cjto_destroi(m->habilidades);
}

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
void executa_eventos_iniciais(struct mundo *m, struct fprio_t *lef)
{
  // Evento inicial (herói)
  for (int i = 0; i < m->n_herois; i++)
  {
    int base = aleat(0, m->n_bases - 1);
    int tempo = aleat(0, 4320);

    // (!): talvez declarar uma função de criação de evento
    struct ev_heroi_base *evento;
    evento = malloc(sizeof(struct ev_heroi_base));

    if (!evento)
      return;

    evento->id_heroi = i;
    evento->id_base = base;

    fprio_insere(lef, evento, 1, tempo);
  }

  // Evento inicial (missão)
  for (int i = 0; i < m->n_missoes; i++)
  {
    int tempo = aleat(0, 4320);
    struct ev_missao *evento;
    evento = malloc(sizeof(struct ev_missao));

    if (!evento)
      return;

    evento->id_missao = i;

    fprio_insere(lef, evento, 10, tempo);
  }

  // Agendando o fim do mundo
  int tempo = T_FIM_DO_MUNDO;
  fprio_insere(lef, "FIM", 11, tempo);
}

// programa principal
int main()
{ 
  srand(0);
  
  // Iniciando o mundo
  struct mundo *m;
  m = malloc(sizeof(struct mundo));

  if (!m)
    return -1;
  
  inicia_mundo(m);

  // Criando a fila de eventos futuros
  struct fprio_t *lef;
  lef = fprio_cria();
  executa_eventos_iniciais(m, lef);

  // Eventos iniciais

  // executar o laço de simulação

  // destruir o mundo

  return 0;
}
