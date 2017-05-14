#include "Diver.h"
#include <ctime>

Diver::Diver()
{
}

Diver::~Diver()
{
}

void Diver::inicializar()
{
	// carregando sprite
	if (!gRecursos.carregouSpriteSheet("diver"))
	{
		gRecursos.carregarSpriteSheet("diver", "imagens/spr_diver.png", 1, 4);
	}
	sprite.setSpriteSheet("diver");

	// configurando o random
	srand(time(0));

	// definindo spawn na esquerda ou direita
	int leftOrRight = rand() % 2;
	if (leftOrRight == 0)
	{
		x = -10;
		facingDirection = facingRight;
	}
	else
	{
		x = 810;
		facingDirection = facingLeft;
		sprite.setInverterX(true);
	}

	// definindo altura do spawn
	int spawnHeight = rand() % 320;
	y = 150 + spawnHeight;

	// definindo speed
	speed = (rand() % 2) + 1;

	// dizendo que está vivo
	isAlive = true;
}

void Diver::atualizar()
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

	// verificar quase-colisão com inimigos (andar mais rápido)
	// to do

	// verificar colisão com player (se destruir + melhorar score do player)
	// to do
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
