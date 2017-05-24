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

	bool verificaSemelhanca(EnemyFish input_);

	Sprite getSprite();
	int getX();
	int getY();
	ShotType getShotType();
	int getId();

	bool isInitialized();
	void reset();

private:
	int id;
	int x;
	int y;
	int speed;
	Sprite sprite;
	Direction facingDirection;
	bool isAlive;
	ShotType shotType;

	bool initialized;
};

