#include "EnemyFish.h"

EnemyFish::EnemyFish()
{
}

EnemyFish::~EnemyFish()
{
}

void EnemyFish::inicializar()
{
	// DETERMINA A COR DESSE PEIXE E CARREGA SPRITE
	int randm = rand() % 3 + 1;
	switch (randm)
	{
	case 1:
		colour = red;
		if (!gRecursos.carregouSpriteSheet("fishRed"))
		{
			gRecursos.carregarSpriteSheet("fishRed", "imagens/spr_fishRed.png", 1, 4);
		}
		sprite.setSpriteSheet("fishRed");
		break;
	case 2:
		colour = green;
		if (!gRecursos.carregouSpriteSheet("fishGreen"))
		{
			gRecursos.carregarSpriteSheet("fishGreen", "imagens/spr_fishGreen.png", 1, 4);
		}
		sprite.setSpriteSheet("fishGreen");
		break;
	case 3:
		colour = blue;
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
}

void EnemyFish::atualizar()
{
	// avança animação
	sprite.avancarAnimacao();

	// faz ele andar
	if (facingDirection == facingRight)
	{
		x += speed;
	}
	else
	{
		x -= speed;
	}

	// verifica out-of-bounds
	if (x > 830 || x < -30)
	{
		destruir();
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
