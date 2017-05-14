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

	//int retornaNumeroTotalDivers();
	//Tiro retornaDiverAtIndex(int index_);
	//void adicionaDiverNaLista(Diver diver_);
	void removeDiverAtIndex(int index_);
	//void adicionaDiverNesteIndex(Diver diver_, int index_);
	void spawnNewRandomDiver();
	void testaColisaoComPlayer(Player player_);

private:
	int numeroTotalUtilizado;
	Diver array[5];
};

