#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"
#include <ctime>

class EnemySub
{
public:
	EnemySub();
	~EnemySub();

	void inicializar();
	void atualizar();
	void desenhar();

	void destruir();
	bool estaVivo();

	Sprite getSprite();
	int getX();
	int getY();
	ShotType getShotType();
	Direction getDirection();
	int getId();

	bool verificaSemelhanca(EnemySub input_);

	void atirar();
	bool wantsToShoot();
	void makeNotWantToShoot();

private:
	int id;
	int x;
	int y;
	int speed;
	Sprite sprite;
	Direction facingDirection;
	bool isAlive;
	ShotType shotType;
	bool subWantsToShoot;
	int shotCooldown;
};

