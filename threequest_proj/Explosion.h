#pragma once
#include "SeaElement.h"

class Explosion: public SeaElement
{
public:
	// construtores e desconstrutores
	Explosion();
	~Explosion();

	// m�todos da lib
	void inicializar(int x_, int y_);
	void atualizar();
	void verificaAnimation();
};

