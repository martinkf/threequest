#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"

class JogoInterface
{
public:
	JogoInterface();
	~JogoInterface();

	void inicializar();
	void desenhar();

	void reduceOxygen();
	void pegouUmaAirBubble();

	void pegouUmDiver();
	void matouUmEnemyFish(ShotType input_);
	void matouUmEnemySub(ShotType input_);

	void adicionaAoThreeGrid(ShotType input_);
	char racionalizaThreeGrid();
	int getThreeGridSize();
	
private:
	int maxOxygen;
	int oxygenLeft;

	int qttyDiver;
	int qttyEnemyFish;
	int qttyEnemySub;

	ShotType threeGrid[3];
	int threeGridSize;

	Texto text;
};

