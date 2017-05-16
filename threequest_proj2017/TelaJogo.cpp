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
	desenhar();
	verificar();
}

void TelaJogo::desenhar()
{
	// ATUALIZA O FRAMECOUNTER
	fcnt.tick();

	// DESENHA O BACKGROUND
	gameBackground.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	int rateOfAnimation = 5;
	if (fcnt.getFrameNumber() % rateOfAnimation == 0) gameBackground.avancarAnimacao();

	// DESENHA A JOGO INTERFACE
	interfac.desenhar();

	// DESENHA A DIVER ARRAY
	divers.atualizar();
	divers.desenhar();

	// DESENHA O PLAYER
	player.atualizar();
	player.desenhar();

	// DESENHA A WATER SURFACE
	gameWaterSurface.desenhar(gJanela.getLargura() / 2, 125);
}

void TelaJogo::verificar()
{
	// SE O PLAYER ESTÁ NA SUPERFÍCIE
	if (player.isPlayerOnSurface())
	{
		divers.turnOffSpawner();
	}
	else
	{
		divers.turnOnSpawner();
		interfac.reduceOxygen();
	}

	// SPAWNER: DIVERS
	if (fcnt.getFrameNumber() % 180 == 0) // 180 -> a cada 3 segundos
	{
		if (rand() % 1 == 0) // 6 -> uma chance em seis
		{
			if (divers.isSpawnerTurnedOn()) // se o spawner está ligado
			{
				divers.spawnNewRandomDiver();
			}
		}
	}

	// COLISION: PLAYER X DIVERS
	for (int i = 0; i < divers.retornaNumeroTotalDivers(); i++)
	{
		if (uniTestarColisao(
			divers.getDiverAtIndex(i).getSprite(),
			divers.getDiverAtIndex(i).getX(),
			divers.getDiverAtIndex(i).getY(),
			0,
			player.getSprite(),
			player.getX(),
			player.getY(),
			0
		))
		{
			// COLIDIU UM DIVER COM O PLAYER!
			// adiciona um diver ao score
			interfac.pegouUmDiver();

			// destrói o diver
			divers.removeDiverAtIndex(i);
		}
	}

	// COLISION: TIRO X DIVERS
	for (int i = 0; i < divers.retornaNumeroTotalDivers(); i++)
	{
		for (int j = 0; j < player.getTiroArray().getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				divers.getDiverAtIndex(i).getSprite(),
				divers.getDiverAtIndex(i).getX(),
				divers.getDiverAtIndex(i).getY(),
				0,
				player.getTiroArray().getTiroAtIndex(j).getSprite(),				
				player.getTiroArray().getTiroAtIndex(j).getX(),
				player.getTiroArray().getTiroAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM TIRO COM UM DIVER!
				// destrói o tiro
				TiroArray test = player.getTiroArray();
				test.removeTiroAtIndex(j);
				player.setTiroArray(test);

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}
}
