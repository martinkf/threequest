#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"

class Tiro
{
public:
	Tiro();
	~Tiro();

	void inicializar(ShotType shotType_, int x_, int y_, Direction direction_);
	void atualizar();
	void desenhar();

	void destruir();

	bool estaVivo();
private:
	Sprite sprite;
	int x;
	int y;
	Direction shotDirection;
	bool isAlive;
	int shotSpeed;
};
