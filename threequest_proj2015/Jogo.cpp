#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	// LIB UNIC�RNIO NECESSARY
	uniInicializar(800, 600, false);	
	
	// INICIALIZA O FRAMECOUNTER
	fcnt.inicializar();

	// INICIALIZA O STATUS DA TELA
	status = sTelaJogo;

	// TELA JOGO: INICIALIZA O BACKGROUND
	gRecursos.carregarSpriteSheet("gameBackground", "imagens/spr_gameBackground.png", 0, 2);	
	gameBackground.setSpriteSheet("gameBackground");

	// TELA JOGO: INICIALIZA O WATER SURFACE
	gRecursos.carregarSpriteSheet("waterSurface", "imagens/spr_waterSurface.png");
	gameWaterSurface.setSpriteSheet("waterSurface");

	// TELA JOGO: INICIALIZA O PLAYER
	player.inicializar();
}

void Jogo::finalizar()
{
	//	O resto da finaliza��o vem aqui (provavelmente, em ordem inversa a inicializa��o)!

	// LIB UNIC�RNIO NECESSARY
	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		// LIB UNIC�RNIO NECESSARY
		uniIniciarFrame();

		// ATUALIZA O FRAMECOUNTER
		fcnt.tick();

		// HANDLEIA AS GAME SCREENS
		switch (status)
		{
			case sTelaJogo: telaJogo();	break;
		}	

		// LIB UNIC�RNIO NECESSARY
		uniTerminarFrame();
	}
}

void Jogo::telaJogo()
{
	// DESENHA O BACKGROUND
	gameBackground.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	int rateOfAnimation = 5;
	if (fcnt.getFrameNumber() % rateOfAnimation == 0) gameBackground.avancarAnimacao();

	// DESENHA O PLAYER
	player.atualizar();
	player.desenhar();

	// DESENHA A WATER SURFACE
	gameWaterSurface.desenhar(gJanela.getLargura() / 2, 125);
}