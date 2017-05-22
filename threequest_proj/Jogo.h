#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"
#include "FrameCounter.h"
#include "Scorekeeping.h"
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

	// métodos da tela splash
	void telaSplash_inicializar();
	void telaSplash_executar();
	void telaSplash_desenhar();
	void telaSplash_verificar();
	// atributos da tela splash
	FrameCounter frameCounterSplash;
	Sprite splashPicture;

	// métodos da tela menu
	void telaMenu_inicializar();
	void telaMenu_executar();
	void telaMenu_desenhar();
	void telaMenu_verificar();
	// atributos da tela menu
	int currentChoice;
	int selectionFishY;
	Sprite selectionFish;
	Sprite menuBackground;

	// métodos da tela jogo
	void telaJogo_inicializar();
	void telaJogo_executar();
	void telaJogo_desenhar();
	void telaJogo_verificar();
	bool shouldDrawPopup();
	void clearAllThreats();
	// atributos da tela jogo
	FrameCounter frameCounterJogo;
	Sprite gameBackground;
	Sprite gameWaterSurface;
	Sprite popupBackground;
	Sprite scoreOverlay;
	Scorekeeping score;
	Sprite gridSlotA;
	Sprite gridSlotB;
	Sprite gridSlotC;
	Player player;
	AirBubbleArray airBubbles;
	TiroArray tirosEnemy;
	TiroArray tirosPlayer;
	DiverArray divers;
	EnemyFishArray enemyFishes;
	EnemySubArray enemySubs;
	bool popupNeedsDrawing;
};

