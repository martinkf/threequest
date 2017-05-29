#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::inicializar()
{
	// atributo: initialized
	initialized = true;

	// atributo: isAlive
	isAlive = true;

	// atributo: sprite
	if (!gRecursos.carregouSpriteSheet("player"))
	{
		gRecursos.carregarSpriteSheet("player", "imagens/spr_player.png", 1, 4);
	}
	sprite.setSpriteSheet("player");
	sprite.setInverterX(true);
	sprite.setVelocidadeAnimacao(5);

	// atributo: x
	x = gJanela.getLargura() / 2;

	// atributo: y
	y = 120;
	
	// atributo: facingDirection	
	facingDirection = facingRight;

	// atributo: isFrozen
	isFrozen = false;

	// atributo: isOnSurface
	isOnSurface = true;

	// atributo: shotType	
	shotType = shotRegular;

	// atributo: wantsToShoot
	wantsToShoot = false;
	
}

void Player::atualizar()
{
	// avança a animação do sprite do player
	advanceAnimation();

	// verificações referentes a submergência
	if (y == 120)
	{
		isOnSurface = true;
	}
	else
	{
		isOnSurface = false;
	}

	if (!(isFrozen)) 
	{
		// verificações referentes a movimentação
		if ((gTeclado.segurando[TECLA_W] || gTeclado.segurando[TECLA_CIMA]) && y > 120)
		{			
			int novoY = y - 3;
			if (novoY < 120)
			{
				novoY = 120;
			}
			y = novoY;
		}
		if ((gTeclado.segurando[TECLA_D] || gTeclado.segurando[TECLA_DIR]) && x < (gJanela.getLargura() - sprite.getLargura() / 2) - 12)
		{
			x += 3;
			facingDirection = facingRight;
			sprite.setInverterX(true);
		}
		if ((gTeclado.segurando[TECLA_S] || gTeclado.segurando[TECLA_BAIXO]) && y < 500)
		{				
			int novoY = y + 3;
			if (novoY > 500)
			{
				novoY = 500;
			}
			y = novoY;
		}
		if ((gTeclado.segurando[TECLA_A] || gTeclado.segurando[TECLA_ESQ]) && x > (sprite.getLargura() / 2) + 12)
		{
			x -= 3;
			facingDirection = facingLeft;
			sprite.setInverterX(false);
		}

		// verificações referentes a atirar
		if (gTeclado.pressionou[TECLA_ESPACO] && !isOnSurface)
		{
			atirar();
		}
	}
}

void Player::freeze()
{
	isFrozen = true;
}

void Player::unfreeze()
{
	isFrozen = false;
}

void Player::changeShotType(ShotType _input)
{
	shotType = _input;
}

void Player::atirar()
{
	wantsToShoot = true;	
}

void Player::makeNotWantToShoot()
{
	wantsToShoot = false;
}

ShotType Player::getShotType()
{
	return shotType;
}

Direction Player::getDirection()
{
	return facingDirection;
}

bool Player::getSurfaceStatus()
{
	return isOnSurface;
}

bool Player::getShootStatus()
{
	return wantsToShoot;
}