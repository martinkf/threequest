#include "AirBubble.h"



AirBubble::AirBubble()
{
}


AirBubble::~AirBubble()
{
}

void AirBubble::inicializar()
{
	// carregando sprite
	if (!gRecursos.carregouSpriteSheet("airBubble"))
	{
		gRecursos.carregarSpriteSheet("airBubble", "imagens/spr_airBubble.png", 1, 4);
	}
	sprite.setSpriteSheet("airBubble");

	y = 510;

	// definindo x do spawn
	int spawnRow = rand() % 20;
	x = 20 + (spawnRow * 40);
	
	// dizendo que está vivo
	isAlive = true;
}

void AirBubble::atualizar()
{
	// avança animação
	sprite.avancarAnimacao();

	// faz ele andar
	y -= 1;

	// verifica out-of-bounds
	if (y <= 120)
	{
		destruir();
	}
}

void AirBubble::desenhar()
{
	sprite.desenhar(x, y);
}

void AirBubble::destruir()
{
	isAlive = false;
}

bool AirBubble::estaVivo()
{
	return isAlive;
}

Sprite AirBubble::getSprite()
{
	return sprite;
}

int AirBubble::getX()
{
	return x;
}

int AirBubble::getY()
{
	return y;
}
