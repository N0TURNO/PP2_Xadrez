
#include"ListaPecas.h"
#include"Jogador.h"

Jogador* CriaJogador(Cor cor, char *nome)
{//Cria um espaço na memoria para o jogador
	Jogador *novoJogador = (Jogador*)malloc(sizeof(Jogador));
	if (novoJogador == NULL)
		return NULL;

	novoJogador->listaPecas = CriarLista();
	//Inicializa a lista de pecas e depois verifica se essa lista foi mesmo criada
	if (novoJogador->listaPecas == NULL)
	{//Caso essa lista venha nula é eliminado apontador para o jogador anteriormente criado
		EliminaJogador(&novoJogador);
		return NULL;
	}
	//Atribui o nome e a cor que recebe como parametro 
	novoJogador->corPeca = cor;
	strcpy(novoJogador->nomeJogador, nome);

	novoJogador->ultimaPecaJogada = NULL;

	return novoJogador;

}

//Cria a lista de 16 pecas para cada jogador nas suas posicoes iniciais
void InicializaJogador(Jogador *jogador)
{
	//Cria oito peoes para cada jogador

	for (int i = 0; i < 8; i++)
	{
		if (jogador->corPeca == Branco)
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(i, 6, jogador->corPeca, Peao, Jogavel));
		}
		else
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(i, 1, jogador->corPeca, Peao, Jogavel));
		}

		//Cria Duas Torres para cada jogador

		if (jogador->corPeca == Branco)
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(0, 7, jogador->corPeca, Torre, Jogavel));
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(7, 7, jogador->corPeca, Torre, Jogavel));
		}
		else
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(0, 0, jogador->corPeca, Torre, Jogavel));
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(7, 0, jogador->corPeca, Torre, Jogavel));
		}

		//Cria dois Cavalos para cada jogador

		if (jogador->corPeca == Branco)
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(1, 7, jogador->corPeca, Cavalo, Jogavel));
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(6, 7, jogador->corPeca, Cavalo, Jogavel));
		}
		else
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(1, 0, jogador->corPeca, Cavalo, Jogavel));
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(6, 0, jogador->corPeca, Cavalo, Jogavel));
		}

		//Cria Bispos para cada jogador

		if (jogador->corPeca == Branco)
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(2, 7, jogador->corPeca, Bispo, Jogavel));
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(5, 7, jogador->corPeca, Bispo, Jogavel));
		}
		else
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(2, 0, jogador->corPeca, Bispo, Jogavel));
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(5, 0, jogador->corPeca, Bispo, Jogavel));
		}

		//Cria Rainhas para cada jogador

		if (jogador->corPeca == Branco)
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(3, 7, jogador->corPeca, Rainha, Jogavel));
		}
		else
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(3, 0, jogador->corPeca, Rainha, Jogavel));
		}
		
		//Cria Reis para cada jogadoor

		if (jogador->corPeca == Branco)
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(4, 7, jogador->corPeca, Rei, Jogavel));
		}
		else
		{
			AdicionarPeca(jogador->listaPecas, CriaPecaXadrez(4, 0, jogador->corPeca, Rei, Jogavel));
		}
	}
}

Boolean EliminaJogador(Jogador **jogador)
{
	if (*jogador != NULL)
	{
		EliminarLista(&((*jogador)->listaPecas));
		free(*jogador);
		*jogador = NULL;
		return True;
	}
	return False;
}

//Get sets 
//Obtem o nome do jogador
char* NomeJogador(Jogador *jogador)
{
	if (jogador == NULL)
		return NULL;

	return jogador->nomeJogador;

}
//Define o nome do jogador
Boolean NomeDefineJogador(Jogador *jogador, const char* nome)
{
	if (jogador == NULL)
	{
		return False;
	}
	strcpy(jogador->nomeJogador, nome);
	return True;
}
//Devolve a lista de pecas de um jogador
ListaPecas* BuscaListaJogador(Jogador *jogador)
{
	if (jogador == NULL)
		return NULL;

	return jogador->listaPecas;
}
//Devolve a ultima peca jogada
PecaXadrez* BuscaUltimaPecaJogador(Jogador *jogador)
{
	if (jogador == NULL)
		return NULL;

	return jogador->ultimaPecaJogada;
}
//Define a ultima peca jogada
Boolean DefineUltimaPecaJogada(Jogador *jogador, PecaXadrez *peca)
{
	if (jogador == NULL)
		return False;

	jogador->ultimaPecaJogada = peca;
	return True;
}
//Devolve Cor do jogasdor
Cor BuscaCorJogador(Jogador *jogador)
{
	if (jogador == NULL)
		return -1;
	return jogador->corPeca;
}
