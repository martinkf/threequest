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
		// LIB UNIC�RNIO NECESSARY
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

		// LIB UNIC�RNIO NECESSARY
		uniTerminarFrame();
	}
}

void Jogo::finalizar()
{
	//	O resto da finaliza��o vem aqui (provavelmente, em ordem inversa a inicializa��o)!

	// LIB UNIC�RNIO NECESSARY
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
	// AVAN�A ANIMA��O DO SELECTION FISH
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

	// INICIALIZA A EXPLOSION ARRAY
	explosions.inicializar();

	// INICIALIZA A SCOREKEEPING
	score.inicializar();
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

	// DESENHA A EXPLOSIONS ARRAY
	explosions.atualizar();
	explosions.desenhar();

	// DESENHA O PLAYER
	player.atualizar();
	player.desenhar();

	// DESENHA A WATER SURFACE
	gameWaterSurface.desenhar(gJanela.getLargura() / 2, 124);

	// DESENHA O SCORE OVERLAY
	scoreOverlay.desenhar(gJanela.getLargura() / 2, 559);

	// DESENHA A JOGO INTERFACE
	score.desenhar();

	// ATUALIZA O SPRITE DAS GRID SLOTS COM RELA��O A O QUE A ARRAY GUARDA
	switch (score.getThreeGridAtThisIndex(0))
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
	switch (score.getThreeGridAtThisIndex(1))
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
	switch (score.getThreeGridAtThisIndex(2))
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

	// SE O PLAYER EST� NA SUPERF�CIE, DESLIGA OS SPAWNERS
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
	if (!player.isPlayerOnSurface() && !(score.getFillStatus() == enumFrozen))
	{
		score.drainOxygen();
	}

	// SE ACONTECEU UM FULL THREE GRID
	if (score.getFillStatus() == enumFilled)
	{
		char temp = score.racionalizaThreeGrid();
		switch (temp)
		{
		case 'n':
			score.clearThreeGrid();
			score.setFillStatus(enumFilling);
			break;
		case 'r':
			score.setFillStatus(enumFrozen);
			score.pegouUmaAirBubble();
			score.setSpecialShotDuration(1000);
			scoreOverlay.setSpriteSheet("scoreOverlaySpRed");
			score.setSpecialShotType(shotRed);
			score.setContentBarContext(barSpecialShot);
			score.stopDisplayingScore();
			player.changeShotType(shotRed);
			break;
		case 'g':
			score.setFillStatus(enumFrozen);
			score.pegouUmaAirBubble();
			score.setSpecialShotDuration(1000);
			scoreOverlay.setSpriteSheet("scoreOverlaySpGreen");
			score.setSpecialShotType(shotGreen);
			score.setContentBarContext(barSpecialShot);
			score.stopDisplayingScore();
			player.changeShotType(shotGreen);
			break;
		case 'b':
			score.setFillStatus(enumFrozen);
			score.pegouUmaAirBubble();
			score.setSpecialShotDuration(500);
			scoreOverlay.setSpriteSheet("scoreOverlaySpBlue");
			score.setSpecialShotType(shotBlue);
			score.setContentBarContext(barBlueFreezer);
			score.stopDisplayingScore();
			player.changeShotType(shotBlue);
			break;
		case 't':
			clearAllThreats();
			score.clearThreeGrid();
			score.setFillStatus(enumFilling);
			break;
		}
	}

	// SE O SHOT FOR SPECIAL, DIMINUIR ELE AOS POUCOS
	if (score.getFillStatus() == enumFrozen)
	{
		if (score.getSpecialShotDuration() > 0)
		{
			score.drainSpecialShotDuration();
		}
		else
		{
			// FIM DO SPECIAL SHOT. VOLTAR AO NORMAL.
			score.clearThreeGrid();
 			score.setFillStatus(enumFilling);
			player.changeShotType(shotRegular);
			scoreOverlay.setSpriteSheet("scoreOverlay");
			score.setContentBarContext(barOxygen);
			score.resumeDisplayingScore();
		}
	}

	// SE FOI PRESSIONADO O BOT�O DE GRID RESET
	if (gTeclado.pressionou[TECLA_SHIFT_ESQ])
	{
		if (score.getFillStatus() == enumFilling)
		{
			// reseta o grid
			score.clearThreeGrid();
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
	for (int i = (enemySubs.getNumeroTotalUtilizado() - 1); i >= 0; i--)
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
		if (rand() % 4 == 0) // 4 -> uma chance em quatro
		{
			if (divers.isSpawnerTurnedOn()) // se o spawner est� ligado
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
			if (airBubbles.isSpawnerTurnedOn()) // se o spawner est� ligado
			{
				airBubbles.spawnNewRandomAirBubble();
			}
		}
	}

	// SPAWNER: ENEMY FISH
	if (frameCounterJogo.getFrameNumber() % 120 == 0) // 120 -> a cada 2 segundos
	{
		if (rand() % 2 == 0) // 2 -> uma chance em dois
		{
			if (enemyFishes.isSpawnerTurnedOn()) // se o spawner est� ligado
			{
				enemyFishes.spawnNewRandomEnemyFish();
			}
		}
	}

	// SPAWNER: ENEMY SUB
	if (frameCounterJogo.getFrameNumber() % 120 == 0) // 120 -> a cada 2 segundos
	{
		if (rand() % 2 == 0) // 2 -> uma chance em dois
		{
			if (enemySubs.isSpawnerTurnedOn()) // se o spawner est� ligado
			{
				enemySubs.spawnNewRandomEnemySub();
			}
		}
	}

	// COLLISION: PLAYER X DIVERS
	for (int i = (divers.getNumeroTotalUtilizado() - 1); i >= 0; i--)
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
			score.pegouUmDiver();

			// destr�i o diver
			divers.removeDiverAtIndex(i);
		}
	}

	// COLLISION: PLAYER X AIR BUBBLE
	for (int i = (airBubbles.getNumeroTotalUtilizado() - 1); i >= 0; i--)
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

			// acrescenta um pouco de oxig�nio de volta ao jogo
			score.pegouUmaAirBubble();

			// destr�i a air bubble
			airBubbles.removeAirBubbleAtIndex(i);
		}
	}

	// COLLISION: PLAYER X ENEMY FISH
	for (int i = (enemyFishes.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		if (uniTestarColisao(
			enemyFishes.getEnemyFishAtIndex(i).getSprite(),
			enemyFishes.getEnemyFishAtIndex(i).getX(),
			enemyFishes.getEnemyFishAtIndex(i).getY(),
			0,
			player.getSprite(),
			player.getX(),
			player.getY(),
			0
		))
		{
			// COLIDIU UM ENEMY FISH COM O PLAYER!

			// remove um pouco de o2 do player
			score.reduceOxygenByAmount(400);

			// cria uma explos�o
			Explosion testD;
			testD.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
			explosions.adicionaExplosionNaLista(testD);

			// destr�i o enemy fish
			enemyFishes.removeEnemyFishAtIndex(i);
		}
	}

	// COLLISION: PLAYER X ENEMY SUB
	for (int i = (enemySubs.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		if (uniTestarColisao(
			enemySubs.getEnemySubAtIndex(i).getSprite(),
			enemySubs.getEnemySubAtIndex(i).getX(),
			enemySubs.getEnemySubAtIndex(i).getY(),
			0,
			player.getSprite(),
			player.getX(),
			player.getY(),
			0
		))
		{
			// COLIDIU UM ENEMY SUB COM O PLAYER!

			// remove um pouco de o2 do player
			score.reduceOxygenByAmount(600);

			// cria uma explos�o
			Explosion testE;
			testE.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
			explosions.adicionaExplosionNaLista(testE);

			// destr�i o enemy sub
			enemySubs.removeEnemySubAtIndex(i);
		}
	}

	// COLLISION: PLAYER X ENEMY TIRO
	for (int i = (tirosEnemy.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		if (uniTestarColisao(
			tirosEnemy.getTiroAtIndex(i).getSprite(),
			tirosEnemy.getTiroAtIndex(i).getX(),
			tirosEnemy.getTiroAtIndex(i).getY(),
			0,
			player.getSprite(),
			player.getX(),
			player.getY(),
			0
		))
		{
			// COLIDIU UM ENEMY TIRO COM O PLAYER!

			// remove um pouco de o2 do player
			score.reduceOxygenByAmount(650);

			// destr�i o enemy tiro
			tirosEnemy.removeTiroAtIndex(i);
		}
	}

	// COLLISION: TIRO PLAYER X DIVERS
	for (int i = (divers.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (tirosPlayer.getNumeroTotalUtilizado() - 1); j >= 0; j--)
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

				// adiciona o fato ao score
				score.matouUmDiver();

				// destr�i o tiro
				if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotRed) 
				{
					tirosPlayer.removeTiroAtIndex(j);
				}

				// cria uma explos�o
				Explosion test;
				test.inicializar(divers.getDiverAtIndex(i).getX(), divers.getDiverAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destr�i o diver
				divers.removeDiverAtIndex(i);				
			}
		}
	}

	// COLLISION: TIRO PLAYER X ENEMY FISH
	for (int i = (enemyFishes.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (tirosPlayer.getNumeroTotalUtilizado() - 1); j >= 0; j--)
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
				
				// adiciona o enemy fish ao score e ao three grid
				// adiciona ao three grid se foi um tiro normal/red/green, mas adiciona somente ao score se foi blue
				if (tirosPlayer.getTiroAtIndex(j).getShotType() == shotBlue)
				{
					score.matouUmEnemyFishSemGrid();
				}
				else
				{
					score.matouUmEnemyFish(enemyFishes.getEnemyFishAtIndex(i).getShotType());
				}

				// destr�i o tiro
				if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosPlayer.removeTiroAtIndex(j);
				}

				// cria uma explos�o
				Explosion test3;
				test3.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test3);

				// destr�i o enemy fish
				enemyFishes.removeEnemyFishAtIndex(i);				
			}
		}
	}

	// COLLISION: TIRO PLAYER X ENEMY SUB
	for (int i = (enemySubs.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (tirosPlayer.getNumeroTotalUtilizado() - 1); j >= 0; j--)
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
				
				// adiciona o enemy sub ao score e ao three grid
				// adiciona ao three grid se foi um tiro normal/red/green, mas adiciona somente ao score se foi blue
				if (tirosPlayer.getTiroAtIndex(j).getShotType() == shotBlue)
				{
					score.matouUmEnemySubSemGrid();
				}
				else
				{
					score.matouUmEnemySub(enemySubs.getEnemySubAtIndex(i).getShotType());
				}

				// destr�i o tiro
				if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosPlayer.removeTiroAtIndex(j);
				}

				// cria uma explos�o
				Explosion test5;
				test5.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test5);

				// destr�i o enemy sub
				enemySubs.removeEnemySubAtIndex(i);				
			}
		}
	}

	// COLLISION: TIRO ENEMY X DIVERS
	for (int i = (divers.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (tirosEnemy.getNumeroTotalUtilizado() - 1); j >= 0; j--)
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

				// destr�i o tiro
				if (tirosEnemy.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosEnemy.removeTiroAtIndex(j);
				}

				// cria uma explos�o
				Explosion test2;
				test2.inicializar(divers.getDiverAtIndex(i).getX(), divers.getDiverAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test2);

				// destr�i o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}	

	// COLLISION: TIRO ENEMY X ENEMY FISH
	for (int i = (enemyFishes.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (tirosEnemy.getNumeroTotalUtilizado() - 1); j >= 0; j--)
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

				// destr�i o tiro
				if (tirosEnemy.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosEnemy.removeTiroAtIndex(j);
				}

				// cria uma explos�o
				Explosion test4;
				test4.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test4);

				// destr�i o enemy fish
				enemyFishes.removeEnemyFishAtIndex(i);
			}
		}
	}

	// COLLISION: TIRO ENEMY X ENEMY SUB
	for (int i = (enemySubs.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (tirosEnemy.getNumeroTotalUtilizado() - 1); j >= 0 ; j--)
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

				// destr�i o tiro
				if (tirosEnemy.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosEnemy.removeTiroAtIndex(j);
				}

				// cria uma explos�o
				Explosion test6;
				test6.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test6);

				// destr�i o enemy fish
				enemySubs.removeEnemySubAtIndex(i);
			}
		}
	}

	// COLLISION: ENEMY FISH X ENEMY FISH
	for (int i = (enemyFishes.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (enemyFishes.getNumeroTotalUtilizado() - 1); j >= 0; j--)
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
				// verifica��o necess�ria por motivos �bvios
				if (!(enemyFishes.getEnemyFishAtIndex(i).verificaSemelhanca(enemyFishes.getEnemyFishAtIndex(j))))
				{
					// cria uma explos�o
					Explosion test7;
					test7.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
					explosions.adicionaExplosionNaLista(test7);

					// destr�i o enemy fish i
					enemyFishes.removeEnemyFishAtIndex(i);

					// cria uma explos�o
					Explosion test8;
					test8.inicializar(enemyFishes.getEnemyFishAtIndex(j).getX(), enemyFishes.getEnemyFishAtIndex(j).getY());
					explosions.adicionaExplosionNaLista(test8);

					// destr�i o enemy fish j
					enemyFishes.removeEnemyFishAtIndex(j);
				}				
			}
		}
	}

	// COLLISION: ENEMY FISH X ENEMY SUB
	for (int i = (enemyFishes.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (enemySubs.getNumeroTotalUtilizado() - 1); j >= 0; j--)
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

				// cria uma explos�o
				Explosion test9;
				test9.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test9);

				// destr�i o enemy fish
				enemyFishes.removeEnemyFishAtIndex(i);

				// cria uma explos�o
				Explosion testA;
				testA.inicializar(enemySubs.getEnemySubAtIndex(j).getX(), enemySubs.getEnemySubAtIndex(j).getY());
				explosions.adicionaExplosionNaLista(testA);

				// destr�i o enemy sub
				enemySubs.removeEnemySubAtIndex(j);
			}
		}
	}

	// COLLISION: ENEMY SUB X ENEMY SUB
	for (int i = (enemySubs.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (enemySubs.getNumeroTotalUtilizado() - 1); j >= 0; j--)
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
				// verifica��o necess�ria por motivos �bvios
				if (!(enemySubs.getEnemySubAtIndex(i).verificaSemelhanca(enemySubs.getEnemySubAtIndex(j))))
				{
					// cria uma explos�o
					Explosion testB;
					testB.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
					explosions.adicionaExplosionNaLista(testB);

					// destr�i o enemy sub I
					enemySubs.removeEnemySubAtIndex(i);

					// cria uma explos�o
					Explosion testC;
					testC.inicializar(enemySubs.getEnemySubAtIndex(j).getX(), enemySubs.getEnemySubAtIndex(j).getY());
					explosions.adicionaExplosionNaLista(testC);

					// destr�i o enemy sub J
					enemySubs.removeEnemySubAtIndex(j);
				}
			}
		}
	}	
}

bool Jogo::shouldDrawPopup()
{
	return popupNeedsDrawing;
}

void Jogo::clearAllThreats()
{
	// mata todos os inimigos fish em tela
	for (int i = (enemyFishes.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		// adiciona o enemy fish ao score
		score.matouUmEnemyFishSemGrid();

		// cria uma explos�o
		Explosion test;
		test.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
		explosions.adicionaExplosionNaLista(test);

		// destr�i o enemy fish
		enemyFishes.removeEnemyFishAtIndex(i);
	}

	// mata todos os inimigos sub em tela
	for (int i = (enemySubs.getNumeroTotalUtilizado() - 1 ); i >= 0; i--)
	{
		// adiciona o enemy sub ao score
		score.matouUmEnemySubSemGrid();

		// cria uma explos�o
		Explosion test2;
		test2.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
		explosions.adicionaExplosionNaLista(test2);

		// destr�i o enemy sub
		enemySubs.removeEnemySubAtIndex(i);
	}

	// limpa a array de tiros inimigos
	tirosEnemy.clearEverything();
	
	// limpa a array de tiros meus
	tirosPlayer.clearEverythingButBlueFreezers();
}