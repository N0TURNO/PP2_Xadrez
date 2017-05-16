#ifndef JOGADOR
#define JOGADOR

#include"Pecas.h"
#include"ListaPecas.h"
#include <stdlib.h>
#include <string.h>

#define MAXPECAS 16

typedef struct jogador Jogador, PtrJogador;

struct jogador
{
	char* nomeJogador;

	ListaPecas *listaPecas;
	PecaXadrez *ultimaPecaJogada;

	Cor corPeca;
};

Jogador* CriaJogador(Cor cor, char *nome);

void InicializaJogador(Jogador *jogador);

Boolean EliminaJogador(Jogador **jogador);

char* NomeJogador(Jogador *jogador);
Boolean NomeDefineJogador(Jogador *jogador, const char* nome);

ListaPecas* BuscaListaJogador(Jogador *jogador);

PecaXadrez* BuscaUltimaPecaJogador(Jogador *jogador);
Boolean DefineUltimaPecaJogada(Jogador *jogador, PecaXadrez *peca);

Cor BuscaCorJogador(Jogador *jogador);

#endif // !JOGADOR
