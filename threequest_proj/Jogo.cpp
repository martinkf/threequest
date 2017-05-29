#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	// lib
	uniInicializar(800, 600, false);
	srand(time(0));

	// atributos
	telaADesenhar = eTelaCredits;

	telaMenu.inicializar();
	telaInstructions.inicializar();
	telaCredits.inicializar();
	telaJogo.inicializar();

	// music
	if (!gRecursos.carregouMusica("menuMusic"))
	{
		gRecursos.carregarMusica("menuMusic", "musica/music_main.mp3");
	}
	gMusica.tocar("menuMusic", true);
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	Seu código vem aqui!

		// LISTENS TO KEYBOARD
		switch (telaADesenhar)
		{
			case eTelaMenu: 
			// LISTENING TO KEYBOARD, TELA MENU
				if (gTeclado.pressionou[TECLA_ESPACO] || gTeclado.pressionou[TECLA_ENTER])
				{
					switch (telaMenu.getCurrentChoice())
					{
					case 0: // NEW GAME						
						gMusica.parar();
						telaJogo.comingIn();
						telaADesenhar = eTelaJogo;
						break;
					case 1: // INSTRUCTIONS
						telaADesenhar = eTelaInstructions;
						break;
					case 2: // CREDITS
						telaCredits.congelaFc();
						telaADesenhar = eTelaCredits;
						break;
					case 3: // EXIT
						gEventos.emitirEventoDeSaida();
						break;
					}
				}
				break;
			case eTelaInstructions:
				// LISTENING TO KEYBOARD, TELA INSTRUCTIONS
				if (gTeclado.pressionou[TECLA_ESPACO] || gTeclado.pressionou[TECLA_ENTER])
				{
					telaADesenhar = eTelaMenu;
				}
				break;
			case eTelaCredits:  
			// LISTENING TO KEYBOARD OR EVENTS, TELA CREDITS
				if (gTeclado.pressionou[TECLA_ESPACO] || gTeclado.pressionou[TECLA_ENTER])
				{
					telaADesenhar = eTelaMenu;
				}
				if (telaCredits.getFrameCounterFrameNumber() == 180)
				{
					telaADesenhar = eTelaMenu;
				}
				break;
			case eTelaJogo:
				// LISTENING TO KEYBOARD OR EVENTS, TELA JOGO
				if (telaJogo.wantsToGoBack())
				{
					telaADesenhar = eTelaMenu;
					gMusica.tocar("menuMusic", true);
				}
				break;
		}

		// REACT TO CHOICE
		switch (telaADesenhar)
		{
			case eTelaMenu:
				telaMenu.draw();
				break;
			case eTelaInstructions:
				telaInstructions.draw();
				break;
			case eTelaCredits:
				telaCredits.draw();
				break;
			case eTelaJogo:
				telaJogo.draw();
				break;
		}

		//	Seu código acima!

		uniTerminarFrame();
	}
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	uniFinalizar();
}