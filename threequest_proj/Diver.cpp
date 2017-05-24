#include "Diver.h"

Diver::Diver()
{
	x = 101;
	y = 101;
	isAlive = false;
	initialized = false;
}

Diver::~Diver()
{
}

void Diver::inicializar()
{
	initialized = true;

	// carregando sprite
	if (!gRecursos.carregouSpriteSheet("diver"))
	{
		gRecursos.carregarSpriteSheet("diver", "imagens/spr_diver.png", 1, 4);
	}
	sprite.setSpriteSheet("diver");

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

void Diver::atualizar()
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

void Diver::desenhar()
{
	sprite.desenhar(x, y);
}

void Diver::destruir()
{	
	isAlive = false;
}

bool Diver::estaVivo()
{
	return isAlive;
}

Sprite Diver::getSprite()
{
	return sprite;
}

int Diver::getX()
{
	return x;
}

int Diver::getY()
{
	return y;
}

bool Diver::isInitialized()
{
	return initialized;
}

void Diver::reset()
{
	initialized = false;
}
