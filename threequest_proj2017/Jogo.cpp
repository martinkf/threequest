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
	
	// INICIALIZA O FRAMECOUNTER
	fcnt.inicializar();

	// INICIALIZA O STATUS DA TELA
	status = sTelaJogo;

	// INICIALIZA A TELA JOGO
	inicializarTelaJogo();
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!

	// LIB UNICÓRNIO NECESSARY
	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		// LIB UNICÓRNIO NECESSARY
		uniIniciarFrame();

		// ATUALIZA O FRAMECOUNTER
		fcnt.tick();

		// HANDLEIA AS GAME SCREENS
		switch (status)
		{
			case sTelaJogo: executarTelaJogo();	break;
		}	

		// LIB UNICÓRNIO NECESSARY
		uniTerminarFrame();
	}
}

void Jogo::inicializarTelaJogo()
{
	// TELA JOGO: INICIALIZA O BACKGROUND
	if (!gRecursos.carregouSpriteSheet("gameBackground"))
	{
		gRecursos.carregarSpriteSheet("gameBackground", "imagens/spr_gameBackground.png", 0, 2);
	}	
	gameBackground.setSpriteSheet("gameBackground");

	// TELA JOGO: INICIALIZA O WATER SURFACE
	if (!gRecursos.carregouSpriteSheet("waterSurface"))
	{
		gRecursos.carregarSpriteSheet("waterSurface", "imagens/spr_waterSurface.png");
	}	
	gameWaterSurface.setSpriteSheet("waterSurface");
	
	// TELA JOGO: INICIALIZA O PLAYER
	player.inicializar();

	// TELA JOGO: INICIALIZA A DIVER ARRAY
	divers.inicializar();
	divers.spawnNewRandomDiver();
}

void Jogo::executarTelaJogo()
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

	// DESENHA A DIVER ARRAY
	divers.atualizar();
	divers.desenhar();

	// TEST: DIVER SPAWNER
	if (fcnt.getFrameNumber() % 180 == 0) divers.spawnNewRandomDiver();

	// TESTANDO COLISÃO DE PLAYER COM DIVER
	divers.testaColisaoComPlayer(player);
}