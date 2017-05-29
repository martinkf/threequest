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

	//
	//
	//

	//
	int getNumeroTotalUtilizado();
	Explosion getExplosionAtIndex(int index_);
	void removeExplosionAtIndex(int index_);

	//
	void adicionaNovaExplosion(int x_, int y_);
	
	//
	//

private:
	int numeroTotalUtilizado;
	Explosion array[20];
};

