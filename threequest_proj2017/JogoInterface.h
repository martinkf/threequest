#pragma once
#include "libUnicornio.h"

class JogoInterface
{
public:
	JogoInterface();
	~JogoInterface();

	void inicializar();
	void desenhar();

	void reduceOxygen();
	void pegouUmaAirBubble();

	void pegouUmDiver();
	void matouUmEnemyFish();

	int getOxygenLeft();

private:
	int maxOxygen;
	int oxygenLeft;

	int qttyDivers;
	int qttyEnemyFish;

	Texto text;
};

