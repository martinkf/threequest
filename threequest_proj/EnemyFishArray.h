#pragma once
#include "EnemyFish.h"

class EnemyFishArray
{
public:
	EnemyFishArray();
	~EnemyFishArray();

	void inicializar();
	void atualizar();
	void desenhar();

	void spawnNewRandomEnemyFish();
	void turnOffSpawner();
	void turnOnSpawner();

	bool isSpawnerTurnedOn();
	int getNumeroTotalUtilizado();
	EnemyFish getEnemyFishAtIndex(int index_);
	void removeEnemyFishAtIndex(int index_);

private:
	int numeroTotalUtilizado;
	EnemyFish array[20];
	bool isTurnedOn;
};
