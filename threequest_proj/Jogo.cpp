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

	// VERIFICA TUDO
	telaSplash_verificar();

	// DESENHA TUDO
	telaSplash_desenhar();	
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
		status = sTelaMenu;
	}
	if (gTeclado.pressionou[TECLA_ESPACO] || gTeclado.pressionou[TECLA_ENTER])
	{
		status = sTelaMenu;
	}
}

void Jogo::telaMenu_inicializar()
{
	// INICIALIZA O INT DE CURRENT CHOICE
	currentChoice = 0;

	// INICIALIZA O SELECTION FISH Y
	selectionFishY = 300;

	// INICIALIZA O MENU PICTURE
	if (!gRecursos.carregouSpriteSheet("menuBackground"))
	{
		gRecursos.carregarSpriteSheet("menuBackground", "imagens/spr_menuBackground.png");
	}
	menuBackground.setSpriteSheet("menuBackground");

	// INICIALIZA O SELECTION FISH
	if (!gRecursos.carregouSpriteSheet("fishRed"))
	{
		gRecursos.carregarSpriteSheet("fishRed", "imagens/spr_fishRed.png", 1, 4);
	}
	selectionFish.setSpriteSheet("fishRed");
	selectionFish.setInverterX(true);
}

void Jogo::telaMenu_executar()
{
	// VERIFICA TUDO
	telaMenu_verificar();

	// DESENHA TUDO
	telaMenu_desenhar();	
}

void Jogo::telaMenu_desenhar()
{
	// DESENHA O MENU BACKGROUND
	menuBackground.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	// DESENHA O SELECTION FISH
	selectionFish.desenhar(200, selectionFishY);
}

void Jogo::telaMenu_verificar()
{
	// AVANÇA ANIMAÇÃO DO SELECTION FISH
	selectionFish.avancarAnimacao();

	// POSICIONA O SELECTION FISH DE ACORDO COM O SELECTION INT
	switch (currentChoice)
	{
		case 0: // NEW GAME
			selectionFishY = 278;
			break;
		case 1: // INSTRUCTIONS
			selectionFishY = 346;
			break;
		case 2: // CREDITS
			selectionFishY = 414;
			break;
		case 3: // EXIT
			selectionFishY = 482;
			break;
	}

	// VERIFICA KEYBOARD PRESSES
	if (gTeclado.pressionou[TECLA_W] || gTeclado.pressionou[TECLA_CIMA])
	{
		if (currentChoice > 0) 
		{
			currentChoice--;
		}
		else 
		{
			currentChoice = 3;
		}
	}
	if (gTeclado.pressionou[TECLA_S] || gTeclado.pressionou[TECLA_BAIXO])
	{
		if (currentChoice < 3)
		{
			currentChoice++;
		}
		else
		{
			currentChoice = 0;
		}
	}
	if (gTeclado.pressionou[TECLA_ESPACO] || gTeclado.pressionou[TECLA_ENTER])
	{
		switch (currentChoice)
		{
		case 0: // NEW GAME
			status = sTelaJogo;
			break;
		case 1: // INSTRUCTIONS
			// status = sTelaInstructions; 
			// nyi
			break;
		case 2: // CREDITS
			frameCounterSplash.freeze();
			status = sTelaSplash;
			break;
		case 3: // EXIT
			// nyi
			break;
		}
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

	// INICIALIZA OS SCORE OVERLAYS
	if (!gRecursos.carregouSpriteSheet("scoreOverlay"))
	{
		gRecursos.carregarSpriteSheet("scoreOverlay", "imagens/spr_scoreOverlay.png");
	}
	if (!gRecursos.carregouSpriteSheet("scoreOverlaySpRed"))
	{
		gRecursos.carregarSpriteSheet("scoreOverlaySpRed", "imagens/spr_scoreOverlaySpRed.png");
	}
	if (!gRecursos.carregouSpriteSheet("scoreOverlaySpGreen"))
	{
		gRecursos.carregarSpriteSheet("scoreOverlaySpGreen", "imagens/spr_scoreOverlaySpGreen.png");
	}
	if (!gRecursos.carregouSpriteSheet("scoreOverlaySpBlue"))
	{
		gRecursos.carregarSpriteSheet("scoreOverlaySpBlue", "imagens/spr_scoreOverlaySpBlue.png");
	}
	scoreOverlay.setSpriteSheet("scoreOverlay");

	// INICIALIZA OS GRID SLOTS
	if (!gRecursos.carregouSpriteSheet("gridEmpty"))
	{
		gRecursos.carregarSpriteSheet("gridEmpty", "imagens/spr_gridEmpty.png");
	}
	if (!gRecursos.carregouSpriteSheet("gridRed"))
	{
		gRecursos.carregarSpriteSheet("gridRed", "imagens/spr_gridRed.png");
	}
	if (!gRecursos.carregouSpriteSheet("gridGreen"))
	{
		gRecursos.carregarSpriteSheet("gridGreen", "imagens/spr_gridGreen.png");
	}
	if (!gRecursos.carregouSpriteSheet("gridBlue"))
	{
		gRecursos.carregarSpriteSheet("gridBlue", "imagens/spr_gridBlue.png");
	}
	gridSlotA.setSpriteSheet("gridEmpty");
	gridSlotB.setSpriteSheet("gridEmpty");
	gridSlotC.setSpriteSheet("gridEmpty");

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

	// VERIFICA TUDO
	telaJogo_verificar();

	// DESENHA TUDO
	telaJogo_desenhar();	
}

void Jogo::telaJogo_desenhar()
{
	// DESENHA O BACKGROUND
	gameBackground.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	int rateOfAnimation = 5;
	if (frameCounterJogo.getFrameNumber() % rateOfAnimation == 0) gameBackground.avancarAnimacao();
	
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
	gameWaterSurface.desenhar(gJanela.getLargura() / 2, 124);

	// DESENHA O SCORE OVERLAY
	scoreOverlay.desenhar(gJanela.getLargura() / 2, 559);

	// DESENHA A JOGO INTERFACE
	interfac.desenhar();

	// DESENHA OS GRID SLOTS
	gridSlotA.desenhar(42, 559);
	gridSlotB.desenhar(113, 559);
	gridSlotC.desenhar(184, 559);

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

	// SE O PLAYER ESTÁ NA SUPERFÍCIE, DESLIGA OS SPAWNERS
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
	}	

	// RACIONALIZA SE DEVE COMER OXYGEN
	if (!player.isPlayerOnSurface() && !(interfac.getFillStatus() == enumFrozen))
	{
		interfac.reduceOxygen();
	}

	// ATUALIZA O SPRITE DAS GRID SLOTS COM RELAÇÃO A O QUE A ARRAY GUARDA
	switch (interfac.getThreeGridAtThisIndex(0))
	{
	case shotRed:
		gridSlotA.setSpriteSheet("gridRed");
		break;
	case shotGreen:
		gridSlotA.setSpriteSheet("gridGreen");
		break;
	case shotBlue:
		gridSlotA.setSpriteSheet("gridBlue");
		break;
	case shotNull:
		gridSlotA.setSpriteSheet("gridEmpty");
	default:
		break;
	};
	switch (interfac.getThreeGridAtThisIndex(1))
	{
	case shotRed:
		gridSlotB.setSpriteSheet("gridRed");
		break;
	case shotGreen:
		gridSlotB.setSpriteSheet("gridGreen");
		break;
	case shotBlue:
		gridSlotB.setSpriteSheet("gridBlue");
		break;
	case shotNull:
		gridSlotB.setSpriteSheet("gridEmpty");
	default:
		break;
	};
	switch (interfac.getThreeGridAtThisIndex(2))
	{
	case shotRed:
		gridSlotC.setSpriteSheet("gridRed");
		break;
	case shotGreen:
		gridSlotC.setSpriteSheet("gridGreen");
		break;
	case shotBlue:
		gridSlotC.setSpriteSheet("gridBlue");
		break;
	case shotNull:
		gridSlotC.setSpriteSheet("gridEmpty");
	default:
		break;
	};

	// SE ACONTECEU UM FULL THREE GRID
	if (interfac.getFillStatus() == enumFilled)
	{
		char temp = interfac.racionalizaThreeGrid();
		switch (temp)
		{
		case 'n':
			interfac.clearThreeGrid();
			interfac.setFillStatus(enumFilling);
			break;
		case 'r':
			interfac.setFillStatus(enumFrozen);
			interfac.pegouUmaAirBubble();
			interfac.setSpecialShotDuration();
			scoreOverlay.setSpriteSheet("scoreOverlaySpRed");
			interfac.setSpecialShotType(shotRed);
			interfac.setContentBarContext(barSpecialShot);
			interfac.stopDisplayingScore();
			player.changeShotType(shotRed);
			break;
		case 'g':
			interfac.setFillStatus(enumFrozen);
			interfac.pegouUmaAirBubble();
			interfac.setSpecialShotDuration();
			scoreOverlay.setSpriteSheet("scoreOverlaySpGreen");
			interfac.setSpecialShotType(shotGreen);
			interfac.setContentBarContext(barSpecialShot);
			interfac.stopDisplayingScore();
			player.changeShotType(shotGreen);
			break;
		case 'b':
			interfac.setFillStatus(enumFrozen);
			interfac.pegouUmaAirBubble();
			interfac.setSpecialShotDuration();
			scoreOverlay.setSpriteSheet("scoreOverlaySpBlue");
			interfac.setSpecialShotType(shotBlue);
			interfac.setContentBarContext(barSpecialShot);
			interfac.stopDisplayingScore();
			player.changeShotType(shotBlue);
			break;
		case 't':
			// FAZ AS COISAS LOUCAS QUE O THREE QUEST FAZ
			// TO DO
			// TODO
			interfac.clearThreeGrid();
			interfac.setFillStatus(enumFilling);
			break;
		}
	}

	// SE O SHOT FOR SPECIAL, DIMINUIR ELE AOS POUCOS
	if (interfac.getFillStatus() == enumFrozen)
	{
		if (interfac.getSpecialShotDuration() > 0)
		{
			interfac.drainSpecialShotDuration();
		}
		else
		{
			// FIM DO SPECIAL SHOT. VOLTAR AO NORMAL.
			interfac.clearThreeGrid();
 			interfac.setFillStatus(enumFilling);
			player.changeShotType(shotRegular);
			scoreOverlay.setSpriteSheet("scoreOverlay");
			interfac.setContentBarContext(barOxygen);
			interfac.resumeDisplayingScore();
		}
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
					// adiciona o fato ao score
					interfac.matouUmDiver();

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

	// COLLISION: TIRO ENEMY X ENEMY SUB
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

	// COLLISION: ENEMY FISH X ENEMY FISH
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
