#include "Jogo.h"
#include "Jogador.h"
//#include "PrintDasCenas"
//#include "Regras.h"
//#include "MovimentosPossiveis.h"

#include <stdio.h>

Jogo *CriarJogo(Jogo *jogo)
{
	Jogo *jogo = malloc(sizeof(Jogo));
	if (jogo == NULL)
		return NULL;

	jogo->PecaEscolhida = NULL;
	jogo->jogoestado = MainMenu;
	jogo->tabuleiro = NULL;

	return jogo;
}

//Começa um novo jogo, inicializa o tabuleiro e os jogadores
Boolean ComecarJogo(Jogo *jogo)
{
	//Inicializar as variaveis de Jogo
	jogo->turno = Branco;
	jogo->PecaEscolhida = NULL;
	jogo->EstaEmJogo = 1;
	jogo->EstaCheck = 0;
	jogo->EstaCheckMate = 0;

	//Pegar nome dos Jogadores
	//Jogador 1
	char nome1[15], nome2[15];
	printf("Jogador 1: ");
	fgets(nome1, 15, stdin);
	LimparSTDIN(nome1);
	//Jogador 2
	printf("Jogador 2: ");
	fgets(nome2, 15, stdin);
	LimparSTDIN(nome2);

	//Criar Tabuleiro e Jogadores
	jogo->tabuleiro = CriarTabuleiro(CriaJogador(Branco, nome1), CriaJogador(Preto, nome2));
	if (jogo->tabuleiro == NULL)
		return False;

	//Inicializar as Listas de cada Jogador
	InicializaJogador(BuscarJogador(jogo->tabuleiro, Branco));
	InicializaJogador(BuscarJogador(jogo->tabuleiro, Preto));

	//Inicializar Tabuleiro
	InicializarTabuleiro(jogo->tabuleiro);

	//Gerar Movimentos Possiveis
	//Codigo Em Falta!!!

	return True;

}

Boolean ReiniciarJogo(Jogo *jogo)
{
	if (jogo == NULL)
		return False;

	jogo->turno = Branco;
	jogo->PecaEscolhida = NULL;
	jogo->EstaEmJogo = 1;
	jogo->EstaCheck = 0;
	jogo->EstaCheckMate = 0;

	//Vai buscar a informação anteriormente escrita
	Jogador *JogadorBranco = BuscarJogador(jogo->tabuleiro, Branco);
	Jogador *JogadorPreto = BuscarJogador(jogo->tabuleiro, Preto);

	char nome[15];

	//Branco
	strcpy(nome, NomeJogador(JogadorBranco));
	EscolherJogador(jogo->tabuleiro, CriaJogador(Branco, nome), Branco);

	//Se não conseguir criar novo jogador branco, vai buscar a informação anterior
	if (BuscarJogador(jogo->tabuleiro, Branco) == NULL)
	{
		EscolherJogador(jogo->tabuleiro, JogadorBranco, Branco);
		return True;
	}

	//Preto
	strcpy(nome, NomeJogador(JogadorPreto));
	EscolherJogador(jogo->tabuleiro, CriaJogador(Preto, nome), Preto);
	
	//Se não conseguir criar novo jogador preto, vai buscar a informação anterior
	//Para ambos os jogadores
	if (BuscarJogador(jogo->tabuleiro, Preto) == NULL)
	{
		//Elimina Jogador branco criado com sucesso
		Jogador *paraEliminar = BuscarJogador(jogo->tabuleiro, Branco);
		EliminaJogador(&(paraEliminar));

		EscolherJogador(jogo->tabuleiro, JogadorBranco, Branco);
		EscolherJogador(jogo->tabuleiro, JogadorPreto, Preto);
		return True;
	}

	InicializaJogador(BuscarJogador(jogo->tabuleiro, Branco));
	InicializaJogador(BuscarJogador(jogo->tabuleiro, Preto));

	//Tabuleiro
	AtualizarTabuleiro(jogo->tabuleiro);

	//Libertar informação inicial dos jogadores
	EliminaJogador(&JogadorBranco);
	EliminaJogador(&JogadorPreto);

	//Gerar Jogadas Possíveis
	//Codigo em Falta!!!
}
