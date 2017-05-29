#include "Explosion.h"

Explosion::Explosion()
{	
}

Explosion::~Explosion()
{
}

void Explosion::inicializar(int x_, int y_)
{
	// atributo: initialized
	initialized = true;

	// atributo: isAlive
	isAlive = true;

	// atributo: x
	x = x_;

	// atributo: y
	y = y_;

	// atributo: sprite
	if (!gRecursos.carregouSpriteSheet("explosion"))
	{
		gRecursos.carregarSpriteSheet("explosion", "imagens/spr_explosion.png", 1, 6);
	}
	sprite.setSpriteSheet("explosion");
	sprite.setVelocidadeAnimacao(16);
}

void Explosion::atualizar()
{
	verificaAnimation();
	advanceAnimation();
}

void Explosion::verificaAnimation()
{
	if (isAlive && initialized)
	{
		if (sprite.getFrame() == 5)
		{
			isAlive = false;
		}
	}
}