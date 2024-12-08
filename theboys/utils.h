// Declarações e configurações auxiliares para a simulação
// Autora: Andrieli Luci Gonçalves, GRR 202449003
// Dez 2024

#ifndef UTILS
#define UTILS

// Configurações gerais do mundo
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 5
#define N_MISSOES T_FIM_DO_MUNDO / 100

// Categorização dos eventos
#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define ENTRA 4
#define SAI 5
#define VIAJA 6
#define MORRE 7
#define AVISA 8
#define MISSAO 9
#define FIM 10

// Estrutura que implementa um par de valores (x, y), representando
// a coordenada de uma localização
struct coordenadas_t
{
  int x; // Coordenada horizontal (eixo x)
  int y; // Coordenada vertical (eixo y)
};

// Gera um número aleatório entre min e max, inclusive
// Retorno: número inteiro aleatório
long aleat(long min, long max);

// Calcula a Distância Euclidiana entre dois locais
// Retorno: número inteiro
int calcula_distancia(struct coordenadas_t c1, struct coordenadas_t c2);

#endif
