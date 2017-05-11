#pragma once
#include "libUnicornio.h"

enum Direction { facingLeft, facingRight };

class Player
{
public:
	Player();
	~Player();

	void inicializar();
	void atualizar();
	void desenhar();	

private:
	float x;
	float y;
	int speed;
	Sprite sprite;
	Direction facingDirection;
	bool isOnSurface;
};

