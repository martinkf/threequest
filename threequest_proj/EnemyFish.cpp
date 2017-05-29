#include "EnemyFish.h"

EnemyFish::EnemyFish()
{	
}

EnemyFish::~EnemyFish()
{
}

void EnemyFish::inicializar()
{
	// atributo: initialized
	initialized = true;

	// atributo: isAlive
	isAlive = true;

	// atributo: sprite, color
	int randm = rand() % 3 + 1;
	switch (randm)
	{
	case 1:		
		if (!gRecursos.carregouSpriteSheet("fishRed"))
		{
			gRecursos.carregarSpriteSheet("fishRed", "imagens/spr_fishRed.png", 1, 4);
		}
		sprite.setSpriteSheet("fishRed");
		color = shotRed;
		break;
	case 2:		
		if (!gRecursos.carregouSpriteSheet("fishGreen"))
		{
			gRecursos.carregarSpriteSheet("fishGreen", "imagens/spr_fishGreen.png", 1, 4);
		}
		sprite.setSpriteSheet("fishGreen");
		color = shotGreen;
		break;
	case 3:		
		if (!gRecursos.carregouSpriteSheet("fishBlue"))
		{
			gRecursos.carregarSpriteSheet("fishBlue", "imagens/spr_fishBlue.png", 1, 4);
		}
		sprite.setSpriteSheet("fishBlue");
		color = shotBlue;
		break;
	}

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

	// atributo: id
	id = rand();

	// atributo: speed
	speed = (rand() % 2) + 1;
}

void EnemyFish::atualizar()
{
	verificaOOB();
	advanceAnimation();
	moveXY();
}

void EnemyFish::verificaOOB()
{
	if (isAlive && initialized)
	{
		if (x > 830 || x < -30)
		{
			isAlive = false;
		}
	}
}

void EnemyFish::moveXY()
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

bool EnemyFish::verificaSemelhanca(EnemyFish input_)
{
	if (id == input_.getId())
	{
		return true;
	}
	return false;
}

int EnemyFish::getId()
{
	return id;
}

ShotType EnemyFish::getColor()
{
	return color;
}