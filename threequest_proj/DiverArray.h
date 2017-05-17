#pragma once
#include "Diver.h"

class DiverArray
{
public:
	DiverArray();
	~DiverArray();

	void inicializar();
	void atualizar();
	void desenhar();
	
	void spawnNewRandomDiver();
	void turnOffSpawner();
	void turnOnSpawner();

	bool isSpawnerTurnedOn();
	int getNumeroTotalUtilizado();
	Diver getDiverAtIndex(int index_);
	void removeDiverAtIndex(int index_);
	
private:
	int numeroTotalUtilizado;
	Diver array[20];
	bool isTurnedOn;
};

