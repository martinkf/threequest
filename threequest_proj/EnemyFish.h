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

	// métodos da lib
	void inicializar();
	void atualizar();
	void verificaOOB();
	void moveXY();

	// métodos
	bool verificaSemelhanca(EnemyFish input_);

	// métodos get
	int getId();
	ShotType getColor();

private:
	// atributos
	int id;
	ShotType color;	
	Direction facingDirection;
	int speed;	
};

