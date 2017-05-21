#include "JogoInterface.h"

JogoInterface::JogoInterface()
{
}

JogoInterface::~JogoInterface()
{
}

void JogoInterface::inicializar()
{	
	maxOxygen = 6000; // 6000 at first = 500 x 12
	oxygenLeft = maxOxygen;
	
	if (!gRecursos.carregouSpriteSheet("oxygenInfinitesimal"))
	{
		gRecursos.carregarSpriteSheet("oxygenInfinitesimal", "imagens/spr_oxygenInfinitesimal.png");
	}
	for (int i = 0; i < 500; i++)
	{
		oxygenArray[i].setSpriteSheet("oxygenInfinitesimal");
	}

	qttyDiver = 0;
	qttyDiverKilled = 0;
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
	for (int i = 0; i < (oxygenLeft / 12); i++)
	{
		oxygenArray[i].desenhar(288 + i, 534);
	}

	// desenha o qtty fish
	text.setString(to_string(qttyEnemyFish));
	text.desenhar(349, 574);

	// desenha o qtty sub
	text.setString(to_string(qttyEnemySub));
	text.desenhar(561, 574);

	// desenha o qtty diver
	text.setString(to_string(qttyDiver));
	text.desenhar(720, 574);
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

void JogoInterface::matouUmDiver()
{
	qttyDiverKilled++;
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
