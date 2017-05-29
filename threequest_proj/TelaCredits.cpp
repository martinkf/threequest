#include "TelaCredits.h"

TelaCredits::TelaCredits()
{
}

TelaCredits::~TelaCredits()
{
}

void TelaCredits::inicializar()
{
	// ATRIBUTO: fcSplash
	fcSplash.inicializar();

	// ATRIBUTO: bg
	if (!gRecursos.carregouSpriteSheet("creditsBg"))
	{
		gRecursos.carregarSpriteSheet("creditsBg", "imagens/spr_creditsBg.png");
	}
	bg.setSpriteSheet("creditsBg");
}

void TelaCredits::draw()
{
	executar();
	desenhar();
}

void TelaCredits::executar()
{	
	// TICK NO FRAME COUNTER
	fcSplash.tick();
}

void TelaCredits::desenhar()
{
	bg.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
}

void TelaCredits::congelaFc()
{
	fcSplash.freeze();
}

int TelaCredits::getFrameCounterFrameNumber()
{
	return fcSplash.getFrameNumber();
}
