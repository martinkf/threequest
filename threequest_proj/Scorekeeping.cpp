#include "Scorekeeping.h"

Scorekeeping::Scorekeeping()
{
}

Scorekeeping::~Scorekeeping()
{
}

void Scorekeeping::inicializar()
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
	qttyThreeQuest = 0;
	totalScore = 0;

	if (!gRecursos.carregouFonte("MONOFONT"))
	{
		gRecursos.carregarFonte("MONOFONT", "fontes/MONOFONT.TTF", 32);
	}
	text.setFonte("MONOFONT");
	text.setAncora(0, 0.5);
		
	threeGridPointer = 0;
	threeGrid[0] = shotNull;
	threeGrid[1] = shotNull;
	threeGrid[2] = shotNull;
	
	gridStatus = enumFilling;

	lives = 3;

	specialShotDuration = 0;

	if (!gRecursos.carregouSpriteSheet("redInfinitesimal"))
	{
		gRecursos.carregarSpriteSheet("redInfinitesimal", "imagens/spr_redInfinitesimal.png");
	}
	if (!gRecursos.carregouSpriteSheet("greenInfinitesimal"))
	{
		gRecursos.carregarSpriteSheet("greenInfinitesimal", "imagens/spr_greenInfinitesimal.png");
	}
	if (!gRecursos.carregouSpriteSheet("blueInfinitesimal"))
	{
		gRecursos.carregarSpriteSheet("blueInfinitesimal", "imagens/spr_blueInfinitesimal.png");
	}

	contentBarIsDisplaying = barOxygen;
	isDisplayingScore = true;
	isDisplayingResults = false;	

	deathBonus = false;
}

void Scorekeeping::desenhar()
{
	if (contentBarIsDisplaying == barOxygen)
	{
		// desenha o oxig�nio
		for (int i = 0; i < (oxygenLeft / 12); i++)
		{
			oxygenArray[i].desenhar(288 + i, 534);
		}
	}
	else if (contentBarIsDisplaying == barBlueFreezer) 
	{
		// desenha o blue freezer duration
		for (int i = 0; i < specialShotDuration; i++)
		{
			specialShotArray[i].desenhar(288 + i, 534);
		}
	} 
	else // ou seja, contentBarIsDisplaying == barSpecialShot
	{
		for (int i = 0; i < (specialShotDuration / 2); i++)
		{
			specialShotArray[i].desenhar(288 + i, 534);
		}
	}

	if (isDisplayingScore == true) 
	{
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

	if (isDisplayingResults == true)
	{
		// desenha o qtty fish
		text.setString(to_string(qttyEnemyFish));
		text.desenhar(345, 125);

		// desenha o qtty sub
		text.setString(to_string(qttyEnemySub));
		text.desenhar(555, 125);

		// desenha o qtty diver
		text.setString(to_string(qttyDiver));
		text.desenhar(345, 192);

		// desenha o qtty diver fail
		text.setString(to_string(qttyDiverKilled));
		text.desenhar(555, 192);

		// desenha o qtty threequest
		text.setString(to_string(qttyThreeQuest));
		text.desenhar(416, 254);

		// atualiza o score total
		totalScore = calculaTotalScore();
		// desenha o score total
		text.setString(to_string(totalScore));
		text.desenhar(564, 348);

		// desenha a quantidade de vidas
		text.setString(to_string(lives));
		text.desenhar(600, 394);
	}
}

void Scorekeeping::drainOxygen()
{
	oxygenLeft--;
}

void Scorekeeping::reduceOxygenByAmount(int oxygenLoss_)
{
	if (oxygenLeft - oxygenLoss_ < 0 )
	{
		oxygenLeft = 0;
	}
	else
	{
		oxygenLeft -= oxygenLoss_;
	}
}

void Scorekeeping::pegouUmaAirBubble()
{
	if (oxygenLeft + 700 > maxOxygen)
	{
		oxygenLeft = maxOxygen;
	}
	else
	{
		oxygenLeft += 700;
	}
}

int Scorekeeping::getOxygenLeft()
{
	return oxygenLeft;
}

void Scorekeeping::pegouUmDiver()
{
	qttyDiver++;

	if (oxygenLeft + 350 > maxOxygen)
	{
		oxygenLeft = maxOxygen;
	}
	else
	{
		oxygenLeft += 350;
	}
}

void Scorekeeping::matouUmDiver()
{
	qttyDiverKilled++;
}

void Scorekeeping::matouUmEnemyFish(ShotType input_)
{
	qttyEnemyFish++;
	
	adicionaAoThreeGrid(input_);
}

void Scorekeeping::matouUmEnemySub(ShotType input_)
{
	qttyEnemySub++;

	adicionaAoThreeGrid(input_);
}

void Scorekeeping::matouUmEnemyFishSemGrid()
{
	qttyEnemyFish++;
}

void Scorekeeping::matouUmEnemySubSemGrid()
{
	qttyEnemySub++;
}

void Scorekeeping::obteveThreeQuest()
{
	qttyThreeQuest++;
}

void Scorekeeping::adicionaAoThreeGrid(ShotType input_)
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

char Scorekeeping::racionalizaThreeGrid()
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
	
	return charToReturn;
}

ShotType Scorekeeping::getThreeGridAtThisIndex(int index_)
{
	return threeGrid[index_];
}

void Scorekeeping::clearThreeGrid()
{
	threeGrid[0] = shotNull;
	threeGrid[1] = shotNull;
	threeGrid[2] = shotNull;
	threeGridPointer = 0;
}

void Scorekeeping::setFillStatus(GridStatus input_)
{
	gridStatus = input_;
}

GridStatus Scorekeeping::getFillStatus()
{
	return gridStatus;
}

void Scorekeeping::setSpecialShotType(ShotType input_)
{
	string temp;

	switch (input_)
	{
	case shotRed:
		temp = "redInfinitesimal";
		break;
	case shotGreen:
		temp = "greenInfinitesimal";
		break;
	case shotBlue:
		temp = "blueInfinitesimal";
		break;
	}

	for (int i = 0; i < 500; i++)
	{
		specialShotArray[i].setSpriteSheet(temp);
	}
}

void Scorekeeping::setSpecialShotDuration(int input_)
{
	specialShotDuration = input_;
}

void Scorekeeping::drainSpecialShotDuration()
{
	specialShotDuration--;
}

int Scorekeeping::getSpecialShotDuration()
{
	return specialShotDuration;
}

void Scorekeeping::resumeDisplayingScore()
{
	isDisplayingScore = true;
}

void Scorekeeping::stopDisplayingScore()
{
	isDisplayingScore = false;
}

void Scorekeeping::setContentBarContext(BarType input_)
{
	contentBarIsDisplaying = input_;
}

BarType Scorekeeping::getContentBarContext()
{
	return contentBarIsDisplaying;
}

void Scorekeeping::startDisplayingResults()
{
	isDisplayingResults = true;
}

void Scorekeeping::stopDisplayingResults()
{
	isDisplayingResults = false;
}

int Scorekeeping::getNumberOfLives()
{
	return lives;
}

void Scorekeeping::removeALife()
{
	lives--;
}

void Scorekeeping::resetLives()
{
	lives = 3;
}

void Scorekeeping::clearAllScores()
{
	int temp = lives;
	inicializar();
	lives = temp;
}

void Scorekeeping::setDeathBonus(bool input_)
{
	deathBonus = input_;
}

int Scorekeeping::calculaTotalScore()
{
	int scoreFish = qttyEnemyFish * 200;
	int scoreSub = qttyEnemySub * 500;
	int scoreDiver = qttyDiver * 500;
	int scoreDiverDeath = -(qttyDiverKilled * 500);
	int scoreThreeQuest = qttyThreeQuest * 1500;

	int sum = scoreFish + scoreSub + scoreDiver + scoreDiverDeath + scoreThreeQuest;
	
	if (deathBonus == true) // morreu de submerg�ncia, n�o asfixia
	{
		sum += 5000;
		sum += ((maxOxygen - oxygenLeft) * 2);
	}

	return sum;
}
