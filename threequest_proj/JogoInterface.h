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
	ShotType getThreeGridAtThisIndex(int index_);
	void clearThreeGrid();

	void setFillStatus(GridStatus input_);
	GridStatus getFillStatus();

	void setSpecialShotDuration();
	void drainSpecialShotDuration();
	int getSpecialShotDuration();
	
private:
	int maxOxygen;
	int oxygenLeft;

	int qttyDiver;
	int qttyEnemyFish;
	int qttyEnemySub;

	ShotType threeGrid[3];
	int threeGridPointer;
	GridStatus gridStatus;

	int specialShotDuration;

	Texto text;
};

