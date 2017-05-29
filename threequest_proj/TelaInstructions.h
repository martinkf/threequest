#pragma once
#include "libUnicornio.h"

class TelaInstructions
{
public:
	TelaInstructions();
	~TelaInstructions();

	void inicializar();
	void draw();
	void executar();
	void desenhar();

private:	
	Sprite bg;
};

