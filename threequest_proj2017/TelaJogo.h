#pragma once
#include "libUnicornio.h"
#include "FrameCounter.h"
#include "Player.h"
#include "MyEnums.h"
#include "DiverArray.h"
#include "JogoInterface.h"
#include <ctime>

class TelaJogo
{
public:
	TelaJogo();
	~TelaJogo();

	void inicializar();
	void executar();

private:
	FrameCounter fcnt;
	Sprite gameBackground;
	Sprite gameWaterSurface;
	JogoInterface interfac;
	Player player;
	DiverArray divers;
};