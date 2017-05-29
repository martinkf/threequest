#pragma once
#include "SeaElement.h"
#include "MyEnums.h"
#include <ctime>

class Diver: public SeaElement
{
public:
	// construtores e desconstrutores
	Diver();
	~Diver();

	// métodos da lib
	void inicializar();
	void atualizar();
	void verificaOOB();
	void moveXY();

private:
	// atributos
	int speed;
	Direction facingDirection;
};

