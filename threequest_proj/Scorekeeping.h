#pragma once
#include "libUnicornio.h"
#include "MyEnums.h"

class Scorekeeping
{
public:
	Scorekeeping();
	~Scorekeeping();

	void inicializar();
	void desenhar();

	void drainOxygen();
	void reduceOxygenByAmount(int oxygenLoss_);
	void pegouUmaAirBubble();

	void pegouUmDiver();
	void matouUmDiver();
	void matouUmEnemyFish(ShotType input_);
	void matouUmEnemySub(ShotType input_);
	void matouUmEnemyFishSemGrid();
	void matouUmEnemySubSemGrid();

	void adicionaAoThreeGrid(ShotType input_);
	char racionalizaThreeGrid();
	ShotType getThreeGridAtThisIndex(int index_);
	void clearThreeGrid();

	void setFillStatus(GridStatus input_);
	GridStatus getFillStatus();

	void setSpecialShotType(ShotType input_);
	void setSpecialShotDuration();
	void drainSpecialShotDuration();
	int getSpecialShotDuration();

	void resumeDisplayingScore();
	void stopDisplayingScore();
	void setContentBarContext(BarType input_);
	
private:
	int maxOxygen;
	int oxygenLeft;
	Sprite oxygenArray[500];

	int qttyDiver;
	int qttyDiverKilled;
	int qttyEnemyFish;
	int qttyEnemySub;

	ShotType threeGrid[3];
	int threeGridPointer;
	GridStatus gridStatus;

	int specialShotDuration;
	Sprite specialShotArray[500];

	Texto text;

	BarType contentBarIsDisplaying;
	bool isDisplayingScore;
};

