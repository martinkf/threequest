#pragma once
#include "Tiro.h"

class TiroArray
{
public:
	TiroArray();
	~TiroArray();

	void inicializar();
	void atualizar();
	void desenhar();

	//
	//
	//

	//
	int getNumeroTotalUtilizado();
	Tiro getTiroAtIndex(int index_);
	void removeTiroAtIndex(int index_);

	//
	void adicionaTiroNaLista(Tiro tiro_);
	
	void clearEverything();
	void clearEverythingButBlueFreezers();

private:
	int numeroTotalUtilizado;
	Tiro array[50];
};

