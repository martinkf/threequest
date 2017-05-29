#pragma once
#include "SeaElement.h"
#include "MyEnums.h"
#include <ctime>

class Enemy: public SeaElement
{
public:
	// construtores e desconstrutores
	Enemy();
	~Enemy();

	// m�todos da lib
	void inicializar();
	void atualizar();
	void verificaOOB();
	void moveXY();
	void tryToShoot();

	// m�todos
	bool verificaSemelhanca(Enemy input_);

	void atirar();
	void makeNotWantToShoot();

	// m�todos get
	EnemyType getEnemyType();
	int getId();
	ShotType getColor();
	Direction getDirection();	
	bool getShootStatus();	

private:
	EnemyType enemyType;

	int id;
	int speed;
	ShotType color;
	Direction facingDirection;	
	bool wantsToShoot;
	int shotCooldown;	
};

