#pragma once
#include "Player.h"

class JogoInterface
{
public:
	JogoInterface();
	~JogoInterface();

	void inicializar();
	void desenhar();

	void reduceOxygen();
	void pegouUmDiver();

	int getOxygenLeft();

private:
	int oxygenLeft;
	int qttyDivers;
	Texto text;
};

