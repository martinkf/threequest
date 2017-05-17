#include "JogoInterface.h"

JogoInterface::JogoInterface()
{
}

JogoInterface::~JogoInterface()
{
}

void JogoInterface::inicializar()
{	
	maxOxygen = 6000;
	oxygenLeft = maxOxygen;
	
	qttyDiver = 0;
	qttyEnemyFish = 0;
	qttyEnemySub = 0;

	gRecursos.carregarFonte("MONOFONT", "fontes/MONOFONT.TTF", 32);
	text.setFonte("MONOFONT");
	text.setAncora(0, 0.5);
		
	threeGridSize = 0;
}

void JogoInterface::desenhar()
{
	// desenha o oxigênio
	text.setString("Oxigênio: " + to_string(oxygenLeft));	
	text.desenhar(300, 550);
}

void JogoInterface::reduceOxygen()
{
	oxygenLeft--;
}

void JogoInterface::pegouUmaAirBubble()
{
	if (oxygenLeft + 500 > maxOxygen)
	{
		oxygenLeft = maxOxygen;
	}
	else
	{
		oxygenLeft += 500;
	}
}

void JogoInterface::pegouUmDiver()
{
	qttyDiver++;
}

void JogoInterface::matouUmEnemyFish(ShotType input_)
{
	qttyEnemyFish++;

	if (threeGridSize < 3) 
	{
		adicionaAoThreeGrid(input_);
	}
}

void JogoInterface::matouUmEnemySub(ShotType input_)
{
	qttyEnemySub++;

	if (threeGridSize < 3)
	{
		adicionaAoThreeGrid(input_);
	}
}

void JogoInterface::adicionaAoThreeGrid(ShotType input_)
{
	threeGrid[threeGridSize] = input_;
	threeGridSize++;
}

char JogoInterface::racionalizaThreeGrid()
{
	// método que é chamado quando a grade está com 3 elementos.
	// hora de pensar se houve alguma combinação.
	// strings de retorno:
	// 'n' - nenhuma combinação. resetar tudo imediatamente.
	// 'r' - combinação de tiros vermelhos
	// 'g' - combinação de tiros verdes
	// 'b' - combinação de tiros azuis
	// 't' - houve o three quest
	
	char charToReturn;

	if ((threeGrid[0] == threeGrid[1]) && (threeGrid[0] == threeGrid[2]) && (threeGrid[0] == shotRed))
	{
		charToReturn = 'r';
	}
	else if ((threeGrid[0] == threeGrid[1]) && (threeGrid[0] == threeGrid[2]) && (threeGrid[0] == shotGreen))
	{
		charToReturn = 'g';
	}
	else if ((threeGrid[0] == threeGrid[1]) && (threeGrid[0] == threeGrid[2]) && (threeGrid[0] == shotBlue))
	{
		charToReturn = 'b';
	}
	else
	{
		charToReturn = 'n';
	}

	threeGridSize = 0;
	return charToReturn;
}

int JogoInterface::getThreeGridSize()
{
	return threeGridSize;
}
