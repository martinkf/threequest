#pragma once
#include "SeaElement.h"
#include "MyEnums.h"
#include <ctime>

class EnemySub: public SeaElement
{
public:
	// construtores e desconstrutores
	EnemySub();
	~EnemySub();

	// m�todos da lib
	void inicializar();
	void atualizar();
	void verificaOOB();
	void moveXY();
	void tryToShoot();

	// m�todos
	bool verificaSemelhanca(EnemySub input_);

	void atirar();
	void makeNotWantToShoot();

	// m�todos get
	int getId();
	ShotType getColor();
	Direction getDirection();	
	bool getShootStatus();	

private:
	int id;
	int speed;
	ShotType color;
	Direction facingDirection;	
	bool wantsToShoot;
	int shotCooldown;
};

