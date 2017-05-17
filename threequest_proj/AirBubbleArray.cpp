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
}

void AirBubbleArray::atualizar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		AirBubble local;
		local = array[i];
		if (local.estaVivo())
		{
			local.atualizar();
			array[i] = local;
		}
		else
		{
			removeAirBubbleAtIndex(i);
		}
	}
}

void AirBubbleArray::desenhar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		array[i].desenhar();
	}
}

void AirBubbleArray::spawnNewRandomAirBubble()
{
	AirBubble local = AirBubble();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
	numeroTotalUtilizado++;
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
	for (int i = index_; i < (numeroTotalUtilizado - 1); i++)
	{
		array[i] = array[i + 1];
	}
	numeroTotalUtilizado--;
}
