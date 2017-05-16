#include "TelaJogo.h"

TelaJogo::TelaJogo()
{
}

TelaJogo::~TelaJogo()
{
}

void TelaJogo::inicializar()
{
	// INICIALIZA O FRAMECOUNTER
	fcnt.inicializar();

	// INICIALIZA O PSEUDORANDOMIZADOR
	srand(time(0));

	// INICIALIZA O BACKGROUND
	if (!gRecursos.carregouSpriteSheet("gameBackground"))
	{
		gRecursos.carregarSpriteSheet("gameBackground", "imagens/spr_gameBackground.png", 0, 2);
	}
	gameBackground.setSpriteSheet("gameBackground");

	// INICIALIZA O WATER SURFACE
	if (!gRecursos.carregouSpriteSheet("waterSurface"))
	{
		gRecursos.carregarSpriteSheet("waterSurface", "imagens/spr_waterSurface.png");
	}
	gameWaterSurface.setSpriteSheet("waterSurface");

	// INICIALIZA O PLAYER
	player.inicializar();

	// INICIALIZA A DIVER ARRAY
	divers.inicializar();

	// INICIALIZA A JOGO INTERFACE
	interfac.inicializar();
}

void TelaJogo::executar()
{
	// ATUALIZA O FRAMECOUNTER
	fcnt.tick();

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

	// SPAWNER: DIVERS
	if (fcnt.getFrameNumber() % 180 == 0) // a cada 3 segundos
	{
		if (rand() % 6 == 0) // uma chance em seis
		{
			divers.spawnNewRandomDiver();
		}
	}

	// COLISION: PLAYER X DIVERS
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