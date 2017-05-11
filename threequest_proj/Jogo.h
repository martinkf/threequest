#pragma once
#include "libUnicornio.h"
#include "Player.h"
#include "FrameCounter.h"

enum StatusJogo { sTelaJogo };


class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();
	void executar();

private:	
	void telaJogo();

	StatusJogo status;

	FrameCounter fcnt;
	Sprite gameBackground;
	Sprite gameWaterSurface;
	Player player;
};

