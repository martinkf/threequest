#pragma once
#include "EnemyFish.h"

class EnemyArray
{
public:
	EnemyArray();
	~EnemyArray();

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

