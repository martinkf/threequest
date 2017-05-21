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
	
	gridStatus = enumFilling;

	specialShotDuration = 0;
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
	
	adicionaAoThreeGrid(input_);
}

void JogoInterface::matouUmEnemySub(ShotType input_)
{
	qttyEnemySub++;

	adicionaAoThreeGrid(input_);
}

void JogoInterface::adicionaAoThreeGrid(ShotType input_)
{
	if (gridStatus == enumFilling) 
	{
		threeGrid[threeGridPointer] = input_;

		if (threeGridPointer < 2)
		{
			threeGridPointer++;
		}
		else 
		{
			gridStatus = enumFilled;
			threeGridPointer = 0;
		}
	}
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
	else if ((threeGrid[0] != threeGrid[1]) && (threeGrid[0] != threeGrid[2]) && (threeGrid[1] != threeGrid[2]))
	{
		charToReturn = 't';
	}
	else
	{
		charToReturn = 'n';
	}
	
	return charToReturn;
}

ShotType JogoInterface::getThreeGridAtThisIndex(int index_)
{
	return threeGrid[index_];
}

void JogoInterface::clearThreeGrid()
{
	threeGrid[0] = shotNull;
	threeGrid[1] = shotNull;
	threeGrid[2] = shotNull;
}

void JogoInterface::setFillStatus(GridStatus input_)
{
	gridStatus = input_;
}

GridStatus JogoInterface::getFillStatus()
{
	return gridStatus;
}

void JogoInterface::setSpecialShotDuration()
{
	specialShotDuration = 720;
}

void JogoInterface::drainSpecialShotDuration()
{
	specialShotDuration--;
}

int JogoInterface::getSpecialShotDuration()
{
	return specialShotDuration;
}
