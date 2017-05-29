#pragma once
#include "libUnicornio.h"

class TelaMenu
{
public:
	TelaMenu();
	~TelaMenu();

	void inicializar();
	void draw();
	void executar();
	void desenhar();

	int getCurrentChoice();

private:
	int currentChoice;
	int selectionFishY;
	Sprite selectionFish;
	Sprite bg;
};

