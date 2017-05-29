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

	for (int i = 0; i < 100; i++)
	{
		Enemy local = Enemy();
		array[i] = local;
	}
}

void EnemyArray::atualizar()
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
			removeEnemyAtIndex(i);
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

void EnemyArray::desenhar()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		if (array[i].estaVivo())
		{
			array[i].desenhar();
		}
	}
}

void EnemyArray::spawnNewRandomEnemy()
{
	Enemy local = Enemy();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
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

Enemy EnemyArray::getEnemyAtIndex(int index_)
{
	return array[index_];
}

void EnemyArray::removeEnemyAtIndex(int index_)
{
	for (int i = 0; i < (49 - index_); i++)
	{
		array[index_ + i] = array[index_ + i + 1];
	}
	numeroTotalUtilizado--;
}

void EnemyArray::addEnemyAtIndex(Enemy _input, int _index)
{
	array[_index] = _input;
}

void EnemyArray::clearEverything()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		removeEnemyAtIndex(i);
	}
}