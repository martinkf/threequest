#pragma once
#include "libUnicornio.h"

class SeaElement
{
public:
	// construtores e desconstrutores
	SeaElement();
	~SeaElement();

	// m�todos da lib
	void desenhar();
	void advanceAnimation();

	// m�todos
	void destruir();

	// m�todos get
	bool isInitialized();
	bool estaVivo();
	Sprite getSprite();
	int getX();
	int getY();

	// atributos
	bool initialized;
	bool isAlive;
	Sprite sprite;
	int x;
	int y;
};

