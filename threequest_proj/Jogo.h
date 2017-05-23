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
#include "ExplosionArray.h"

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

	// tela splash / créditos

	// métodos da tela splash
	void telaSplash_inicializar();
	void telaSplash_executar();
	void telaSplash_desenhar();
	void telaSplash_verificar();

	// atributos da tela splash
	FrameCounter frameCounterSplash;
	Sprite splashPicture;


	// tela menu

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



	// tela instructions

	// métodos
	void telaInstructions_inicializar();
	void telaInstructions_executar();
	void telaInstructions_desenhar();
	
	// atributos
	Sprite instructionsPicture;




	// tela jogo

	// métodos da tela jogo
	void telaJogo_inicializar();
	void telaJogo_executar();
	void telaJogo_desenhar();
	void telaJogo_verificar();
	
	void telaJogo_mortePorSubmergencia();
	void telaJogo_mortePorAsfixia();

	void telaJogo_clearAll();
	void telaJogo_clearAllThreats();

	void telaJogo_collisionPlayerDiver();
	void telaJogo_collisionPlayerBubble();
	void telaJogo_collisionPlayerFish();
	void telaJogo_collisionPlayerSub();
	void telaJogo_collisionPlayerEnemyTiro();
	void telaJogo_collisionFriendlyTiroDiver();
	void telaJogo_collisionFriendlyTiroFish();
	void telaJogo_collisionFriendlyTiroSub();
	void telaJogo_collisionEnemyTiroDiver();
	void telaJogo_collisionEnemyTiroFish();
	void telaJogo_collisionEnemyTiroSub();
	void telaJogo_collisionFishDiver();
	void telaJogo_collisionFishFish();
	void telaJogo_collisionFishSub();
	void telaJogo_collisionSubDiver();
	void telaJogo_collisionSubSub();

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
	ExplosionArray explosions;
	bool popupNeedsDrawing;
	bool gameStarted;
};

