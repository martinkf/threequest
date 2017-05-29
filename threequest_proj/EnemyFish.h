#pragma once
#include "SeaElement.h"
#include "MyEnums.h"
#include <ctime>

class EnemyFish: public SeaElement
{
public:
	// construtores e desconstrutores
	EnemyFish();
	~EnemyFish();

	// m�todos da lib
	void inicializar();
	void atualizar();
	void verificaOOB();
	void moveXY();

	// m�todos
	bool verificaSemelhanca(EnemyFish input_);

	// m�todos get
	int getId();
	ShotType getColor();

private:
	// atributos
	int id;
	ShotType color;	
	Direction facingDirection;
	int speed;	
};

