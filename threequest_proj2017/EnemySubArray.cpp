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
}

void EnemySubArray::atualizar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		EnemySub local;
		local = array[i];
		if (local.estaVivo())
		{
			local.atualizar();
			array[i] = local;
		}
		else
		{
			removeEnemySubAtIndex(i);
		}
	}
}

void EnemySubArray::desenhar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		array[i].desenhar();
	}
}

void EnemySubArray::spawnNewRandomEnemySub()
{
	EnemySub local = EnemySub();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
	numeroTotalUtilizado++;
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
	for (int i = index_; i < (numeroTotalUtilizado - 1); i++)
	{
		array[i] = array[i + 1];
	}
	numeroTotalUtilizado--;
}

void EnemySubArray::addEnemySubAtIndex(EnemySub _input, int _index)
{
	array[_index] = _input;
}
