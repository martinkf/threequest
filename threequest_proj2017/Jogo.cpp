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
	
	// INICIALIZA O PSEUDORANDOMIZADOR
	srand(time(0));

	// INICIALIZA O FRAMECOUNTER
	fcnt.inicializar();

	// INICIALIZA O STATUS DA TELA
	status = sTelaJogo;

	// INICIALIZA A TELA JOGO
	inicializarTelaJogo();
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

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!

	// LIB UNICÓRNIO NECESSARY
	uniFinalizar();
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

	// TELA JOGO: INICIALIZA A JOGO INTERFACE
	interfac.inicializar();
}

void Jogo::executarTelaJogo()
{
	// DESENHA O BACKGROUND
	gameBackground.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	int rateOfAnimation = 5;
	if (fcnt.getFrameNumber() % rateOfAnimation == 0) gameBackground.avancarAnimacao();

	// DESENHA A JOGO INTERFACE
	interfac.atualizar(player);
	interfac.desenhar();

	// DESENHA A DIVER ARRAY
	divers.atualizar();
	divers.desenhar();
	
	// DESENHA O PLAYER
	player.atualizar();
	player.desenhar();

	// DESENHA A WATER SURFACE
	gameWaterSurface.desenhar(gJanela.getLargura() / 2, 125);

	// SPAWNER: DIVER 
	if (fcnt.getFrameNumber() % 180 == 0) // a cada 3 segundos
	{
		if (rand() % 6 == 0) // uma chance em seis
		{
			divers.spawnNewRandomDiver();
		}
	}

	// COLISION: PLAYER X DIVER
	for (int i = 0; i < divers.retornaNumeroTotalDivers(); i++)
	{
		if (uniTestarColisao(
			divers.retornaDiverAtIndex(i).getSprite(),
			divers.retornaDiverAtIndex(i).getX(),
			divers.retornaDiverAtIndex(i).getY(),
			0,
			player.getSprite(),
			player.getX(),
			player.getY(),
			0
		))
		{
			// COLIDIU UM DIVER COM O PLAYER!
			// vê se cabe um diver no submarino
			if (player.tryAddOneDiver())
			{
				// adiciona o diver
				player.addOneDiver();

				// destrói o diver do mundo
				divers.removeDiverAtIndex(i);
			}
		}
	}	
}