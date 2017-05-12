#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"

class Diver
{
public:
	Diver();
	~Diver();

	void inicializar();
	void atualizar();
	void desenhar();

	void destruir();

private:
	int x;
	int y;
	int speed;
	Sprite sprite;
	Direction facingDirection;
};

