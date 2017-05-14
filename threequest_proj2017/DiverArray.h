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
	
	int retornaNumeroTotalDivers();
	Diver retornaDiverAtIndex(int index_);
	void removeDiverAtIndex(int index_);
	
private:
	int numeroTotalUtilizado;
	Diver array[5];
};

