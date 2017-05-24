#include "EnemySubArray.h"

EnemySubArray::EnemySubArray()
{
}

EnemySubArray::~EnemySubArray()
{
}

void EnemySubArray::inicializar()
{
	numeroTotalUtilizado = 0;

	for (int i = 0; i < 50; i++)
	{
		EnemySub local = EnemySub();
		array[i] = local;
	}
}

void EnemySubArray::atualizar()
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
			removeEnemySubAtIndex(i);
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

void EnemySubArray::desenhar()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		if (array[i].estaVivo())
		{
			array[i].desenhar();
		}
	}
}

void EnemySubArray::spawnNewRandomEnemySub()
{
	EnemySub local = EnemySub();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
}

void EnemySubArray::turnOffSpawner()
{
	isTurnedOn = false;
}

void EnemySubArray::turnOnSpawner()
{
	isTurnedOn = true;
}

bool EnemySubArray::isSpawnerTurnedOn()
{
	return isTurnedOn;
}

int EnemySubArray::getNumeroTotalUtilizado()
{
	return numeroTotalUtilizado;
}

EnemySub EnemySubArray::getEnemySubAtIndex(int index_)
{
	return array[index_];
}

void EnemySubArray::removeEnemySubAtIndex(int index_)
{
	for (int i = 0; i < (49 - index_); i++)
	{
		array[index_ + i] = array[index_ + i + 1];
	}
}

void EnemySubArray::addEnemySubAtIndex(EnemySub _input, int _index)
{
	array[_index] = _input;
}

void EnemySubArray::clearEverything()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		removeEnemySubAtIndex(i);
	}
}