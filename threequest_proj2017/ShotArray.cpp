#include "ShotArray.h"

ShotArray::ShotArray()
{
	numeroTotalUtilizado = 0;
}

ShotArray::~ShotArray()
{
}

int ShotArray::retornaNumeroTotalTiros()
{
	return numeroTotalUtilizado;
}

Tiro ShotArray::retornaTiroAtIndex(int index_)
{	
	return array[index_];
}

void ShotArray::adicionaTiroNaLista(Tiro tiro_)
{
	array[numeroTotalUtilizado] = tiro_;
	numeroTotalUtilizado++;
}

void ShotArray::removeTiroAtIndex(int index_)
{	
	for (int i = index_; i < (numeroTotalUtilizado - 1); i++)
	{
		array[i] = array[i + 1];
	}
	numeroTotalUtilizado--;
}

void ShotArray::adicionaTiroNesteIndex(Tiro tiro_, int index_)
{
	array[index_] = tiro_;
}
