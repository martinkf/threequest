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

void TiroArray::atualizar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		Tiro test;
		test = array[i];
		if (test.estaVivo())
		{
			test.atualizar();
			array[i] = test;
		}
		else
		{
			removeTiroAtIndex(i);
		}
	}
}

void TiroArray::desenhar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		if (array[i].estaVivo()) 
		{
			array[i].desenhar();
		}
	}
}

int TiroArray::getNumeroTotalUtilizado()
{
	return numeroTotalUtilizado;
}

Tiro TiroArray::getTiroAtIndex(int index_)
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

void TiroArray::clearEverything()
{
	numeroTotalUtilizado = 0;
}
