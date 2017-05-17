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

private:
	int x;
	int y;
	Sprite sprite;
	bool isAlive;
};

