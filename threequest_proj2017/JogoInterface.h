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
	void matouUmEnemySub();

	//int getOxygenLeft();

private:
	int maxOxygen;
	int oxygenLeft;

	int qttyDiver;
	int qttyEnemyFish;
	int qttyEnemySub;

	Texto text;
};

