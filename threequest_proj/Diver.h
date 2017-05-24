#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"
#include <ctime>

class Diver
{
public:
	Diver();
	~Diver();

	void inicializar();
	void atualizar();
	void desenhar();

	void destruir();
	bool estaVivo();

	Sprite getSprite();
	int getX();
	int getY();

	bool isInitialized();
	void reset();

private:
	int x;
	int y;
	int speed;
	Sprite sprite;
	Direction facingDirection;
	bool isAlive;

	bool initialized;
};

