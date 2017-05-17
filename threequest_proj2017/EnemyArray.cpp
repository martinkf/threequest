#include "EnemyArray.h"



EnemyArray::EnemyArray()
{
}


EnemyArray::~EnemyArray()
{
}

void EnemyArray::inicializar()
{
	numeroTotalUtilizado = 0;
}

void EnemyArray::atualizar()
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

void EnemyArray::desenhar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		array[i].desenhar();
	}
}

void EnemyArray::spawnNewRandomEnemyFish()
{
	EnemyFish local = EnemyFish();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
	numeroTotalUtilizado++;
}

void EnemyArray::turnOffSpawner()
{
	isTurnedOn = false;
}

void EnemyArray::turnOnSpawner()
{
	isTurnedOn = true;
}

bool EnemyArray::isSpawnerTurnedOn()
{
	return isTurnedOn;
}

int EnemyArray::getNumeroTotalUtilizado()
{
	return numeroTotalUtilizado;
}

EnemyFish EnemyArray::getEnemyFishAtIndex(int index_)
{
	return array[index_];
}

void EnemyArray::removeEnemyFishAtIndex(int index_)
{
	for (int i = index_; i < (numeroTotalUtilizado - 1); i++)
	{
		array[i] = array[i + 1];
	}
	numeroTotalUtilizado--;
}
