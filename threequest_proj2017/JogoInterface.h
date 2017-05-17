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

	void pegouUmDiver();
	void matouUmEnemyFish();

	int getOxygenLeft();

private:
	int oxygenLeft;

	int qttyDivers;
	int qttyEnemyFish;

	Texto text;
};

