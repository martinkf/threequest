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
}

void ExplosionArray::atualizar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		Explosion test;
		test = array[i];
		if (test.estaVivo())
		{
			test.atualizar();
			array[i] = test;
		}
		else
		{
			removeExplosionAtIndex(i);
		}
	}
}

void ExplosionArray::desenhar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		array[i].desenhar();
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

void ExplosionArray::adicionaExplosionNaLista(Explosion explosion_)
{
	array[numeroTotalUtilizado] = explosion_;
	numeroTotalUtilizado++;
}

void ExplosionArray::removeExplosionAtIndex(int index_)
{
	for (int i = index_; i < (numeroTotalUtilizado - 1); i++)
	{
		array[i] = array[i + 1];
	}
	numeroTotalUtilizado--;
}
