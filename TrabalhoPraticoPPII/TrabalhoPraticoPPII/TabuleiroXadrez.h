#ifndef TABULEIROXADREZ_H
#define TABULEIROXADREZ_H

#include "Jogador.h"

typedef struct tabuleiroXadrez TabuleiroXadrez;

struct tabuleiroXadrez
{
	PecaXadrez *pecas[8][8];

	Jogador *jogador1;
	Jogador *jogador2;
};

TabuleiroXadrez *CriarTabuleiro(Jogador *jogador1, Jogador *jogador2);
Boolean InicializarTabuleiro(TabuleiroXadrez *tabuleiro);
//Reset do tabuleiro
Boolean RecomporTabuleiro(TabuleiroXadrez *tabuleiro);
Boolean AtualizarTabuleiro(TabuleiroXadrez *tabuleiro);

Boolean AtualizarMovimentosPossíveisListas(TabuleiroXadrez *tabuleiro);
Boolean AtualizarMovimentosPossíveisLista(TabuleiroXadrez *tabuleiro, PecaXadrez *peca);

Boolean EliminarTabuleiro(TabuleiroXadrez **tabuleiro);

PecaXadrez *BuscarPecaPosicaoTabuleiro(TabuleiroXadrez *tabuleiro, int x, int y);
Boolean AdicionarPecaPosicaoTabuleiro(TabuleiroXadrez *tabuleiro, int x, int y, PecaXadrez *peca);

Jogador *BuscarJogador(TabuleiroXadrez *tabuleiro, Cor color);
//Escolhe qual jogador irá jogar de momento
Boolean EscolherJogador(TabuleiroXadrez *tabuleiro, Jogador *jogador, Cor cor);

#endif // TABULEIROXADREZ_H