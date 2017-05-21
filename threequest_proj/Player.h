#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"

class Player
{
public:
	Player();
	~Player();

	void inicializar();
	void atualizar();
	void desenhar();	

	void atirar();

	ShotType getShotType();
	int getX();
	int getY();
	Direction getDirection();
	Sprite getSprite();
	bool isPlayerOnSurface();

	void changeShotType(ShotType _input);
	bool wantsToShoot();
	void makeNotWantToShoot();
	
private:
	int x;
	int y;
	int speed;
	Sprite sprite;
	Direction facingDirection;
	bool isOnSurface;
	ShotType shotType;
	bool playerWantsToShoot;
};

