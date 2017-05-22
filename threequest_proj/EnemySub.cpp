#include "EnemySub.h"



EnemySub::EnemySub()
{
}


EnemySub::~EnemySub()
{
}

void EnemySub::inicializar()
{
	// DETERMINA A COR DESSE SUB E CARREGA SPRITE
	int randm = rand() % 3 + 1;
	switch (randm)
	{
	case 1:
		shotType = shotRed;
		if (!gRecursos.carregouSpriteSheet("subRed"))
		{
			gRecursos.carregarSpriteSheet("subRed", "imagens/spr_subRed.png", 1, 4);
		}
		sprite.setSpriteSheet("subRed");
		break;
	case 2:
		shotType = shotGreen;
		if (!gRecursos.carregouSpriteSheet("subGreen"))
		{
			gRecursos.carregarSpriteSheet("subGreen", "imagens/spr_subGreen.png", 1, 4);
		}
		sprite.setSpriteSheet("subGreen");
		break;
	case 3:
		shotType = shotBlue;
		if (!gRecursos.carregouSpriteSheet("subBlue"))
		{
			gRecursos.carregarSpriteSheet("subBlue", "imagens/spr_subBlue.png", 1, 4);
		}
		sprite.setSpriteSheet("subBlue");
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

	// não nasce já querendo atirar pls
	subWantsToShoot = false;
	shotCooldown = 0;

	// obtém uma random id
	id = rand();	
}

void EnemySub::atualizar()
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

	// reduz o cooldown do tiro, caso tenha
	if (shotCooldown > 0) 
	{
		shotCooldown--;
	}

	// 1 chance em 120, a cada frame, de atirar. chance média de 2 segundos por tiro
	int randm = rand() % 120;
	if (randm == 0)
	{
		if (shotType != shotBlue) // submarinos azuis não atiram :)
		{
			if (shotCooldown == 0) // somente atira se não está em cooldown
			{
				atirar();
			}
		}
	}

	// verifica out-of-bounds
	if (x > 830 || x < -30)
	{
		destruir();
	}
}

void EnemySub::desenhar()
{
	sprite.desenhar(x, y);
}

void EnemySub::destruir()
{
	isAlive = false;
}

bool EnemySub::estaVivo()
{
	return isAlive;
}

Sprite EnemySub::getSprite()
{
	return sprite;
}

int EnemySub::getX()
{
	return x;
}

int EnemySub::getY()
{
	return y;
}

ShotType EnemySub::getShotType()
{
	return shotType;
}

Direction EnemySub::getDirection()
{
	return facingDirection;
}

int EnemySub::getId()
{
	return id;
}

bool EnemySub::verificaSemelhanca(EnemySub input_)
{
	if (id == input_.getId())
	{
		return true;
	}
	return false;
}

void EnemySub::atirar()
{
	subWantsToShoot = true;
	shotCooldown = 120;
}

bool EnemySub::wantsToShoot()
{
	return subWantsToShoot;
}

void EnemySub::makeNotWantToShoot()
{
	subWantsToShoot = false;
}
