#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	// LIB UNICÓRNIO NECESSARY
	uniInicializar(800, 600, false);	
	
	// INICIALIZA O STATUS DA TELA
	status = sTelaJogo;

	// INICIALIZA A TELA JOGO
	telaJogo.inicializar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		// LIB UNICÓRNIO NECESSARY
		uniIniciarFrame();		

		// HANDLEIA AS GAME SCREENS
		switch (status)
		{
			case sTelaJogo:
				telaJogo.executar();
				break;
		}	

		// LIB UNICÓRNIO NECESSARY
		uniTerminarFrame();
	}
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!

	// LIB UNICÓRNIO NECESSARY
	uniFinalizar();
}