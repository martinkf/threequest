#include "Enemy.h"

Enemy::Enemy()
{	
}

Enemy::~Enemy()
{
}

void Enemy::inicializar()
{
	// atributo: enemyType
	int randm = rand() % 2;
	if (randm == 0)
	{
		enemyType = enemySub;
	}
	else
	{
		enemyType = enemyFish;
	}

	// atributo: initialized
	initialized = true;

	// atributo: isAlive
	isAlive = true;

	// atributo: color
	int randm2 = rand() % 3 + 1;
	switch (randm2)
	{
	case 1:
		color = shotRed;
		break;
	case 2:
		color = shotGreen;
		break;
	case 3:
		color = shotBlue;
		break;
	}

	// atributo: sprite
	switch (enemyType)
	{
		case enemyFish:
			switch (color)
			{
				case shotRed:
					if (!gRecursos.carregouSpriteSheet("fishRed"))
					{
						gRecursos.carregarSpriteSheet("fishRed", "imagens/spr_fishRed.png", 1, 4);
					}
					sprite.setSpriteSheet("fishRed");
					break;
				case shotGreen:
					if (!gRecursos.carregouSpriteSheet("fishGreen"))
					{
						gRecursos.carregarSpriteSheet("fishGreen", "imagens/spr_fishGreen.png", 1, 4);
					}
					sprite.setSpriteSheet("fishGreen");
					break;
				case shotBlue:
					if (!gRecursos.carregouSpriteSheet("fishBlue"))
					{
						gRecursos.carregarSpriteSheet("fishBlue", "imagens/spr_fishBlue.png", 1, 4);
					}
					sprite.setSpriteSheet("fishBlue");
					break;
			}
			break;
		case enemySub:
			switch (color)
			{
				case shotRed:
					if (!gRecursos.carregouSpriteSheet("subRed"))
					{
						gRecursos.carregarSpriteSheet("subRed", "imagens/spr_subRed.png", 1, 4);
					}
					sprite.setSpriteSheet("subRed");
					break;
				case shotGreen:
					if (!gRecursos.carregouSpriteSheet("subGreen"))
					{
						gRecursos.carregarSpriteSheet("subGreen", "imagens/spr_subGreen.png", 1, 4);
					}
					sprite.setSpriteSheet("subGreen");
					break;
				case shotBlue:
					if (!gRecursos.carregouSpriteSheet("subBlue"))
					{
						gRecursos.carregarSpriteSheet("subBlue", "imagens/spr_subBlue.png", 1, 4);
					}
					sprite.setSpriteSheet("subBlue");
					break;
			}
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

void Enemy::atualizar()
{
	verificaOOB();
	advanceAnimation();
	moveXY();
	if (enemyType == enemySub)
	{
		tryToShoot();
	}
}

void Enemy::verificaOOB()
{
	if (isAlive && initialized)
	{
		if (x > 830 || x < -30)
		{
			isAlive = false;
		}
	}
}

void Enemy::moveXY()
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

void Enemy::tryToShoot()
{
	if (isAlive && initialized && (enemyType == enemySub))
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

ShotType Enemy::getColor()
{
	return color;
}

Direction Enemy::getDirection()
{
	return facingDirection;
}

EnemyType Enemy::getEnemyType()
{
	return enemyType;
}

int Enemy::getId()
{
	return id;
}

bool Enemy::verificaSemelhanca(Enemy input_)
{
	if (id == input_.getId())
	{
		return true;
	}
	return false;
}

void Enemy::atirar()
{
	if (enemyType == enemySub) 
	{
		wantsToShoot = true;
		shotCooldown = 120;
	}
}

bool Enemy::getShootStatus()
{
	return wantsToShoot;
}

void Enemy::makeNotWantToShoot()
{
	wantsToShoot = false;
}