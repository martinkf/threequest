#pragma once
#include "libUnicornio.h"
#include "Tiro.h"

class TiroArray
{
public:
	TiroArray();
	~TiroArray();

	void inicializar();
	void atualizar();
	void desenhar();

	int getNumeroTotalUtilizado();
	Tiro getTiroAtIndex(int index_);

	void adicionaTiroNaLista(Tiro tiro_);
	void removeTiroAtIndex(int index_);

private:
	int numeroTotalUtilizado;
	Tiro array[200];
};

