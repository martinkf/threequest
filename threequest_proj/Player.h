#pragma once
#include "SeaElement.h"
#include "MyEnums.h"

class Player: public SeaElement
{
public:
	// construtores e desconstrutores
	Player();
	~Player();

	// m�todos da lib
	void inicializar();
	void atualizar();

	// m�todos
	void freeze();
	void unfreeze();

	void changeShotType(ShotType _input);
	void atirar();
	void makeNotWantToShoot();

	// m�todos get
	ShotType getShotType();
	Direction getDirection();
	bool getSurfaceStatus();
	bool getShootStatus();

private:
	// atributos
	Direction facingDirection;
	bool isFrozen;

	bool isOnSurface;
	
	ShotType shotType;
	bool wantsToShoot;	
};

