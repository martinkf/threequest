#pragma once
#include "Player.h"

class JogoInterface
{
public:
	JogoInterface();
	~JogoInterface();

	void inicializar();
	void atualizar(Player player_);
	void desenhar();

private:
	int oxygenLeft;
	Texto text;
};

