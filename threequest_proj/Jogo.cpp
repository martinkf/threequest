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

	// INICIALIZA AS TELAS
	telaSplash_inicializar();
	telaJogo_inicializar();
	telaMenu_inicializar();
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
			case sTelaSplash:
				telaSplash_executar();
				break;
			case sTelaMenu:
				telaMenu_executar();
				break;
			case sTelaJogo:
				telaJogo_executar();
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

void Jogo::setStatusJogo(StatusJogo input_)
{
	status = input_;
}

void Jogo::telaSplash_inicializar()
{
	// INICIALIZA O FRAMECOUNTER
	frameCounterSplash.inicializar();

	// INICIALIZA O SPLASH PICTURE
	if (!gRecursos.carregouSpriteSheet("splashPic"))
	{
		gRecursos.carregarSpriteSheet("splashPic", "imagens/spr_splashPic.png");
	}
	splashPicture.setSpriteSheet("splashPic");
}

void Jogo::telaSplash_executar()
{
	// ATUALIZA O FRAMECOUNTER
	frameCounterSplash.tick();

	// DESENHA TUDO
	telaSplash_desenhar();

	// VERIFICA TUDO
	telaSplash_verificar();
}

void Jogo::telaSplash_desenhar()
{
	// DESENHA O SPLASH PICTURE
	splashPicture.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
}

void Jogo::telaSplash_verificar()
{
	if (frameCounterSplash.getFrameNumber() == 180)
	{
		// SAI DESSA SPLASH SCREEN
		setStatusJogo(sTelaMenu);
	}
}

void Jogo::telaMenu_inicializar()
{
	// INICIALIZA O FRAMECOUNTER
	frameCounterMenuTemp.inicializar();

	// INICIALIZA O SPLASH PICTURE
	if (!gRecursos.carregouSpriteSheet("menuBackground"))
	{
		gRecursos.carregarSpriteSheet("menuBackground", "imagens/spr_menuBackground.png");
	}
	menuBackground.setSpriteSheet("menuBackground");
}

void Jogo::telaMenu_executar()
{
	// ATUALIZA O FRAMECOUNTER
	frameCounterMenuTemp.tick();

	// DESENHA TUDO
	telaMenu_desenhar();

	// VERIFICA TUDO
	telaMenu_verificar();
}

void Jogo::telaMenu_desenhar()
{
	// DESENHA O MENU BACKGROUND
	menuBackground.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
}

void Jogo::telaMenu_verificar()
{
	if (frameCounterMenuTemp.getFrameNumber() == 240) // ISSO TUDO É MUITO TEMPORÁRIO NÉ MDS  TE LIGA
	{
		// SAI DESSE MENU SCREEN
		setStatusJogo(sTelaJogo);
	}
}

void Jogo::telaJogo_inicializar()
{
	// INICIALIZA O FRAMECOUNTER
	frameCounterJogo.inicializar();

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

	// INICIALIZA O SCORE OVERLAY
	if (!gRecursos.carregouSpriteSheet("scoreOverlay"))
	{
		gRecursos.carregarSpriteSheet("scoreOverlay", "imagens/spr_scoreOverlay.png");
	}
	scoreOverlay.setSpriteSheet("scoreOverlay");

	// INICIALIZA O POPUP MENU BACKGROUND
	if (!gRecursos.carregouSpriteSheet("popupBackground"))
	{
		gRecursos.carregarSpriteSheet("popupBackground", "imagens/spr_popupBackground.png");
	}
	popupBackground.setSpriteSheet("popupBackground");

	// INICIALIZA A POPUP
	popupNeedsDrawing = true;

	// INICIALIZA O PLAYER
	player.inicializar();

	// INICIALIZA O TIRO ENEMY ARRAY
	tirosEnemy.inicializar();

	// INICIALIZA O TIRO PLAYER ARRAY
	tirosPlayer.inicializar();

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

void Jogo::telaJogo_executar()
{
	// ATUALIZA O FRAMECOUNTER
	frameCounterJogo.tick();

	// DESENHA TUDO
	telaJogo_desenhar();

	// VERIFICA TUDO
	telaJogo_verificar();
}

void Jogo::telaJogo_desenhar()
{
	// DESENHA O BACKGROUND
	gameBackground.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	int rateOfAnimation = 5;
	if (frameCounterJogo.getFrameNumber() % rateOfAnimation == 0) gameBackground.avancarAnimacao();

	// DESENHA A JOGO INTERFACE
	interfac.desenhar();

	// DESENHA A DIVER ARRAY
	divers.atualizar();
	divers.desenhar();

	// DESENHA A TIRO ENEMY ARRAY
	tirosEnemy.atualizar();
	tirosEnemy.desenhar();

	// DESENHA A TIRO PLAYER ARRAY
	tirosPlayer.atualizar();
	tirosPlayer.desenhar();

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

	// DESENHA O SCORE OVERLAY
	scoreOverlay.desenhar(gJanela.getLargura() / 2, 559);

	// DESENHA O POPUP MENU
	if (shouldDrawPopup()) 
	{
		popupBackground.desenhar(gJanela.getLargura() / 2, (gJanela.getAltura() / 2) - 50);
	}
}

void Jogo::telaJogo_verificar()
{
	// TEMP TEST
	// timer para sumir o popup
	if (frameCounterJogo.getFrameNumber() == 360) 
	{
		popupNeedsDrawing = false;
	}

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
		tirosPlayer.adicionaTiroNaLista(tiro);

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
			tirosEnemy.adicionaTiroNaLista(tiro);

			// unset the wants-to-shoot flag
			EnemySub test = EnemySub();
			test = enemySubs.getEnemySubAtIndex(i);
			test.makeNotWantToShoot();
			enemySubs.addEnemySubAtIndex(test, i);
		}
	}

	// SPAWNER: DIVERS
	if (frameCounterJogo.getFrameNumber() % 180 == 0) // 180 -> a cada 3 segundos
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
	if (frameCounterJogo.getFrameNumber() % 240 == 0) // 240 -> a cada 4 segundos
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
	if (frameCounterJogo.getFrameNumber() % 120 == 0) // 120 -> a cada 2 segundos
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
	if (frameCounterJogo.getFrameNumber() % 120 == 0) // 120 -> a cada 2 segundos
	{
		if (rand() % 4 == 0) // 4 -> uma chance em quatro
		{
			if (enemySubs.isSpawnerTurnedOn()) // se o spawner está ligado
			{
				enemySubs.spawnNewRandomEnemySub();
			}
		}
	}

	// COLLISION: PLAYER X DIVERS
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

	// COLLISION: TIRO PLAYER X DIVERS
	for (int i = 0; i < divers.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < tirosPlayer.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				divers.getDiverAtIndex(i).getSprite(),
				divers.getDiverAtIndex(i).getX(),
				divers.getDiverAtIndex(i).getY(),
				0,
				tirosPlayer.getTiroAtIndex(j).getSprite(),
				tirosPlayer.getTiroAtIndex(j).getX(),
				tirosPlayer.getTiroAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM TIRO PLAYER COM UM DIVER!
				if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotBlue) // tiros azuis do player não matam!
				{				
					// destrói o tiro
					if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotRed) 
					{
						tirosPlayer.removeTiroAtIndex(j);
					}

					// destrói o diver
					divers.removeDiverAtIndex(i);
				}
			}
		}
	}

	// COLLISION: TIRO ENEMY X DIVERS
	for (int i = 0; i < divers.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < tirosEnemy.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				divers.getDiverAtIndex(i).getSprite(),
				divers.getDiverAtIndex(i).getX(),
				divers.getDiverAtIndex(i).getY(),
				0,
				tirosEnemy.getTiroAtIndex(j).getSprite(),
				tirosEnemy.getTiroAtIndex(j).getX(),
				tirosEnemy.getTiroAtIndex(j).getY(),
				0
				))
			{
				// COLIDIU UM TIRO PLAYER COM UM DIVER!

				// destrói o tiro
				if (tirosEnemy.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosEnemy.removeTiroAtIndex(j);
				}

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}

	// COLLISION: TIRO PLAYER X ENEMY FISH
	for (int i = 0; i < enemyFishes.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < tirosPlayer.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				enemyFishes.getEnemyFishAtIndex(i).getSprite(),
				enemyFishes.getEnemyFishAtIndex(i).getX(),
				enemyFishes.getEnemyFishAtIndex(i).getY(),
				0,
				tirosPlayer.getTiroAtIndex(j).getSprite(),
				tirosPlayer.getTiroAtIndex(j).getX(),
				tirosPlayer.getTiroAtIndex(j).getY(),
				0
				))
			{
				// COLIDIU UM TIRO PLAYER COM UM ENEMY FISH!
				if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotBlue) // tiros azuis do player não matam!
				{				
					// adiciona o enemy fish ao score e ao three grid
					interfac.matouUmEnemyFish(enemyFishes.getEnemyFishAtIndex(i).getShotType());

					// destrói o tiro
					if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotRed)
					{
						tirosPlayer.removeTiroAtIndex(j);
					}

					// destrói o enemy fish
					enemyFishes.removeEnemyFishAtIndex(i);
				}
			}
		}
	}

	// COLLISION: TIRO ENEMY X ENEMY FISH
	for (int i = 0; i < enemyFishes.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < tirosEnemy.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				enemyFishes.getEnemyFishAtIndex(i).getSprite(),
				enemyFishes.getEnemyFishAtIndex(i).getX(),
				enemyFishes.getEnemyFishAtIndex(i).getY(),
				0,
				tirosEnemy.getTiroAtIndex(j).getSprite(),
				tirosEnemy.getTiroAtIndex(j).getX(),
				tirosEnemy.getTiroAtIndex(j).getY(),
				0
				))
			{
				// COLIDIU UM TIRO ENEMY COM UM ENEMY FISH!

				// destrói o tiro
				if (tirosEnemy.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosEnemy.removeTiroAtIndex(j);
				}

				// destrói o enemy fish
				enemyFishes.removeEnemyFishAtIndex(i);
			}
		}
	}

	// COLLISION: TIRO PLAYER X ENEMY SUB
	for (int i = 0; i < enemySubs.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < tirosPlayer.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				enemySubs.getEnemySubAtIndex(i).getSprite(),
				enemySubs.getEnemySubAtIndex(i).getX(),
				enemySubs.getEnemySubAtIndex(i).getY(),
				0,
				tirosPlayer.getTiroAtIndex(j).getSprite(),
				tirosPlayer.getTiroAtIndex(j).getX(),
				tirosPlayer.getTiroAtIndex(j).getY(),
				0
				))
			{
				// COLIDIU UM TIRO PLAYER COM UM ENEMY SUB!
				if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotBlue) // tiros azuis do player não matam!
				{
					// adiciona o enemy sub ao score e ao three grid
					interfac.matouUmEnemySub(enemySubs.getEnemySubAtIndex(i).getShotType());

					// destrói o tiro
					if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotRed)
					{
						tirosPlayer.removeTiroAtIndex(j);
					}

					// destrói o enemy fish
					enemySubs.removeEnemySubAtIndex(i);
				}				
			}
		}
	}

	// COLISION: TIRO ENEMY X ENEMY SUB
	for (int i = 0; i < enemySubs.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < tirosEnemy.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				enemySubs.getEnemySubAtIndex(i).getSprite(),
				enemySubs.getEnemySubAtIndex(i).getX(),
				enemySubs.getEnemySubAtIndex(i).getY(),
				0,
				tirosEnemy.getTiroAtIndex(j).getSprite(),
				tirosEnemy.getTiroAtIndex(j).getX(),
				tirosEnemy.getTiroAtIndex(j).getY(),
				0
				))
			{
				// COLIDIU UM TIRO COM UM ENEMY SUB!

				// destrói o tiro
				if (tirosEnemy.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosEnemy.removeTiroAtIndex(j);
				}

				// destrói o enemy fish
				enemySubs.removeEnemySubAtIndex(i);
			}
		}
	}

	//COLLISION: ENEMY FISH X ENEMY FISH
	for (int i = 0; i < enemyFishes.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < enemyFishes.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				enemyFishes.getEnemyFishAtIndex(i).getSprite(),
				enemyFishes.getEnemyFishAtIndex(i).getX(),
				enemyFishes.getEnemyFishAtIndex(i).getY(),
				0,
				enemyFishes.getEnemyFishAtIndex(j).getSprite(),
				enemyFishes.getEnemyFishAtIndex(j).getX(),
				enemyFishes.getEnemyFishAtIndex(j).getY(),
				0
				))
			{
				// COLIDIU UM ENEMY FISH COM UM ENEMY FISH!
				// verificação necessária por motivos óbvios
				if (!(enemyFishes.getEnemyFishAtIndex(i).verificaSemelhanca(enemyFishes.getEnemyFishAtIndex(j))))
				{
					// destrói o enemy fish i
					enemyFishes.removeEnemyFishAtIndex(i);

					// destrói o enemy fish j
					enemyFishes.removeEnemyFishAtIndex(j);
				}				
			}
		}
	}

	// COLLISION: ENEMY FISH X ENEMY SUB
	for (int i = 0; i < enemyFishes.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < enemySubs.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				enemyFishes.getEnemyFishAtIndex(i).getSprite(),
				enemyFishes.getEnemyFishAtIndex(i).getX(),
				enemyFishes.getEnemyFishAtIndex(i).getY(),
				0,
				enemySubs.getEnemySubAtIndex(j).getSprite(),
				enemySubs.getEnemySubAtIndex(j).getX(),
				enemySubs.getEnemySubAtIndex(j).getY(),
				0
				))
			{
				// COLIDIU UM ENEMY FISH COM UM ENEMY SUB!

				// destrói o enemy fish
				enemyFishes.removeEnemyFishAtIndex(i);

				// destrói o enemy sub
				enemySubs.removeEnemySubAtIndex(j);
			}
		}
	}

	// COLLISION: ENEMY SUB X ENEMY SUB
	for (int i = 0; i < enemySubs.getNumeroTotalUtilizado(); i++)
	{
		for (int j = 0; j < enemySubs.getNumeroTotalUtilizado(); j++)
		{
			if (uniTestarColisao(
				enemySubs.getEnemySubAtIndex(i).getSprite(),
				enemySubs.getEnemySubAtIndex(i).getX(),
				enemySubs.getEnemySubAtIndex(i).getY(),
				0,
				enemySubs.getEnemySubAtIndex(j).getSprite(),
				enemySubs.getEnemySubAtIndex(j).getX(),
				enemySubs.getEnemySubAtIndex(j).getY(),
				0
				))
			{
				// COLIDIU UM ENEMY SUB COM UM ENEMY SUB!
				// verificação necessária por motivos óbvios
				if (!(enemySubs.getEnemySubAtIndex(i).verificaSemelhanca(enemySubs.getEnemySubAtIndex(j))))
				{
					// destrói o enemy sub I
					enemySubs.removeEnemySubAtIndex(i);

					// destrói o enemy sub J
					enemySubs.removeEnemySubAtIndex(j);
				}
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

bool Jogo::shouldDrawPopup()
{
	return popupNeedsDrawing;
}
