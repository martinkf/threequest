#pragma once
#include "libUnicornio.h"
#include "FrameCounter.h"
#include "Player.h"
#include "MyEnums.h"
#include "Diver.h"

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
	Player player;
	Diver divertest;
};

