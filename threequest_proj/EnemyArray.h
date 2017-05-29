#pragma once
#include "Enemy.h"

class EnemyArray
{
public:
	EnemyArray();
	~EnemyArray();

	void inicializar();
	void atualizar();
	void desenhar();

	void spawnNewRandomEnemy();
	void turnOffSpawner();
	void turnOnSpawner();

	bool isSpawnerTurnedOn();
	int getNumeroTotalUtilizado();
	Enemy getEnemyAtIndex(int index_);
	void removeEnemyAtIndex(int index_);

	void addEnemyAtIndex(Enemy _input, int _index);
	//

	void clearEverything();
	//

private:
	int numeroTotalUtilizado;
	Enemy array[100];
	bool isTurnedOn;
};