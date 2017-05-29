#include "Tiro.h"

Tiro::Tiro()
{
}

Tiro::~Tiro()
{
}

void Tiro::inicializar(ShotType shotType_, int x_, int y_, Direction direction_)
{
	// atributo: initialized
	initialized = true;

	// atributo: isAlive
	isAlive = true;

	// atributo: shotType	
	shotType = shotType_;

	// atributo: shotDirection
	shotDirection = direction_;

	// atributo: x
	if (shotDirection == facingRight)
	{
		x = x_ + 44;
	}
	else 
	{
		x = x_ - 44;
	}

	// atributo: y
	y = y_;	

	// atributo: sprite, shotSpeed
	switch (shotType)
	{
		case shotRegular:
			if (!gRecursos.carregouSpriteSheet("shotRegular"))
			{
				gRecursos.carregarSpriteSheet("shotRegular", "imagens/spr_shotRegular.png");
			}
			sprite.setSpriteSheet("shotRegular");						
			shotSpeed = 5;			
			break;		
		case shotRed:
			if (!gRecursos.carregouSpriteSheet("shotRed"))
			{
				gRecursos.carregarSpriteSheet("shotRed", "imagens/spr_shotRed.png");
			}
			sprite.setSpriteSheet("shotRed");
			shotSpeed = 6;
			break;
		case shotGreen:
			if (!gRecursos.carregouSpriteSheet("shotGreen"))
			{
				gRecursos.carregarSpriteSheet("shotGreen", "imagens/spr_shotGreen.png");
			}
			sprite.setSpriteSheet("shotGreen");
			shotSpeed = 4;
			break;
		case shotBlue:
			if (!gRecursos.carregouSpriteSheet("shotBlue"))
			{
				gRecursos.carregarSpriteSheet("shotBlue", "imagens/spr_shotBlue.png");
			}
			sprite.setSpriteSheet("shotBlue");
			shotSpeed = 3;
			break;
	}	
}

void Tiro::atualizar()
{
	verificaOOB();
	moveXY();
}

void Tiro::verificaOOB()
{
	if (isAlive && initialized)
	{		
		if (x < -sprite.getLargura() / 2 || x > gJanela.getLargura() + sprite.getLargura() / 2)
		{
			isAlive = false;
		}
	}
}

void Tiro::moveXY()
{
	if (isAlive && initialized)
	{
		if (shotType != shotBlue) // pois tiros azuis não se movem
		{
			if (shotDirection == facingLeft)
			{
				x -= shotSpeed;
			}
			else
			{
				x += shotSpeed;
			}
		}
	}
}

ShotType Tiro::getShotType()
{
	return shotType;
}