#pragma once
#include "libUnicornio.h"
#include "Diver.h"
#include "Player.h"

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
	int retornaNumeroTotalDivers();
	Diver getDiverAtIndex(int index_);
	void removeDiverAtIndex(int index_);
	
private:
	int numeroTotalUtilizado;
	Diver array[10];
	bool isTurnedOn;
};

