#pragma once
#include "libUnicornio.h"
#include "Tiro.h"

class ShotArray
{
public:
	ShotArray();
	~ShotArray();

	int retornaNumeroTotalTiros();
	Tiro retornaTiroAtIndex(int index_);
	void adicionaTiroNaLista(Tiro tiro_);
	void removeTiroAtIndex(int index_);
	void adicionaTiroNesteIndex(Tiro tiro_, int index_);
private:
	int numeroTotalUtilizado;
	Tiro array[200];
};

