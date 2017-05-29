#pragma once
#include "libUnicornio.h"

class SeaElement
{
public:
	// construtores e desconstrutores
	SeaElement();
	~SeaElement();

	// métodos da lib
	void desenhar();
	void advanceAnimation();

	// métodos
	void destruir();

	// métodos get
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

