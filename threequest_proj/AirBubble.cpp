#include "AirBubble.h"

AirBubble::AirBubble()
{
	x = 101;
	y = 101;
	isAlive = false;
	initialized = false;
}

AirBubble::~AirBubble()
{
}

void AirBubble::inicializar()
{
	initialized = true;

	// carregando sprite
	if (!gRecursos.carregouSpriteSheet("airBubble"))
	{
		gRecursos.carregarSpriteSheet("airBubble", "imagens/spr_airBubble.png", 1, 4);
	}
	sprite.setSpriteSheet("airBubble");

	y = 510;

	// definindo x do spawn
	int spawnRow = rand() % 20;
	x = 20 + (spawnRow * 40);
	
	// dizendo que está vivo
	isAlive = true;	
}

void AirBubble::atualizar()
{
	if (isAlive && initialized) 
	{
		// avança animação
		sprite.avancarAnimacao();
	
		// verifica out-of-bounds
		if (y <= 120)
		{
			destruir();
		}

		// faz ele andar
		y -= 1;
	}
}

void AirBubble::desenhar()
{
	sprite.desenhar(x, y);
}

void AirBubble::destruir()
{
	isAlive = false;
}

bool AirBubble::estaVivo()
{
	return isAlive;
}

Sprite AirBubble::getSprite()
{
	return sprite;
}

int AirBubble::getX()
{
	return x;
}

int AirBubble::getY()
{
	return y;
}

bool AirBubble::isInitialized()
{
	return initialized;
}

void AirBubble::reset()
{
	initialized = false;
}
