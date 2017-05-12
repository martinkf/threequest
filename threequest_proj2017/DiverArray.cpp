#include "DiverArray.h"

DiverArray::DiverArray()
{
	numeroTotalUtilizado = 0;
}

DiverArray::~DiverArray()
{
}

void DiverArray::inicializar()
{
	numeroTotalUtilizado = 0;
}

void DiverArray::atualizar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		Diver local;
		local = array[i];
		if (local.estaVivo())
		{
			local.atualizar();
			array[i] = local;
		}
		else
		{
			removeDiverAtIndex(i);
		}
	}
}

void DiverArray::desenhar()
{
	for (int i = 0; i < numeroTotalUtilizado; i++)
	{
		array[i].desenhar();
	}
}

void DiverArray::adicionaDiverNaLista(Diver diver_)
{
	array[numeroTotalUtilizado] = diver_;
	numeroTotalUtilizado++;
}

void DiverArray::removeDiverAtIndex(int index_)
{
	for (int i = index_; i < (numeroTotalUtilizado - 1); i++)
	{
		array[i] = array[i + 1];
	}
	numeroTotalUtilizado--;
}

void DiverArray::spawnNewRandomDiver()
{
	Diver local = Diver();
	local.inicializar();
	array[numeroTotalUtilizado] = local;
	numeroTotalUtilizado++;
}
