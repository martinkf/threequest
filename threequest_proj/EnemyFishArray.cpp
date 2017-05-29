#include "EnemyFishArray.h"

EnemyFishArray::EnemyFishArray()
{
}

EnemyFishArray::~EnemyFishArray()
{
}

void EnemyFishArray::inicializar()
{
	numeroTotalUtilizado = 0;

	for (int i = 0; i < 50; i++)
	{
		EnemyFish local = EnemyFish();
		array[i] = local;
	}
}

void EnemyFishArray::atualizar()
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
			removeEnemyFishAtIndex(i);
		}
	}

	// atualiza seu numero de real size
	numeroTotalUtilizado = 0;
	for (int i = 0; i < 50; i++)
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

void EnemyFishArray::desenhar()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		if (array[i].estaVivo())
		{
			array[i].desenhar();
		}
	}
}

void EnemyFishArray::spawnNewRandomEnemyFish()
{
	EnemyFish local = EnemyFish();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
}

void EnemyFishArray::turnOffSpawner()
{
	isTurnedOn = false;
}

void EnemyFishArray::turnOnSpawner()
{
	isTurnedOn = true;
}

bool EnemyFishArray::isSpawnerTurnedOn()
{
	return isTurnedOn;
}

int EnemyFishArray::getNumeroTotalUtilizado()
{
	return numeroTotalUtilizado;
}

EnemyFish EnemyFishArray::getEnemyFishAtIndex(int index_)
{
	return array[index_];
}

void EnemyFishArray::removeEnemyFishAtIndex(int index_)
{
	for (int i = 0; i < (49 - index_); i++)
	{
		array[index_ + i] = array[index_ + i + 1];
	}
	numeroTotalUtilizado--;
}

void EnemyFishArray::clearEverything()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		removeEnemyFishAtIndex(i);
	}
}
