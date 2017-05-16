#include "JogoInterface.h"

JogoInterface::JogoInterface()
{
}

JogoInterface::~JogoInterface()
{
}

void JogoInterface::inicializar()
{	
	oxygenLeft = 6000;
	
	qttyDivers = 0;

	gRecursos.carregarFonte("MONOFONT", "fontes/MONOFONT.TTF", 32);
	text.setFonte("MONOFONT");
	text.setAncora(0, 0.5);
}

void JogoInterface::desenhar()
{
	// desenha o oxig�nio
	text.setString("Oxig�nio: " + to_string(oxygenLeft));	
	text.desenhar(300, 550);
}

void JogoInterface::reduceOxygen()
{
	oxygenLeft--;
}

void JogoInterface::pegouUmDiver()
{
	qttyDivers++;
}

int JogoInterface::getOxygenLeft()
{
	return oxygenLeft;
}
