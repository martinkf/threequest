#include "AirBubbleArray.h"

AirBubbleArray::AirBubbleArray()
{
}

AirBubbleArray::~AirBubbleArray()
{
}

void AirBubbleArray::inicializar()
{
	numeroTotalUtilizado = 0;

	for (int i = 0; i < 100; i++)
	{
		AirBubble local = AirBubble();
		array[i] = local;
	}
}

void AirBubbleArray::atualizar()
{
	// atualiza seu numero de real size
	numeroTotalUtilizado = 0;
	for (int i = 0; i < 100; i++)
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
			removeAirBubbleAtIndex(i);
		}
	}

	// atualiza seu numero de real size
	numeroTotalUtilizado = 0;
	for (int i = 0; i < 100; i++)
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

void AirBubbleArray::desenhar()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		if (array[i].estaVivo())
		{
			array[i].desenhar();
		}
	}
}

void AirBubbleArray::spawnNewRandomAirBubble()
{
	AirBubble local = AirBubble();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
}

void AirBubbleArray::turnOffSpawner()
{
	isTurnedOn = false;
}

void AirBubbleArray::turnOnSpawner()
{
	isTurnedOn = true;
}

bool AirBubbleArray::isSpawnerTurnedOn()
{
	return isTurnedOn;
}

int AirBubbleArray::getNumeroTotalUtilizado()
{
	return numeroTotalUtilizado;
}

AirBubble AirBubbleArray::getAirBubbleAtIndex(int index_)
{
	return array[index_];
}

void AirBubbleArray::removeAirBubbleAtIndex(int index_)
{
	for (int i = 0; i < ( 99 - index_ ); i++)
	{
		array[index_ + i] = array[index_ + i + 1];
	}
}

void AirBubbleArray::clearEverything()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		removeAirBubbleAtIndex(i);
	}
}
