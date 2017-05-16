#ifndef LISTAPECAS
#define LISTAPECAS

#include"Pecas.h"

//Estrutura da lista das peças 
typedef struct ListaPecas ListaPecas;

struct ListaPecas {
	PecaXadrez **pecas;
	int tamanhoLista;
};
//Criação da lista das peças
ListaPecas* CriarLista();
Boolean EliminarLista(ListaPecas **lista);

/*-----------------Getters e Setters-----------------*/

//Adicionar peça à lista de peças
Boolean AdicionarPeca(ListaPecas* lista, PecaXadrez* peca);
//Remover peça da lista
Boolean RemoverPeca(ListaPecas* lista, int x, int y);
//Remover peça através da sua posição no array
Boolean RemoverPecaIndex(ListaPecas *lista, int index);
//Encontra e busca o rei à lista
PecaXadrez* BuscarRei(ListaPecas* lista);
//Busca peça através da sua posição no array
PecaXadrez* BuscarPecaIndex(ListaPecas* lista, int index);
//Busca peça através da sua posição no tabuleiro
PecaXadrez* BuscarPecaPosicao(ListaPecas *l, int x, int y);

//Busca tamanho da lista
int BuscaTamanhoLista(ListaPecas *l);
//Adiciona uma peça à lista dando um index
void AdicionaPecaIndex(ListaPecas* lista, int index, PecaXadrez *peca);

#endif // !LISTAPECAS

