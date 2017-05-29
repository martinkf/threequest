#pragma once
#include <ctime>
#include "libUnicornio.h"
#include "MyEnums.h"
#include "TelaMenu.h"
#include "TelaInstructions.h"
#include "TelaCredits.h"
#include "TelaJogo.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	// métodos da lib
	void inicializar();
	
	void executar();

	void finalizar();

private:
	// atributos
	Telas telaADesenhar;

	TelaMenu telaMenu;
	TelaInstructions telaInstructions;
	TelaCredits telaCredits;
	TelaJogo telaJogo;
};

