#include <stdio.h>
#include "utils.h"
#include "eventos.h"
#include "mundo.h"

// Função para realizar os eventos iniciais
void executa_eventos_iniciais(struct mundo *m, struct fprio_t *lef)
{
  // Evento inicial (herói)
  for (int i = 0; i < m->n_herois; i++)
  {
    int base = aleat(0, m->n_bases - 1);
    int tempo = aleat(0, 4320);

    // (!): talvez declarar uma função de criação de evento
    struct evento_t *evento;
    evento = malloc(sizeof(struct evento_t));

    if (!evento)
      return;

    evento->tempo = tempo;
    evento->d1 = i;
    evento->d2 = base;

    fprio_insere(lef, evento, 1, tempo);
  }

  // Evento inicial (missão)
  for (int i = 0; i < m->n_missoes; i++)
  {
    int tempo = aleat(0, 4320);
    struct evento_t *evento;
    evento = malloc(sizeof(struct evento_t));

    if (!evento)
      return;

    evento->tempo = tempo;
    evento->d1 = i;

    fprio_insere(lef, evento, 10, tempo);
  }

  // Agendando o fim do mundo
  int tempo = T_FIM_DO_MUNDO;
  fprio_insere(lef, "FIM", 11, tempo);
}

// Funções dos eventos ---------------------------------------------------------

// Chega
void chega(int t, struct heroi *h, struct base *b)
{
  h->id_base = b->id_base;
  int espera;

  if (b->presentes < b->lotacao && fprio_tamanho(b->espera) == 0)
    espera = 1;
  else
    espera = (h->paciencia) > (10 * fprio_tamanho(b->espera));

  // if (espera)
  // crie evento espera
  // else
  // cria evento desiste
}

// Espera
void espera(int t, struct heroi *h, struct base *b)
{
}

// Desiste
void desiste(int t, struct heroi *h, struct base *b)
{
}

// Avisa
void avisa(int t, struct base *b)
{
}

// Entra
void entra(int t, struct heroi *h, struct base *b)
{
}

// Sai
void sai(int t, struct heroi *h, struct base *b)
{
}

// Viaja
void viaja(int t, struct heroi *h, struct base *b)
{
}

// Morre
void morre(int t, struct heroi *h, struct base *b)
{
}

// Missao
void missao(int t, struct missao *m)
{
}

// Fim
void fim(int t)
{
}