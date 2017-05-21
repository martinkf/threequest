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
		
	threeGridPointer = 0;
	threeGrid[0] = shotNull;
	threeGrid[1] = shotNull;
	threeGrid[2] = shotNull;
	hasBeenFilled = false;
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
	
	adicionaAoThreeGrid(input_);
}

void JogoInterface::matouUmEnemySub(ShotType input_)
{
	qttyEnemySub++;

	adicionaAoThreeGrid(input_);
}

void JogoInterface::adicionaAoThreeGrid(ShotType input_)
{
	threeGrid[threeGridPointer] = input_;

	if (threeGridPointer < 2)
	{
		threeGridPointer++;
	}
	else 
	{
		hasBeenFilled = true;
		threeGridPointer = 0;
	}
}

char JogoInterface::racionalizaThreeGrid()
{
	// m�todo que � chamado quando a grade est� com 3 elementos.
	// hora de pensar se houve alguma combina��o.
	// strings de retorno:
	// 'n' - nenhuma combina��o. resetar tudo imediatamente.
	// 'r' - combina��o de tiros vermelhos
	// 'g' - combina��o de tiros verdes
	// 'b' - combina��o de tiros azuis
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
	else if ((threeGrid[0] != threeGrid[1]) && (threeGrid[0] != threeGrid[2]) && (threeGrid[1] != threeGrid[2]))
	{
		charToReturn = 't';
	}
	else
	{
		charToReturn = 'n';
	}

	// temp
	threeGrid[0] = shotNull;
	threeGrid[1] = shotNull;
	threeGrid[2] = shotNull;

	// end temp

	hasBeenFilled = false;
	return charToReturn;
}

ShotType JogoInterface::getThreeGridAtThisIndex(int index_)
{
	return threeGrid[index_];
}

bool JogoInterface::getFillStatus()
{
	return hasBeenFilled;
}
