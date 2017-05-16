#ifndef LISTAPECAS
#define LISTAPECAS

#include"Pecas.h"

//Estrutura da lista das pe�as 
typedef struct ListaPecas ListaPecas;

struct ListaPecas {
	PecaXadrez **pecas;
	int tamanhoLista;
};
//Cria��o da lista das pe�as
ListaPecas* CriarLista();
Boolean EliminarLista(ListaPecas **lista);

/*-----------------Getters e Setters-----------------*/

//Adicionar pe�a � lista de pe�as
Boolean AdicionarPeca(ListaPecas* lista, PecaXadrez* peca);
//Remover pe�a da lista
Boolean RemoverPeca(ListaPecas* lista, int x, int y);
//Remover pe�a atrav�s da sua posi��o no array
Boolean RemoverPecaIndex(ListaPecas *lista, int index);
//Encontra e busca o rei � lista
PecaXadrez* BuscarRei(ListaPecas* lista);
//Busca pe�a atrav�s da sua posi��o no array
PecaXadrez* BuscarPecaIndex(ListaPecas* lista, int index);
//Busca pe�a atrav�s da sua posi��o no tabuleiro
PecaXadrez* BuscarPecaPosicao(ListaPecas *l, int x, int y);

//Busca tamanho da lista
int BuscaTamanhoLista(ListaPecas *l);
//Adiciona uma pe�a � lista dando um index
void AdicionaPecaIndex(ListaPecas* lista, int index, PecaXadrez *peca);

#endif // !LISTAPECAS

