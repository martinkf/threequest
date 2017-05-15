#pragma once
#include "libUnicornio.h"
#include "FrameCounter.h"
#include "Player.h"
#include "MyEnums.h"
#include "DiverArray.h"
#include "JogoInterface.h"
#include <ctime>

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();	
	void executar();
	void finalizar();

private:
	void inicializarTelaJogo();
	void executarTelaJogo();

	StatusJogo status;

	FrameCounter fcnt;
	Sprite gameBackground;
	Sprite gameWaterSurface;
	JogoInterface interfac;
	Player player;
	DiverArray divers;
};

