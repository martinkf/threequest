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
}

void EnemyFishArray::atualizar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		EnemyFish local;
		local = array[i];
		if (local.estaVivo())
		{
			local.atualizar();
			array[i] = local;
		}
		else
		{
			removeEnemyFishAtIndex(i);
		}
	}
}

void EnemyFishArray::desenhar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		array[i].desenhar();
	}
}

void EnemyFishArray::spawnNewRandomEnemyFish()
{
	EnemyFish local = EnemyFish();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
	numeroTotalUtilizado++;
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
	for (int i = index_; i < (numeroTotalUtilizado - 1); i++)
	{
		array[i] = array[i + 1];
	}
	numeroTotalUtilizado--;
}