#include "Player.h"
#include "Jogo.h"

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
	speed = 3;
	shotType = shotRegular;
	tiroArray = TiroArray();
	tiroArray.inicializar();
}

void Player::atualizar()
{
	// avan�a a anima��o do sprite do player
	sprite.avancarAnimacao();

	// atualiza os tiros
	tiroArray.atualizar();

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

	// verifica��es referentes a atirar
	if (gTeclado.pressionou[TECLA_ESPACO] && !isOnSurface)
	{
		atirar();
	}
}

void Player::desenhar()
{
	// desenha o player
	sprite.desenhar(x, y);

	// desenha os tiros
	tiroArray.desenhar();
}

void Player::atirar()
{
	Tiro tiro = Tiro();
	tiro.inicializar(shotType, x, y, facingDirection);
	tiroArray.adicionaTiroNaLista(tiro);
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

Direction Player::getDirection()
{
	return facingDirection;
}

Sprite Player::getSprite()
{
	return sprite;
}

TiroArray Player::getTiroArray()
{
	return tiroArray;
}

void Player::setTiroArray(TiroArray _input)
{
	tiroArray = _input;
}

bool Player::isPlayerOnSurface()
{
	return isOnSurface;
}
