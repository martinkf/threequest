#pragma once
#include "libUnicornio.h"
#include "Tiro.h"

class TiroArray
{
public:
	TiroArray();
	~TiroArray();

	void inicializar();

	int retornaNumeroTotalTiros();
	Tiro retornaTiroAtIndex(int index_);
	void adicionaTiroNaLista(Tiro tiro_);
	void removeTiroAtIndex(int index_);
	void adicionaTiroNesteIndex(Tiro tiro_, int index_);
private:
	int numeroTotalUtilizado;
	Tiro array[200];
};

