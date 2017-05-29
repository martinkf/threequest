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

	// métodos da lib
	void inicializar();
	void atualizar();
	void verificaOOB();
	void moveXY();
	void tryToShoot();

	// métodos
	bool verificaSemelhanca(Enemy input_);

	void atirar();
	void makeNotWantToShoot();

	// métodos get
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

