#include "TelaMenu.h"

TelaMenu::TelaMenu()
{	
}

TelaMenu::~TelaMenu()
{
}

void TelaMenu::inicializar()
{		
	// atributo: current choice
	currentChoice = 0;

	// atributo: selection fish y
	selectionFishY = 278;

	// atributo: selection fish
	if (!gRecursos.carregouSpriteSheet("fishRed"))
	{
		gRecursos.carregarSpriteSheet("fishRed", "imagens/spr_fishRed.png", 1, 4);
	}
	selectionFish.setSpriteSheet("fishRed");
	selectionFish.setVelocidadeAnimacao(5);
	selectionFish.setInverterX(true);

	// atributo: bg
	if (!gRecursos.carregouSpriteSheet("menuBg"))
	{
		gRecursos.carregarSpriteSheet("menuBg", "imagens/spr_menuBg.png");
	}
	bg.setSpriteSheet("menuBg");
}

void TelaMenu::draw()
{
	executar();
	desenhar();
}

void TelaMenu::executar()
{	
	// AVANÇA ANIMAÇÃO DO SELECTION FISH
	selectionFish.avancarAnimacao();

	// POSICIONA O SELECTION FISH DE ACORDO COM O SELECTION INT
	switch (currentChoice)
	{
	case 0: // NEW GAME
		selectionFishY = 278;
		break;
	case 1: // INSTRUCTIONS
		selectionFishY = 346;
		break;
	case 2: // CREDITS
		selectionFishY = 414;
		break;
	case 3: // EXIT
		selectionFishY = 482;
		break;
	}

	// VERIFICA KEYBOARD PRESSES
	if (gTeclado.pressionou[TECLA_CIMA])
	{
		if (currentChoice > 0)
		{
			currentChoice--;
		}
		else
		{
			currentChoice = 3;
		}
	}
	if (gTeclado.pressionou[TECLA_BAIXO])
	{
		if (currentChoice < 3)
		{
			currentChoice++;
		}
		else
		{
			currentChoice = 0;
		}
	}
}

void TelaMenu::desenhar()
{
	// DESENHA O MENU BACKGROUND
	bg.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	// DESENHA O SELECTION FISH
	selectionFish.desenhar(200, selectionFishY);
}

int TelaMenu::getCurrentChoice()
{
	return currentChoice;
}
