#include "JogoInterface.h"

JogoInterface::JogoInterface()
{
}

JogoInterface::~JogoInterface()
{
}

void JogoInterface::inicializar()
{
	// to do	
	gRecursos.carregarFonte("MONOFONT", "fontes/MONOFONT.TTF", 32);
	text.setFonte("MONOFONT");
	text.setAncora(0, 0.5);
}

void JogoInterface::atualizar(Player player_)
{
	// to do
	oxygenLeft = player_.getOxygenLeft();
}

void JogoInterface::desenhar()
{
	// to do
	text.setString("Oxigênio: " + to_string(oxygenLeft));	
	text.desenhar(300, 550);
}
