#include "ListaPecas.h"

ListaPecas* CriarLista()
{
	//Criar espaço na memória para a lista
	ListaPecas* l = (ListaPecas*)malloc(sizeof(ListaPecas));

	//Verifica se a alocação foi bem sucedida
	if (l == NULL)
		return NULL;

	//Define o tamanho da lista
	l->tamanhoLista = 16;
	//Criar espaço na memória para 
	l->pecas = malloc((l->tamanhoLista) * sizeof(PecaXadrez*));

	//Verifica se a lista está vazia
	if (l->pecas == NULL)
	{
		EliminarLista(&l);
		return NULL;
	}

	int i;
	for (i = 0; i < l->tamanhoLista; i++)
		l->pecas[i] = NULL;

	return l;
}

Boolean EliminarLista(ListaPecas **lista)
{
	if (*lista == NULL)
		return False;
	else
	{
		if ((*lista)->pecas != NULL)
		{
			int i;
			for (i = 0; i < (*lista)->tamanhoLista; i++)
			{
				if ((*lista)->pecas[i] != NULL)
					EliminaPeca(&((*lista)->pecas[i]));
			}
		}
		free(*lista);
		*lista = NULL;
	}
	return True;
}

Boolean AdicionarPeca(ListaPecas* lista, PecaXadrez* peca)
{
	if (peca == NULL)
		return False;
	int i;
	for (i = 0; i < lista->tamanhoLista; i++)
	{
		if (lista->pecas[i] == NULL)
		{
			lista->pecas[i] = peca;
			return True;
		}
	}

}

Boolean RemoverPeca(ListaPecas* lista, int x, int y)
{
	if (lista == NULL)
		return False;

	int i;
	for (i = 0; i < lista->tamanhoLista; i++)
	{
		if (lista->pecas[i] != NULL)
		{
			if (BuscaPosicaoPeca_X(lista->pecas[i]) == x &&  BuscaPosicaoPeca_Y(lista->pecas[i] == y))
			{
				EliminaPeca(&(lista->pecas[i]));
				lista->pecas[i] = NULL;
				return True;
			}
		}
	}
}

Boolean RemoverPecaIndex(ListaPecas *lista, int index)
{
	if (lista == NULL)
		return False;

	EliminaPeca(&(lista->pecas[index]));
	lista->pecas[index] = NULL;

	return True;
}

PecaXadrez* BuscarRei(ListaPecas* lista)
{
	int i;
	for (i = 0; i < lista->tamanhoLista; i++)
	{
		if (lista->pecas[i] != NULL && BuscaTipoPeca(lista->pecas[i]) == Rei)
			return lista->pecas[i];
	}
	return NULL;
}

PecaXadrez* BuscarPecaIndex(ListaPecas* lista, int index)
{
	return lista->pecas[index];
}

PecaXadrez* BuscarPecaPosicao(ListaPecas *lista, int x, int y)
{
	int i;
	for (i = 0; i<lista->tamanhoLista; i++) {
		if (lista->pecas[i] != NULL) {
			if (ChessPiece_GetX(lista->pecas[i]) == x && ChessPiece_GetY(lista->pecas[i]) == y)
				return lista->pecas[i];
		}
	}
	return NULL;
}

int BuscaTamanhoLista(ListaPecas *lista)
{
	if (lista == NULL)
		return -1;

	return lista->tamanhoLista;
}

Boolean AdicionaPecaIndex(ListaPecas* lista, int index, PecaXadrez *peca)
{
	if (lista == NULL) return False;

	lista->pecas[index] = peca;
	return True;
}