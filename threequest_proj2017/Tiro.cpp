#include "Tiro.h"



Tiro::Tiro()
{
}


Tiro::~Tiro()
{
}

void Tiro::inicializar(ShotType shotType_, int x_, int y_, Direction direction_)
{
	int xOffset = 0;
	int yOffset = 0;

	switch (shotType_)
	{
		case shotRegular:
			if (!gRecursos.carregouSpriteSheet("shotRegular"))
			{
				gRecursos.carregarSpriteSheet("shotRegular", "imagens/spr_shotRegular.png");
			}
			sprite.setSpriteSheet("shotRegular");

			shotSpeed = 3;
			xOffset = 44;
			yOffset = 0;
			break;		
		case shotRed:
			if (!gRecursos.carregouSpriteSheet("shotRed"))
			{
				gRecursos.carregarSpriteSheet("shotRed", "imagens/spr_shotRed.png");
			}
			sprite.setSpriteSheet("shotRed");

			shotSpeed = 4;
			xOffset = 44;
			yOffset = 0;
			break;
		case shotGreen:
			if (!gRecursos.carregouSpriteSheet("shotGreen"))
			{
				gRecursos.carregarSpriteSheet("shotGreen", "imagens/spr_shotGreen.png");
			}
			sprite.setSpriteSheet("shotGreen");

			shotSpeed = 2;
			xOffset = 44;
			yOffset = 0;
			break;
		case shotBlue:
			if (!gRecursos.carregouSpriteSheet("shotBlue"))
			{
				gRecursos.carregarSpriteSheet("shotBlue", "imagens/spr_shotBlue.png");
			}
			sprite.setSpriteSheet("shotBlue");

			shotSpeed = 1;
			xOffset = 44;
			yOffset = 0;
			break;
	}
	shotDirection = direction_;
	y = y_ + yOffset;

	switch (shotDirection)
	{
		case facingLeft:
			x = x_ - xOffset;
			break;
		case facingRight:
			x = x_ + xOffset;
			break;
	}

	isAlive = true;

}

void Tiro::atualizar()
{
	if (isAlive)
	{		
		if (shotDirection == facingLeft)
		{
			x -= shotSpeed;
		}
		else
		{
			x += shotSpeed;
		}
		if (x < -sprite.getLargura() / 2 || x > gJanela.getLargura() + sprite.getLargura() / 2)
		{
			destruir();
		}
	}
}

void Tiro::desenhar()
{
	if (isAlive)
	{
		sprite.desenhar(x, y);
	}
}

void Tiro::destruir()
{
	isAlive = false;
}

bool Tiro::estaVivo()
{
	return isAlive;
}