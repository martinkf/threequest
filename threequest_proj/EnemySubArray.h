#pragma once
#include "EnemySub.h"

class EnemySubArray
{
public:
	EnemySubArray();
	~EnemySubArray();

	void inicializar();
	void atualizar();
	void desenhar();

	void spawnNewRandomEnemySub();
	void turnOffSpawner();
	void turnOnSpawner();

	bool isSpawnerTurnedOn();
	int getNumeroTotalUtilizado();
	EnemySub getEnemySubAtIndex(int index_);
	void removeEnemySubAtIndex(int index_);

	void addEnemySubAtIndex(EnemySub _input, int _index);
	
	void clearEverything();

private:
	int numeroTotalUtilizado;
	EnemySub array[50];
	bool isTurnedOn;
};