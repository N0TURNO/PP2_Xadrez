#include"Pecas.h"
//#include"ListaMovimentosPossiveis"

PecaXadrez* CriaPecaXadrez(int posicaoIX, int posicaoIY, Cor cor, PecaTipo tipo, PecaEstado estado)
{
	//Cria espaco na memoria heap para uma nova peca
	PecaXadrez *novaPeca = (PecaXadrez*)malloc(sizeof(PecaXadrez));

	//Verifica se a alocaçao foi bem sucedida
	if (novaPeca == NULL)
		return NULL;

	//Define a posicao inicial da peca criada
	novaPeca->posicaoIX = posicaoIX;
	novaPeca->posicaoIY = posicaoIY;
	//Define a cor da peca criada
	novaPeca->corPeca = cor;
	//Define qual é o tipo de peca criada
	novaPeca->tipoPeca = tipo;
	//Define que a peca comeca com o estado jogavel quando é criada
	novaPeca->estadoPeca = Jogavel;
	//Define que a peca começa como nao utilizada
	novaPeca->numeroMovimentos = 0;

	/*novaPeca->ListaMovimentosPossiveis = CriaListaMovimentosPossiveis();
	if (novaPeca->ListaMovimentosPossiveis == NULL)
	{
		EliminaPeca(&novaPeca);
		return NULL;
	}*/

	return novaPeca;

}

Boolean EliminaPeca(PecaXadrez **peca)
{
	if (*peca != NULL)
	{
		//EliminaListaMovimentosPossivies(&((*peca)->listaMovimentosPossiveis));
		free(*peca);
		*peca = NULL;
		return True;
	}
	return False;
}

PecaTipo* BuscaTipoTexto(char tipo)
{
	switch (tipo)
	{
	case 'P': return Peao;
	case 'T': return Torre;
	case 'C': return Cavalo;
	case 'B': return Bispo;
	case 'Q': return Rainha;
	case 'R': return Rei;
	default: return Peao;

	}
}

char BuscaTipoPorTipo(PecaTipo tipo)
{
	switch (tipo)
	{
	case Peao : return 'P';
	case Torre: return 'T';
	case Cavalo: return 'C';
	case Bispo: return 'B';
	case Rainha: return 'Q';
	case Rei: return 'R';
	default: return 'P';
	}
}

//Getters Setters

//Para posiçao
int BuscaPosicaoPeca_X(PecaXadrez *peca)
{
	if (peca == NULL)
		return -1;

	return peca->posicaoIX;

}

int BuscaPosicaoPeca_Y(PecaXadrez *peca)
{
	if (peca == NULL)
		return -1;

	return peca->posicaoIY;
}

Boolean DefinePosicaoPeca(PecaXadrez *peca, int x, int y)
{
	if (peca == NULL)
		return False;
	//Ligeiramente diferente o bloco de condicao
	if ((x != -1) && (y != -1))
	{
		peca->posicaoIX = x;
		peca->posicaoIY = y;

		return True;
	}
}


//Para o tipo
int BuscaTipoPeca(PecaXadrez *peca)
{
	if (peca == NULL)
		return -1;

	return peca->tipoPeca;
}

Boolean DefineTipoPeca(PecaXadrez *peca, PecaTipo tipo)
{
	if (peca == NULL)
		return False;

	peca->tipoPeca = tipo;
	return True;
}


//Para Cor
Cor BuscaCorPeca(PecaXadrez *peca)
{
	if (peca == NULL)
		return -1;

	return peca->corPeca;

}

//Para Moviemntos 
int BuscaNumMovimentos(PecaXadrez *peca)
{
	if (peca == NULL)
		return -1;

	return peca->numeroMovimentos;

}
Boolean AdicionaNumMovimentos(PecaXadrez *peca, int movimentos)
{
	if (peca == NULL)
		return False;

	peca->numeroMovimentos += movimentos;
	return True;
}
Boolean DefineNumMovimentos(PecaXadrez *peca, int movimentos)
{
	if (peca == NULL)
		return False;

	return peca->numeroMovimentos = movimentos;

}

//Para Estado
int BuscaEstadoPeca(PecaXadrez *peca)
{
	if (peca == NULL)
		return -1;

	return peca->estadoPeca;
}
Boolean ModificaEstadoPeca(PecaXadrez *peca, PecaEstado estado)
{
	if (peca == NULL)
		return False;


	peca->estadoPeca = estado;
	return True;
}

//Para Movimentos
/*ListaMovimentosPossiveis* BuscaListaMovimentosPossiveis(PecaXadrez *peca)
{
if(peca==NULL)
return NULL;

return peca->listaMovimentosPossiveis;
}
*/
