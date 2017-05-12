#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::inicializar()
{
	if (!gRecursos.carregouSpriteSheet("player"))
	{
		gRecursos.carregarSpriteSheet("player", "imagens/spr_player.png", 1, 4);
	}

	sprite.setSpriteSheet("player");
	x = gJanela.getLargura() / 2;
	y = 120;
	isOnSurface = false;
	facingDirection = facingRight;
	sprite.setInverterX(true);
	speed = 6;
}

void Player::atualizar()
{
	// avan�a a anima��o do sprite do player
	sprite.avancarAnimacao();

	// verifica��es referentes a movimenta��o
	if (gTeclado.segurando[TECLA_CIMA] && y > 120)
	{
		int valorASubir = speed;
		int novoY = y - valorASubir;
		if (novoY < 120)
		{
			novoY = 120;
		}
		y = novoY;
	}
	if (gTeclado.segurando[TECLA_BAIXO] && y < 500)
	{
		//y += speed;		
		int valorADescer = speed;
		int novoY = y + valorADescer;
		if (novoY > 500)
		{
			novoY = 500;
		}
		y = novoY;
	}
	if (gTeclado.segurando[TECLA_ESQ] && x > (sprite.getLargura() / 2) + 12)
	{
		x -= speed;
		facingDirection = facingLeft;
		
	}
	if (gTeclado.segurando[TECLA_DIR] && x < (gJanela.getLargura() - sprite.getLargura() / 2) - 12)
	{
		x += speed;
		facingDirection = facingRight;		
	}

	// verifica��es referentes a dire��o (esq/dir)
	if (facingDirection == facingRight) 
	{
		sprite.setInverterX(true);
	}
	else 
	{
		sprite.setInverterX(false);
	}

	// verifica��es referentes a submerg�ncia
	if (y == 120) 
	{
		isOnSurface = true;
	}
	else 
	{
		isOnSurface = false;
	}

	if (isOnSurface)
	{
		// coisas a se fazer quando na superficie aqui
		// TO DO
	}
}

void Player::desenhar()
{
	sprite.desenhar(x, y);
}