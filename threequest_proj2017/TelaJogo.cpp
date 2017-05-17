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

	// INICIALIZA A AIR BUBBLE ARRAY
	airBubbles.inicializar();

	// INICIALIZA A DIVER ARRAY
	divers.inicializar();

	// INICIALIZA A ENEMY FISH ARRAY
	enemyFishes.inicializar();

	// INICIALIZA A ENEMY SUB ARRAY
	enemySubs.inicializar();

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

	// DESENHA A AIR BUBBLE ARRAY
	airBubbles.atualizar();
	airBubbles.desenhar();

	// DESENHA A ENEMY FISHES ARRAY
	enemyFishes.atualizar();
	enemyFishes.desenhar();

	// DESENHA A ENEMY SUBS ARRAY
	enemySubs.atualizar();
	enemySubs.desenhar();

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
		// desliga os spawners
		divers.turnOffSpawner();		
		airBubbles.turnOffSpawner();
		enemyFishes.turnOffSpawner();
		enemySubs.turnOffSpawner();
	}
	else
	{
		// liga os spawners
		divers.turnOnSpawner();
		airBubbles.turnOnSpawner();
		enemyFishes.turnOnSpawner();
		enemySubs.turnOnSpawner();		

		// come o oxigênio, matando-lhe lentamente
		interfac.reduceOxygen();
	}

	// SE ACONTECEU UM FULL THREE GRID
	if (interfac.getThreeGridSize() == 3)
	{
		char temp = interfac.racionalizaThreeGrid();
		switch (temp)
		{
		case 'n':
			break;
		case 'r':
			player.changeShotType(shotRed);
			player.setShotTimeRemaining();
			break;
		case 'g':
			player.changeShotType(shotGreen);
			player.setShotTimeRemaining();
			break;
		case 'b':
			player.changeShotType(shotBlue);
			player.setShotTimeRemaining();
			break;
		case 't':
			break;
		}
	}

	// SE O SHOT FOR SPECIAL, DIMINUIR ELE AOS POUCOS
	if (player.getShotTimeRemaining() > 0) 
	{
		player.drainShotTimeRemaining();
	}
	else 
	{
		player.changeShotType(shotRegular);
	}

	// SE O PLAYER ATIROU
	if (player.wantsToShoot()) 
	{
		// cria o tiro
		Tiro tiro = Tiro();
		tiro.inicializar(
			player.getShotType(), 
			player.getX(), 
			player.getY(), 
			player.getDirection()
		);
		tiros.adicionaTiroNaLista(tiro);

		// unset the flag
		player.makeNotWantToShoot();
	}

	// SE ALGUM ENEMY SUB ATIROU
	for (int i = 0; i < enemySubs.getNumeroTotalUtilizado(); i++)
	{
		if (enemySubs.getEnemySubAtIndex(i).wantsToShoot()) 
		{
			// cria o tiro
			Tiro tiro = Tiro();
			tiro.inicializar(
				enemySubs.getEnemySubAtIndex(i).getShotType(),
				enemySubs.getEnemySubAtIndex(i).getX(),
				enemySubs.getEnemySubAtIndex(i).getY(),
				enemySubs.getEnemySubAtIndex(i).getDirection()
			);			
			tiros.adicionaTiroNaLista(tiro);

			// unset the wants-to-shoot flag
			EnemySub test = EnemySub();
			test = enemySubs.getEnemySubAtIndex(i);
			test.makeNotWantToShoot();
			enemySubs.addEnemySubAtIndex(test, i);
		}
	}

	// SPAWNER: DIVERS
	if (fcnt.getFrameNumber() % 180 == 0) // 180 -> a cada 3 segundos
	{
		if (rand() % 6 == 0) // 6 -> uma chance em seis
		{
			if (divers.isSpawnerTurnedOn()) // se o spawner está ligado
			{
				divers.spawnNewRandomDiver();
			}
		}
	}

	// SPAWNER: AIR BUBBLE
	if (fcnt.getFrameNumber() % 240 == 0) // 240 -> a cada 4 segundos
	{
		if (rand() % 6 == 0) // 6 -> uma chance em seis
		{
			if (airBubbles.isSpawnerTurnedOn()) // se o spawner está ligado
			{				
				airBubbles.spawnNewRandomAirBubble();
			}
		}
	}

	// SPAWNER: ENEMY FISH
	if (fcnt.getFrameNumber() % 120 == 0) // 120 -> a cada 2 segundos
	{
		if (rand() % 4 == 0) // 4 -> uma chance em quatro
		{
			if (enemyFishes.isSpawnerTurnedOn()) // se o spawner está ligado
			{				
				enemyFishes.spawnNewRandomEnemyFish();
			}
		}
	}

	// SPAWNER: ENEMY SUB
	if (fcnt.getFrameNumber() % 120 == 0) // 120 -> a cada 2 segundos
	{
		if (rand() % 4 == 0) // 4 -> uma chance em quatro
		{
			if (enemySubs.isSpawnerTurnedOn()) // se o spawner está ligado
			{
				enemySubs.spawnNewRandomEnemySub();
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

			// destrói o diver
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

				// destrói o tiro
				tiros.removeTiroAtIndex(j);

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}

	// COLISION: TIRO X ENEMY FISH
	for (int i = 0; i < enemyFishes.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < tiros.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				enemyFishes.getEnemyFishAtIndex(i).getSprite(),
				enemyFishes.getEnemyFishAtIndex(i).getX(),
				enemyFishes.getEnemyFishAtIndex(i).getY(),
				0,
				tiros.getTiroAtIndex(j).getSprite(),
				tiros.getTiroAtIndex(j).getX(),
				tiros.getTiroAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM TIRO COM UM ENEMY FISH!

				// adiciona o enemy fish ao score e ao three grid
				interfac.matouUmEnemyFish(enemyFishes.getEnemyFishAtIndex(i).getShotType());

				// destrói o tiro
				tiros.removeTiroAtIndex(j);

				// destrói o enemy fish
				enemyFishes.removeEnemyFishAtIndex(i);
			}
		}
	}

	// COLISION: TIRO X ENEMY SUB
	for (int i = 0; i < enemySubs.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < tiros.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				enemySubs.getEnemySubAtIndex(i).getSprite(),
				enemySubs.getEnemySubAtIndex(i).getX(),
				enemySubs.getEnemySubAtIndex(i).getY(),
				0,
				tiros.getTiroAtIndex(j).getSprite(),
				tiros.getTiroAtIndex(j).getX(),
				tiros.getTiroAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM TIRO COM UM ENEMY SUB!

				// adiciona o enemy sub ao score e ao three grid
				interfac.matouUmEnemySub(enemySubs.getEnemySubAtIndex(i).getShotType());

				// destrói o tiro
				tiros.removeTiroAtIndex(j);

				// destrói o enemy fish
				enemySubs.removeEnemySubAtIndex(i);
			}
		}
	}

	// COLLISION: PLAYER X ENEMY FISH
	// TO DO

	// COLLISION: PLAYER X ENEMY SUB
	// TO DO

	// COLLISION: PLAYER X AIR BUBBLE
	for (int i = 0; i < airBubbles.getNumeroTotalUtilizado(); i++)
	{
		if (uniTestarColisao(			
			airBubbles.getAirBubbleAtIndex(i).getSprite(),
			airBubbles.getAirBubbleAtIndex(i).getX(),
			airBubbles.getAirBubbleAtIndex(i).getY(),
			0,
			player.getSprite(),
			player.getX(),
			player.getY(),
			0
		))
		{
			// COLIDIU UMA AIR BUBBLE COM O PLAYER!

			// acrescenta um pouco de oxigênio de volta ao jogo
			interfac.pegouUmaAirBubble();

			// destrói a air bubble
			airBubbles.removeAirBubbleAtIndex(i);
		}
	}
}
