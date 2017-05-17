#pragma once
#include "libUnicornio.h"
#include "TelaJogo.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();	
	void executar();
	void finalizar();

private:
	StatusJogo status;
	TelaJogo telaJogo;
};

