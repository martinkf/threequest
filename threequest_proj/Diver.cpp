#include "Diver.h"

Diver::Diver()
{
}

Diver::~Diver()
{
}

void Diver::inicializar()
{
	// atributo: initialized
	initialized = true;

	// atributo: isAlive
	isAlive = true;

	// atributo: sprite
	if (!gRecursos.carregouSpriteSheet("diver"))
	{
		gRecursos.carregarSpriteSheet("diver", "imagens/spr_diver.png", 1, 4);
	}
	sprite.setSpriteSheet("diver");

	// atributo: x, facingDirection	
	int leftOrRight = rand() % 2;
	if (leftOrRight == 0)
	{
		x = -10;
		facingDirection = facingRight;
		sprite.setInverterX(true);
	}
	else
	{
		x = 810;
		facingDirection = facingLeft;
		
	}

	// atributo: y
	int spawnRow = rand() % 9;
	y = 165 + (spawnRow * 40);

	// atributo: speed
	speed = (rand() % 2) + 1;	
}

void Diver::atualizar()
{	
	verificaOOB();
	advanceAnimation();
	moveXY();
}

void Diver::verificaOOB()
{	
	if (isAlive && initialized)
	{
		if (x > 830 || x < -30)
		{
			isAlive = false;
		}
	}
}

void Diver::moveXY()
{
	if (isAlive && initialized)
	{
		if (facingDirection == facingRight)
		{
			x += speed;
		}
		else
		{
			x -= speed;
		}
	}
}