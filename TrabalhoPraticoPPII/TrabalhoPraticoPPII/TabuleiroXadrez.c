#include "TabuleiroXadrez.h"
//#include "MovimentosPossiveis.h"
//#include "Regras.h"

#include <stdlib.h>

TabuleiroXadrez *CriarTabuleiro(Jogador *jogador1, Jogador *jogador2)
{
	TabuleiroXadrez *tabuleiro = malloc(sizeof(TabuleiroXadrez));
	if (tabuleiro == NULL)
		return NULL;

	RecomporTabuleiro(tabuleiro);

	tabuleiro->jogador1 = jogador1;
	tabuleiro->jogador2 = jogador2;

	if (tabuleiro->jogador1 == NULL || tabuleiro->jogador2 == NULL)
	{
		EliminarTabuleiro(&tabuleiro);
		return NULL;
	}

	return tabuleiro;
}

Boolean InicializarTabuleiro(TabuleiroXadrez *tabuleiro)
{
	if (tabuleiro == NULL)
		return False;
	else
	{
		int i;
		for (i = 0; i < MAXPECAS; i++)
		{
			PecaXadrez *p1 = BuscarPecaIndex(BuscaListaJogador(BuscarJogador(tabuleiro, Branco)), i);
			if (p1 == NULL)
				return False;
			else
				tabuleiro->pecas[BuscaPosicaoPeca_X(p1)][BuscaPosicaoPeca_Y(p1)] = p1;

			PecaXadrez *p2 = BuscarPecaIndex(BuscaListaJogador(BuscarJogador(tabuleiro, Preto)), i);
			if (p2 == NULL)
				return False;
			else
				tabuleiro->pecas[BuscaPosicaoPeca_X(p2)][BuscaPosicaoPeca_Y(p2)] = p2;
		}

		return True;
	}
}

Boolean RecomporTabuleiro(TabuleiroXadrez *tabuleiro)
{
	if (tabuleiro == NULL)
		return False;
	else
	{
		int i, j;
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				tabuleiro->pecas[j][i] = NULL;
			}
		}

		return True;
	}
}

Boolean AtualizarTabuleiro(TabuleiroXadrez *tabuleiro)
{
	RecomporTabuleiro(tabuleiro);
	InicializarTabuleiro(tabuleiro);
}

Boolean AtualizarMovimentosPossíveisListas(TabuleiroXadrez *tabuleiro)
{
	if (tabuleiro == NULL)
		return False;

	int i;
	for (i = 0; i < MAXPECAS; i++)
	{
		//Jogador 1
		PecaXadrez *peca = BuscarPecaIndex(BuscaListaJogador(BuscarJogador(tabuleiro, Branco)), i);
		if (peca == NULL)
			return False;
		else
			AtualizarMovimentosPossíveisLista(tabuleiro, peca);

		//Jogador 2
		peca = BuscarPecaIndex(BuscaListaJogador(BuscarJogador(tabuleiro, Preto)), i);
		if (peca == NULL)
			return False;
		else
			AtualizarMovimentosPossíveisLista(tabuleiro, peca);
	}
	return True;
}

Boolean AtualizarMovimentosPossíveisLista(TabuleiroXadrez *tabuleiro, PecaXadrez *peca)
{
	if (peca == NULL || tabuleiro == NULL)
		return False;

	//Precisa da classe Movimentos Possiveis!!!!
}

Boolean EliminarTabuleiro(TabuleiroXadrez **tabuleiro)
{
	if (*tabuleiro == NULL)
		return False;
	else
	{
		EliminaJogador(&((*tabuleiro)->jogador1));
		EliminaJogador(&((*tabuleiro)->jogador2));
		free(*tabuleiro);
		*tabuleiro = NULL;
	}
	
	return True;
}

PecaXadrez *BuscarPecaPosicaoTabuleiro(TabuleiroXadrez *tabuleiro, int x, int y)
{
	if (tabuleiro == NULL)
		return NULL;

	return tabuleiro->pecas[x][y];
}

Boolean AdicionarPecaPosicaoTabuleiro(TabuleiroXadrez *tabuleiro, int x, int y, PecaXadrez *peca)
{
	if (tabuleiro == NULL)
		return False;

	tabuleiro->pecas[x][y] = peca;
	return True;
}

Jogador *BuscarJogador(TabuleiroXadrez *tabuleiro, Cor cor)
{
	if (BuscaCorJogador(tabuleiro->jogador1) == cor)
		return tabuleiro->jogador1;
	else
		return tabuleiro->jogador2;
}

Boolean EscolherJogador(TabuleiroXadrez *tabuleiro, Jogador *jogador, Cor cor)
{
	if (tabuleiro == NULL || jogador == NULL)
		return False;

	if (cor == Branco)
		tabuleiro->jogador1 = jogador;
	else
		tabuleiro->jogador2 = jogador;

	return True;
}

