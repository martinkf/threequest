#include "EnemySub.h"

EnemySub::EnemySub()
{	
}

EnemySub::~EnemySub()
{
}

void EnemySub::inicializar()
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
		if (!gRecursos.carregouSpriteSheet("subRed"))
		{
			gRecursos.carregarSpriteSheet("subRed", "imagens/spr_subRed.png", 1, 4);
		}
		sprite.setSpriteSheet("subRed");
		color = shotRed;
		break;
	case 2:		
		if (!gRecursos.carregouSpriteSheet("subGreen"))
		{
			gRecursos.carregarSpriteSheet("subGreen", "imagens/spr_subGreen.png", 1, 4);
		}
		sprite.setSpriteSheet("subGreen");
		color = shotGreen;
		break;
	case 3:		
		if (!gRecursos.carregouSpriteSheet("subBlue"))
		{
			gRecursos.carregarSpriteSheet("subBlue", "imagens/spr_subBlue.png", 1, 4);
		}
		sprite.setSpriteSheet("subBlue");
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

	// atributo: wantsToShoot
	wantsToShoot = false;

	// atributo: shotCooldown
	shotCooldown = 0;
}

void EnemySub::atualizar()
{
	verificaOOB();
	advanceAnimation();
	moveXY();
	tryToShoot();
}

void EnemySub::verificaOOB()
{
	if (isAlive && initialized)
	{
		if (x > 830 || x < -30)
		{
			isAlive = false;
		}
	}
}

void EnemySub::moveXY()
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

void EnemySub::tryToShoot()
{
	if (isAlive && initialized)
	{
		// reduz o cooldown do tiro, caso tenha
		if (shotCooldown > 0)
		{
			shotCooldown--;
		}

		// 1 chance em 120, a cada frame, de atirar. chance média de 2 segundos por tiro
		int randm = rand() % 120;
		if (randm == 0)
		{
			if (color != shotBlue) // submarinos azuis não atiram :)
			{
				if (shotCooldown == 0) // somente atira se não está em cooldown
				{
					atirar();
				}
			}
		}
	}
}

ShotType EnemySub::getColor()
{
	return color;
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
	wantsToShoot = true;
	shotCooldown = 120;
}

bool EnemySub::getShootStatus()
{
	return wantsToShoot;
}

void EnemySub::makeNotWantToShoot()
{
	wantsToShoot = false;
}