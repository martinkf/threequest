#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"
#include "FrameCounter.h"
#include "JogoInterface.h"
#include "Player.h"
#include "AirBubbleArray.h"
#include "TiroArray.h"
#include "DiverArray.h"
#include "EnemyFishArray.h"
#include "EnemySubArray.h"

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
	void setStatusJogo(StatusJogo input_);

	// métodos da tela splash
	void telaSplash_inicializar();
	void telaSplash_executar();
	void telaSplash_desenhar();
	void telaSplash_verificar();
	// atributos da tela splash
	FrameCounter frameCounterSplash;
	Sprite splashPicture;

	// métodos da tela jogo
	void telaJogo_inicializar();
	void telaJogo_executar();
	void telaJogo_desenhar();
	void telaJogo_verificar();
	// atributos da tela jogo
	FrameCounter frameCounterJogo;
	Sprite gameBackground;
	Sprite gameWaterSurface;
	JogoInterface interfac;
	Player player;
	AirBubbleArray airBubbles;
	TiroArray tirosEnemy;
	TiroArray tirosPlayer;
	DiverArray divers;
	EnemyFishArray enemyFishes;
	EnemySubArray enemySubs;
};

