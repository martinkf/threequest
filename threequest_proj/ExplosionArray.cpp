#include "ExplosionArray.h"

ExplosionArray::ExplosionArray()
{
}

ExplosionArray::~ExplosionArray()
{
}

void ExplosionArray::inicializar()
{
	numeroTotalUtilizado = 0;

	for (int i = 0; i < 20; i++)
	{
		Explosion local = Explosion();
		array[i] = local;
	}
}

void ExplosionArray::atualizar()
{
	// atualiza seu numero de real size
	numeroTotalUtilizado = 0;
	for (int i = 0; i < 20; i++)
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
			removeExplosionAtIndex(i);
		}
	}

	// atualiza seu numero de real size
	numeroTotalUtilizado = 0;
	for (int i = 0; i < 20; i++)
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

void ExplosionArray::desenhar()
{
	for (int i = (numeroTotalUtilizado - 1); i >= 0; i--)
	{
		if (array[i].estaVivo())
		{
			array[i].desenhar();
		}
	}
}

int ExplosionArray::getNumeroTotalUtilizado()
{
	return numeroTotalUtilizado;
}

Explosion ExplosionArray::getExplosionAtIndex(int index_)
{
	return array[index_];
}

void ExplosionArray::adicionaNovaExplosion(int x_, int y_)
{
	Explosion local;
	local.inicializar(x_, y_);
	array[numeroTotalUtilizado] = local;
	numeroTotalUtilizado++;
}

void ExplosionArray::removeExplosionAtIndex(int index_)
{
	for (int i = 0; i < (19 - index_); i++)
	{
		array[index_ + i] = array[index_ + i + 1];
	}
}
