#pragma once
#include "libUnicornio.h"
#include "FrameCounter.h"

class TelaCredits
{
public:
	TelaCredits();
	~TelaCredits();

	void inicializar();
	void draw();
	void executar();
	void desenhar();

	void congelaFc();

	int getFrameCounterFrameNumber();

private:	
	FrameCounter fcSplash;
	Sprite bg;
};

