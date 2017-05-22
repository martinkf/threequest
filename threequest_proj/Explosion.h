#pragma once
#include "libUnicornio.h"

class Explosion
{
public:
	Explosion();
	~Explosion();

	void inicializar(int x_, int y_);
	void atualizar();
	void desenhar();

	bool estaVivo();

private:
	Sprite sprite;
	int x;
	int y;
	int lifeRemaining;
	bool isAlive;
};

