#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"
#include <ctime>

class EnemyFish
{
public:
	EnemyFish();
	~EnemyFish();

	void inicializar();
	void atualizar();
	void desenhar();

	void destruir();
	bool estaVivo();

	Sprite getSprite();
	int getX();
	int getY();
	ShotType getShotType();

private:
	int x;
	int y;
	int speed;
	Sprite sprite;
	Direction facingDirection;
	bool isAlive;
	ShotType shotType;
};

