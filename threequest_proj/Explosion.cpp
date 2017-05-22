#include "Explosion.h"



Explosion::Explosion()
{
}


Explosion::~Explosion()
{
}

void Explosion::inicializar(int x_, int y_)
{
	if (!gRecursos.carregouSpriteSheet("explosion"))
	{
		gRecursos.carregarSpriteSheet("explosion", "imagens/spr_explosion.png", 1, 6);
	}
	sprite.setSpriteSheet("explosion");

	x = x_;
	y = y_;

	lifeRemaining = 5;
	isAlive = true;
}

void Explosion::atualizar()
{
	sprite.avancarAnimacao();
	lifeRemaining--;
	if (lifeRemaining < 0)
	{
		isAlive = false;
	}
}

void Explosion::desenhar()
{
	sprite.desenhar(x, y);
}

bool Explosion::estaVivo()
{
	return isAlive;
}
