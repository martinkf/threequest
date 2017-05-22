#pragma once
#include "libUnicornio.h"

class AirBubble
{
public:
	AirBubble();
	~AirBubble();

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
	Sprite sprite;
	bool isAlive;

	bool initialized = false;
};

