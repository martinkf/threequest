#pragma once
#include "SeaElement.h"

class AirBubble: public SeaElement
{
public:
	// construtores e desconstrutores
	AirBubble();
	~AirBubble();

	// m�todos da lib
	void inicializar();
	void atualizar();
	void verificaOOB();
	void moveXY();
};

