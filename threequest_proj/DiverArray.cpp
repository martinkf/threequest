#include "DiverArray.h"

DiverArray::DiverArray()
{	
}

DiverArray::~DiverArray()
{
}

void DiverArray::inicializar()
{
	numeroTotalUtilizado = 0;

	for (int i = 0; i < 10; i++)
	{
		Diver local = Diver();
		array[i] = local;
	}
}

void DiverArray::atualizar()
{
	// atualiza seu numero de real size
	numeroTotalUtilizado = 0;
	for (int i = 0; i < 10; i++)
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
			removeDiverAtIndex(i);
		}
	}

	// atualiza seu numero de real size
	numeroTotalUtilizado = 0;
	for (int i = 0; i < 10; i++)
	{
		if (array[i].isInitialized())
		{
			numeroTotalUtilizado++;
		}
	}

	// atualiza cada um dos seus elementinhos
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		array[i].atualizar();
	}
}

void DiverArray::desenhar()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		if (array[i].estaVivo())
		{
			array[i].desenhar();
		}
	}
}

bool DiverArray::isSpawnerTurnedOn()
{
	return isTurnedOn;
}

int DiverArray::getNumeroTotalUtilizado()
{
	return numeroTotalUtilizado;
}

Diver DiverArray::getDiverAtIndex(int index_)
{
	return array[index_];
}

void DiverArray::removeDiverAtIndex(int index_)
{
	for (int i = 0; i < (19 - index_); i++)
	{
		array[index_ + i] = array[index_ + i + 1];
	}
}

void DiverArray::clearEverything()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		removeDiverAtIndex(i);
	}
}

void DiverArray::spawnNewRandomDiver()
{
	Diver local = Diver();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
}

void DiverArray::turnOffSpawner()
{
	isTurnedOn = false;
}

void DiverArray::turnOnSpawner()
{
	isTurnedOn = true;
}
