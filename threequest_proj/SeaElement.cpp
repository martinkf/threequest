#include "SeaElement.h"

SeaElement::SeaElement()
{
	x = 101;
	y = 101;
	isAlive = false;
	initialized = false;
}

SeaElement::~SeaElement()
{
}

void SeaElement::desenhar()
{
	if (isAlive) 
	{
		sprite.desenhar(x, y);
	}
}

void SeaElement::advanceAnimation()
{
	if (isAlive && initialized)
	{
		sprite.avancarAnimacao();
	}
}

bool SeaElement::isInitialized()
{
	return initialized;
}

bool SeaElement::estaVivo()
{
	return isAlive;
}

void SeaElement::destruir()
{
	isAlive = false;
}

Sprite SeaElement::getSprite()
{
	return sprite;
}

int SeaElement::getX()
{
	return x;
}

int SeaElement::getY()
{
	return y;
}