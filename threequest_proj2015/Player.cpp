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
	speed = 4;
	shotType = shotBlue;
	shotArray = TiroArray();
	shotArray.inicializar();
	maxOxygen = 2300;
	oxygenLeft = maxOxygen;
	numberDivers = 0;		 
}

void Player::atualizar()
{
	// avança a animação do sprite do player
	sprite.avancarAnimacao();

	// verificações referentes a velocidade do submarino do player
	switch (numberDivers)
	{
	case 0:
	case 1:
		speed = 4;
		break;
	case 2:
	case 3:
		speed = 3;
		break;
	case 4:
	case 5:
		speed = 2;
		break;
	case 6:
		speed = 1;
		break;
	}

	// verificações referentes a movimentação
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

	// verificações referentes a direção (esq/dir)
	if (facingDirection == facingRight) 
	{
		sprite.setInverterX(true);
	}
	else 
	{
		sprite.setInverterX(false);
	}

	// verificações referentes a submergência
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
		if (oxygenLeft <= maxOxygen) 
		{
			if (oxygenLeft + 9 > maxOxygen)
			{
				oxygenLeft = maxOxygen;
			} 
			else
			{
				oxygenLeft += 9;
			}
		}
		if (numberDivers > 0)
		{
			numberDivers--;
		}
	}
	else
	{
		oxygenLeft--;
	}

	// verificações referentes a oxigênio disponível
	if (oxygenLeft == 0)
	{
		// MATAR O PLAYER POR FALTA DE OXIGÊNIO
	}

	// verificações referentes a atirar
	if (gTeclado.pressionou[TECLA_ESPACO] && !isOnSurface)
	{
		atirar();
	}
	
	// atualiza os tiros
	for (int i = 0; i < shotArray.retornaNumeroTotalTiros(); i++)
	{
		Tiro test;
		test = shotArray.retornaTiroAtIndex(i);
		if (test.estaVivo())
		{
			test.atualizar();
			shotArray.adicionaTiroNesteIndex(test, i);
		}
		else 
		{
			shotArray.removeTiroAtIndex(i);
		}		
	}
}

void Player::desenhar()
{
	// desenha o player
	sprite.desenhar(x, y);

	// desenha os tiros
	for (int i = 0; i < shotArray.retornaNumeroTotalTiros(); i++)
	{
		shotArray.retornaTiroAtIndex(i).desenhar();
	}
}

void Player::atirar()
{
	Tiro tiro = Tiro();
	tiro.inicializar(shotType, x, y, facingDirection);
	shotArray.adicionaTiroNaLista(tiro);
}

bool Player::tryAddOneDiver()
{
	if (numberDivers < 6) 
	{		
		return true;
	}
	else 
	{
		return false;
	}	
}

void Player::addOneDiver()
{
	numberDivers++;
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

int Player::getOxygenLeft()
{
	return oxygenLeft;
}

int Player::getNumberDivers()
{
	return numberDivers;
}
