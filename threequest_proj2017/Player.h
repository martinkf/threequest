#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"
#include "Tiro.h"
#include "TiroArray.h"

class Player
{
public:
	Player();
	~Player();

	void inicializar();
	void atualizar();
	void desenhar();	

	void atirar();

	int getX();
	int getY();
	Direction getDirection();
	Sprite getSprite();
	TiroArray getTiroArray();
	void setTiroArray(TiroArray _input);
	bool isPlayerOnSurface();

private:
	int x;
	int y;
	int speed;
	Sprite sprite;
	Direction facingDirection;
	bool isOnSurface;
	ShotType shotType;
	TiroArray tiroArray;
};

