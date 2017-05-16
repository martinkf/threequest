#include "TiroArray.h"

TiroArray::TiroArray()
{	
}

TiroArray::~TiroArray()
{
}

void TiroArray::inicializar()
{
	numeroTotalUtilizado = 0;
}

int TiroArray::retornaNumeroTotalTiros()
{
	return numeroTotalUtilizado;
}

Tiro TiroArray::retornaTiroAtIndex(int index_)
{	
	return array[index_];
}

void TiroArray::adicionaTiroNaLista(Tiro tiro_)
{
	array[numeroTotalUtilizado] = tiro_;
	numeroTotalUtilizado++;
}

void TiroArray::removeTiroAtIndex(int index_)
{	
	for (int i = index_; i < (numeroTotalUtilizado - 1); i++)
	{
		array[i] = array[i + 1];
	}
	numeroTotalUtilizado--;
}

void TiroArray::adicionaTiroNesteIndex(Tiro tiro_, int index_)
{
	array[index_] = tiro_;
}
