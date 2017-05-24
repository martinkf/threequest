#include "Explosion.h"

Explosion::Explosion()
{
	x = 101;
	y = 101;
	isAlive = false;
	initialized = false;
}

Explosion::~Explosion()
{
}

void Explosion::inicializar(int x_, int y_)
{
	initialized = true;

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
	if (isAlive && initialized)
	{
		// avança animação
		sprite.avancarAnimacao();

		// reduz a vida útil restante
		lifeRemaining--;

		// verifica e assassina
		if (lifeRemaining < 0)
		{
			isAlive = false;
		}
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

bool Explosion::isInitialized()
{
	return initialized;
}

void Explosion::reset()
{
	initialized = false;
}
