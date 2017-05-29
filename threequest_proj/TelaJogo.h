#pragma once
#include "libUnicornio.h"
#include "FrameCounter.h"
#include "Scorekeeping.h"
#include "Player.h"
#include "AirBubbleArray.h"
#include "TiroArray.h"
#include "DiverArray.h"
#include "EnemyArray.h"
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
	void collisionPlayerEnemy();
	void collisionPlayerEnemyTiro();
	void collisionFriendlyTiroDiver();
	void collisionFriendlyTiroEnemy();
	void collisionEnemyTiroDiver();
	void collisionEnemyTiroEnemy();
	void collisionEnemyDiver();
	void collisionEnemyEnemy();
		
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
	EnemyArray enemies;
	ExplosionArray explosions;
	bool popupNeedsDrawing;
	bool gameStarted;
	Som som;
	bool goBackPls;
};

