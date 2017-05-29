#include "AirBubble.h"

AirBubble::AirBubble()
{	
}

AirBubble::~AirBubble()
{
}

void AirBubble::inicializar()
{
	// atributo: initialized
	initialized = true;

	// atributo: isAlive
	isAlive = true;

	// atributo: sprite
	if (!gRecursos.carregouSpriteSheet("airBubble"))
	{
		gRecursos.carregarSpriteSheet("airBubble", "imagens/spr_airBubble.png", 1, 4);
	}
	sprite.setSpriteSheet("airBubble");

	// atributo: x
	int spawnRow = rand() % 20;
	x = 20 + (spawnRow * 40);

	// atributo: y
	y = 510;	
}

void AirBubble::atualizar()
{
	verificaOOB();
	advanceAnimation();
	moveXY();
}

void AirBubble::verificaOOB()
{
	if (isAlive && initialized)
	{
		if (y <= 120)
		{
			isAlive = false;
		}
	}
}

void AirBubble::moveXY()
{
	if (isAlive && initialized)
	{
		y -= 1;
	}
}
