#pragma once
#include "libUnicornio.h"
#include "FrameCounter.h"
#include "Scorekeeping.h"
#include "Player.h"
#include "AirBubbleArray.h"
#include "TiroArray.h"
#include "DiverArray.h"
#include "EnemyFishArray.h"
#include "EnemySubArray.h"
#include "ExplosionArray.h"

class TelaJogo
{
public:
	TelaJogo();
	~TelaJogo();

	void inicializar();
	void draw();
	void executar();
	void desenhar();

	void mortePorSubmergencia();
	void mortePorAsfixia();

	void clearAll();
	void clearAllThreats();

	void collisionPlayerDiver();
	void collisionPlayerBubble();
	void collisionPlayerFish();
	void collisionPlayerSub();
	void collisionPlayerEnemyTiro();
	void collisionFriendlyTiroDiver();
	void collisionFriendlyTiroFish();
	void collisionFriendlyTiroSub();
	void collisionEnemyTiroDiver();
	void collisionEnemyTiroFish();
	void collisionEnemyTiroSub();
	void collisionFishDiver();
	void collisionFishFish();
	void collisionFishSub();
	void collisionSubDiver();
	void collisionSubSub();
		
	void comingIn();
	bool wantsToGoBack();

private:
	// ATRIBUTOS
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
	TiroArray tirosPlayer;
	TiroArray tirosEnemy;
	DiverArray divers;
	EnemyFishArray enemyFishes;
	EnemySubArray enemySubs;
	ExplosionArray explosions;
	bool popupNeedsDrawing;
	bool gameStarted;
	Som som;
	bool goBackPls;
};

