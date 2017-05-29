#pragma once
#include "SeaElement.h"
#include "MyEnums.h"

class Tiro: public SeaElement
{
public:
	// construtores e desconstrutores
	Tiro();
	~Tiro();

	// métodos da lib
	void inicializar(ShotType shotType_, int x_, int y_, Direction direction_);
	void atualizar();	
	void verificaOOB();
	void moveXY();

	// métodos get
	ShotType getShotType();

private:
	// atributos
	ShotType shotType;
	Direction shotDirection;
	int shotSpeed;
};

