#pragma once
#include "AirBubble.h"

class AirBubbleArray
{
public:
	AirBubbleArray();
	~AirBubbleArray();

	void inicializar();
	void atualizar();
	void desenhar();

	void spawnNewRandomAirBubble();
	void turnOffSpawner();
	void turnOnSpawner();

	bool isSpawnerTurnedOn();
	int getNumeroTotalUtilizado();
	AirBubble getAirBubbleAtIndex(int index_);
	void removeAirBubbleAtIndex(int index_);

private:
	int numeroTotalUtilizado;
	AirBubble array[200];
	bool isTurnedOn;
};
