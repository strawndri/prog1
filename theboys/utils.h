#ifndef UTILS
#define UTILS

// Configurações gerais
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 5
#define N_MISSOES T_FIM_DO_MUNDO / 10

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
struct coordenada
{
  int x; // Coordenada horizontal (eixo x)
  int y; // Coordenada vertical (eixo y)
};

long aleat(long min, long max);

int calcula_distancia(struct coordenada c1, struct coordenada c2);

#endif
