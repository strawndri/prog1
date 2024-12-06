#ifndef ENTIDADES
#define ENTIDADES

#include <stdbool.h>

#include "conjunto.h"
#include "fprio.h"
#include "mundo.h"
#include "utils.h"

// Estrutura que implementa um herói
struct heroi_t
{
  int id_heroi;               // Identificador do herói
  int id_base;                // Identificador da base onde o herói está
  int paciencia;              // Nível de paciência 
  int velocidade;             // Quão rápido ele se locomove
  int experiencia;            // Nível de experiência do herói
  bool morto;                 // false se estiver vivo,
                              // true se morreu em missão
  struct cjto_t *habilidades; // Conjunto de habilidades
};

// Estrutura que implementa uma base
struct base_t
{
  int id_base;                // Identificador da base 
  int lotacao;                // Capacidade máxima possível
  int espera_max;             // Maior lotação atingida  
  int missoes;                // Quantas missões foram concluídas na base
  struct cjto_t *presentes;   // Conjunto de heróis na base
  struct lista_t *espera;     // Fila de heróis esperando para entrar
  struct coordenadas_t local; // Localização em (x, y)
};

// Estrutura que implementa uma missão
struct missao_t
{
  int id_missao;              // Identificador da missão
  int tentativas;             // Quantas vezes a missão foi "tentada"
  int perigo;                 // Nível de dificuldade
  bool cumprida;              // true se cumprida, false caso contrário
  struct cjto_t *habilidades; // Conjunto de habilidades
  struct coordenadas_t local; // Localização em (x, y)
};

// Inicializa os atributos do herói
// Retorno: struct heroi_t
struct heroi_t cria_heroi(int id);

// Destroi os atributos alocados dinamicamente do herói
// Retorno: void
void destroi_heroi(struct heroi_t *h);

// Inicializa os atributos da base
// Retorno: struct base_t
struct base_t cria_base(int id);

// Destroi os atributos alocados dinamicamente da base
// Retorno: void
void destroi_base(struct base_t *b);

// Inicializa os atributos da missão
// Retorno: struct missao_t
struct missao_t cria_missao(int id);

// Destroi os atributos alocados dinamicamente da missão
// Retorno: void
void destroi_missao(struct missao_t *m);

#endif