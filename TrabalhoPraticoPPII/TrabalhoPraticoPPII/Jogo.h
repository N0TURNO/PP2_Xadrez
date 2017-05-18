#ifndef JOGO_H
#define JOGO_H

#include "TabuleiroXadrez.h"
#include "Pecas.h"

typedef enum jogoestado {Playing, PromotionMenu, PauseMenu, PauseOptionsMenu, EndGameMenu, MainMenu }JogoEstado;

typedef struct jogo Jogo;

struct jogo {
	TabuleiroXadrez *tabuleiro;
	PecaXadrez *PecaEscolhida;

	Cor turno;
	JogoEstado jogoestado;

	int EstaEmJogo;
	int EstaCheckMate;
	int EstaCheck;
};

Jogo* CriarJogo();
Boolean ReiniciarJogo(Jogo *jogo);

Boolean ComeçarJogo(Jogo *jogo);
Boolean Jogar(Jogo *jogo);
Boolean AtualizarJogo(Jogo *jogo);

Boolean PararJogo(Jogo *jogo);
Boolean ApagarJogo(Jogo **jogo);

Boolean LimparSTDIN(char *s);

int EstaCheckJogo(Jogo *jogo);
Boolean EstabeleceCheckJogo(Jogo *jogo, int a);

int EstaCheckMateJogo(Jogo *jogo);
Boolean EstabeleceCheckMateJogo(Jogo *jogo, int a);

int EstaEmJogo(Jogo *jogo);
Boolean EstabeleceEstaEmJogo(Jogo *jogo, int a);

Cor BuscarTurnoJogo(Jogo *jogo);
Boolean EstabelecerTurnoJogo(Jogo *jogo, Cor t);
Boolean MudarJogador(Jogo *jogo);

JogoEstado BuscarEstadoJogo(Jogo *jogo);
JogoEstado EstabelecerEstadoJogo(Jogo *jogo);

PecaXadrez *BuscarPecaSelecionadaJogo(Jogo *jogo);
Boolean EstabelecerPecaSelecionadaJogo(Jogo *jogo, PecaXadrez *peca);

PecaXadrez* BuscarTabuleiro(Jogo *jogo);
Boolean EstabelecerTabuleiro(Jogo *jogo, TabuleiroXadrez *tabuleiro);

#endif // JOGO_H
