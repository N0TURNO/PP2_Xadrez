#include<stdio.h>
typedef enum boolean { NO, YES };

struct Peca
{
	char* nome;

	int posicaoinX;
	int posicaoinY;

	int movPeca;

	int posicaoAct;
	int numPecaMov;

	boolean presença;
	boolean eliminada;

};

