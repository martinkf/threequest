#pragma once
#include "Explosion.h"

class ExplosionArray
{
public:
	ExplosionArray();
	~ExplosionArray();

	void inicializar();
	void atualizar();
	void desenhar();

	int getNumeroTotalUtilizado();
	Explosion getExplosionAtIndex(int index_);

	void adicionaExplosionNaLista(Explosion explosion_);
	void removeExplosionAtIndex(int index_);

private:
	int numeroTotalUtilizado;
	Explosion array[50];
};

