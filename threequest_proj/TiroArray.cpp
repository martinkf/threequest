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

	for (int i = 0; i < 50; i++)
	{
		Tiro local = Tiro();
		array[i] = local;
	}
}

void TiroArray::atualizar()
{	
	// atualiza seu numero de real size
	numeroTotalUtilizado = 0;
	for (int i = 0; i < 50; i++)
	{
		if (array[i].isInitialized())
		{
			numeroTotalUtilizado++;
		}
	}

	// confere seus elementinhos mortos e os remove
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		if (!array[i].estaVivo()) 
		{
			removeTiroAtIndex(i);
		}
	}

	// atualiza cada um dos seus elementinhos
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		array[i].atualizar();
	}
}

void TiroArray::desenhar()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
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
}

void TiroArray::removeTiroAtIndex(int index_)
{
	for (int i = 0; i < ( 49 - index_ ); i++)
	{
		array[index_ + i] = array[index_ + i + 1];
	}
}

void TiroArray::clearEverything()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		array[i].reset();
	}
}

void TiroArray::clearEverythingButBlueFreezers()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		if (array[i].getShotType() != shotBlue)
		{
			removeTiroAtIndex(i);
		}
	}
}
