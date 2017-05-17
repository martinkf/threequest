#pragma once
#include "libUnicornio.h"
#include "FrameCounter.h"
#include "Player.h"
#include "MyEnums.h"
#include "DiverArray.h"
#include "TiroArray.h"
#include "EnemyArray.h"
#include "AirBubbleArray.h"
#include "JogoInterface.h"
#include <ctime>

class TelaJogo
{
public:
	TelaJogo();
	~TelaJogo();

	void inicializar();
	void executar();
	void desenhar();
	void verificar();

private:
	FrameCounter fcnt;

	Sprite gameBackground;
	Sprite gameWaterSurface;

	JogoInterface interfac;

	Player player;
	AirBubbleArray airBubbles;
	TiroArray tiros;
	DiverArray divers;
	EnemyArray enemyFishes;
};