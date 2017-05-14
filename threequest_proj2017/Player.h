#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"
#include "Tiro.h"
#include "ShotArray.h"

class Player
{
public:
	Player();
	~Player();

	void inicializar();
	void atualizar();
	void desenhar();	

	void atirar();
	bool tryAddOneDiver();
	void addOneDiver();

	int getX();
	int getY();
	Direction getDirection();
	Sprite getSprite();
	int getOxygenLeft();
	int getNumberDivers();

private:
	int x;
	int y;
	int speed;
	Sprite sprite;
	Direction facingDirection;
	bool isOnSurface;
	ShotType shotType;
	ShotArray shotArray;
	int oxygenLeft;
	int numberDivers;
};

