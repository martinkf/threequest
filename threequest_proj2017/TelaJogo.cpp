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

	// INICIALIZA O TIRO ARRAY
	tiros.inicializar();

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

	// DESENHA A TIRO ARRAY
	tiros.atualizar();
	tiros.desenhar();

	// DESENHA O PLAYER
	player.atualizar();
	player.desenhar();

	// DESENHA A WATER SURFACE
	gameWaterSurface.desenhar(gJanela.getLargura() / 2, 125);
}

void TelaJogo::verificar()
{
	// SE O PLAYER EST� NA SUPERF�CIE
	if (player.isPlayerOnSurface())
	{
		divers.turnOffSpawner();
	}
	else
	{
		divers.turnOnSpawner();
		interfac.reduceOxygen();
	}

	// SE O PLAYER ATIROU
	if (player.wantsToShoot()) 
	{
		// cria o tiro
		Tiro tiro = Tiro();
		tiro.inicializar(player.getShotType(), player.getX(), player.getY(), player.getDirection());
		tiros.adicionaTiroNaLista(tiro);

		// unset the flag
		player.makeNotWantToShoot();
	}
	// SPAWNER: DIVERS
	if (fcnt.getFrameNumber() % 180 == 0) // 180 -> a cada 3 segundos
	{
		if (rand() % 1 == 0) // 6 -> uma chance em seis
		{
			if (divers.isSpawnerTurnedOn()) // se o spawner est� ligado
			{
				divers.spawnNewRandomDiver();
			}
		}
	}

	// COLISION: PLAYER X DIVERS
	for (int i = 0; i < divers.getNumeroTotalUtilizado(); i++)
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

			// destr�i o diver
			divers.removeDiverAtIndex(i);
		}
	}

	// COLISION: TIRO X DIVERS
	for (int i = 0; i < divers.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < tiros.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				divers.getDiverAtIndex(i).getSprite(),
				divers.getDiverAtIndex(i).getX(),
				divers.getDiverAtIndex(i).getY(),
				0,
				tiros.getTiroAtIndex(j).getSprite(),
				tiros.getTiroAtIndex(j).getX(),
				tiros.getTiroAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM TIRO COM UM DIVER!
				// destr�i o tiro
				TiroArray test = tiros;
				test.removeTiroAtIndex(j);
				tiros = test;

				// destr�i o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}
}
