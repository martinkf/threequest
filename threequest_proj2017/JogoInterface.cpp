#include "JogoInterface.h"

JogoInterface::JogoInterface()
{
}

JogoInterface::~JogoInterface()
{
}

void JogoInterface::inicializar()
{	
	gRecursos.carregarFonte("MONOFONT", "fontes/MONOFONT.TTF", 32);
	text.setFonte("MONOFONT");
	text.setAncora(0, 0.5);
}

void JogoInterface::atualizar(Player player_)
{	
	oxygenLeft = player_.getOxygenLeft();
	numberDivers = player_.getNumberDivers();
}

void JogoInterface::desenhar()
{
	// desenha o oxig�nio
	text.setString("Oxig�nio: " + to_string(oxygenLeft));	
	text.desenhar(300, 550);

	// desenha os divers
	text.setString("Divers: " + to_string(numberDivers));
	text.desenhar(520, 550);
}
