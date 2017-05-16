#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>

#ifndef PECAXADREZ
#define PECAXADREZ

typedef enum boolean{False, True}Boolean;
//Define a cor do jogador
typedef enum cor { Branco, Preto}Cor;
//Define o tipo de peça
typedef enum pecaTipo{Peao, Torre, Cavalo, Bispo, Rainha, Rei }PecaTipo;
//Define se a peca esta em jogo, se foi eliminada mas pode voltar a jogo ou se esta permanentemente eleminada neste jogo.
typedef enum pecaEstado{Jogavel, NaoJogavel, Eliminada}PecaEstado;
//Estrutura que suporta as pecas de jogo
typedef struct pecaXadrez PecaXadrez, *PtrPecaXadrez;

struct  pecaXadrez
{
	int posicaoIX;
	int posicaoIY;
	int numeroCasas;
	int numeroMovimentos;

	Cor corPeca;
	PecaTipo tipoPeca;
	PecaEstado estadoPeca;

	//ListaPossiveisMovimentos *listaPossiveisMovimentos;

};
//Construtor de pecas
PecaXadrez* CriaPecaXadrez(int posicaoIX, int posicaoIY, Cor cor, PecaTipo tipo, PecaEstado estado);
//Elimina uma peca da lista do jogador
Boolean EliminaPeca(PecaXadrez **peca);

//Getters e Setters


//Obtem o tipo da peca por uma chave de texto
PecaTipo BuscaTipoTexto(char tipo);
//Devolver a chave de texto correspondente à peca
char BuscaTipoPorTipo(PecaTipo tipo);


//Encontra as coordenadas de uma peca no tabuleiro 
int BuscaPosicaoPeca_X(PecaXadrez *peca);
int BuscaPosicaoPeca_Y(PecaXadrez *peca);
//Define a posicao de uma peca no tabuleiro
Boolean DefinePosicaoPeca(PecaXadrez *peca, int x, int y);

//Devolve o tipo de peca usando apenas a peca
int BuscaTipoPeca(PecaXadrez *peca);
//Define o tipo da peca
Boolean DefineTipoPeca(PecaXadrez *peca, PecaTipo tipo);

//Devolve a cor da peca
Cor BuscaCorPeca(PecaXadrez *peca);

//Metodos de obtêm o numero de vezes que uma peca foi jogada, adiciona uma nova jogada e define um novo numero de jogadas.
int BuscaNumMovimentos(PecaXadrez *peca);
Boolean AdicionaNumMovimentos(PecaXadrez *peca, int movimentos);
Boolean DefineNumMovimentos(PecaXadrez *peca, int movimentos);

//Metodos que devolvem o estado da peca e modificam o seu estado
int BuscaEstadoPeca(PecaXadrez *peca);
Boolean ModificaEstadoPeca(PecaXadrez *peca, PecaEstado estado);


//ListaMovimentosPossiveis* BuscaListaMovimentosPossiveis(PecaXadrez *peca);


#endif // PECAXADREZ