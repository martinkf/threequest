#include "EnemyFish.h"

EnemyFish::EnemyFish()
{
	id = 101;
	x = 101;
	y = 101;
	isAlive = false;
	initialized = false;
}

EnemyFish::~EnemyFish()
{
}

void EnemyFish::inicializar()
{
	initialized = true;

	// DETERMINA A COR DESSE PEIXE E CARREGA SPRITE
	int randm = rand() % 3 + 1;
	switch (randm)
	{
	case 1:
		shotType = shotRed;
		if (!gRecursos.carregouSpriteSheet("fishRed"))
		{
			gRecursos.carregarSpriteSheet("fishRed", "imagens/spr_fishRed.png", 1, 4);
		}
		sprite.setSpriteSheet("fishRed");
		break;
	case 2:
		shotType = shotGreen;
		if (!gRecursos.carregouSpriteSheet("fishGreen"))
		{
			gRecursos.carregarSpriteSheet("fishGreen", "imagens/spr_fishGreen.png", 1, 4);
		}
		sprite.setSpriteSheet("fishGreen");
		break;
	case 3:
		shotType = shotBlue;
		if (!gRecursos.carregouSpriteSheet("fishBlue"))
		{
			gRecursos.carregarSpriteSheet("fishBlue", "imagens/spr_fishBlue.png", 1, 4);
		}
		sprite.setSpriteSheet("fishBlue");
		break;
	}

	// definindo spawn na esquerda ou direita
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

	// definindo y do spawn
	int spawnRow = rand() % 9;
	y = 165 + (spawnRow * 40);

	// definindo speed
	speed = (rand() % 2) + 1;

	// dizendo que está vivo
	isAlive = true;

	// dá um random id
	id = rand();
}

void EnemyFish::atualizar()
{
	if (isAlive && initialized)
	{	
		// avança animação
		sprite.avancarAnimacao();
		
		// verifica out-of-bounds
		if (x > 830 || x < -30)
		{
			destruir();
		}

		// faz ele andar
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

void EnemyFish::desenhar()
{
	sprite.desenhar(x, y);
}

void EnemyFish::destruir()
{
	isAlive = false;
}

bool EnemyFish::estaVivo()
{
	return isAlive;
}

bool EnemyFish::verificaSemelhanca(EnemyFish input_)
{
	if (id == input_.getId())
	{
		return true;
	}
	return false;
}

Sprite EnemyFish::getSprite()
{
	return sprite;
}

int EnemyFish::getX()
{
	return x;
}

int EnemyFish::getY()
{
	return y;
}

ShotType EnemyFish::getShotType()
{
	return shotType;
}

int EnemyFish::getId()
{
	return id;
}

bool EnemyFish::isInitialized()
{
	return initialized;
}

void EnemyFish::reset()
{
	initialized = false;
}
