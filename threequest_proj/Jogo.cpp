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
	status = sTelaSplash;

	// INICIALIZA AS TELAS
	telaSplash_inicializar();
	telaJogo_inicializar();
	telaInstructions_inicializar();
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
			case sTelaInstructions:
				telaInstructions_executar();
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
	// INICIALIZA A MENU MUSIC
	if (!gRecursos.carregouMusica("menuMusic")) 
	{
		gRecursos.carregarMusica("menuMusic", "musica/music_main.mp3");
	}
	musicIsPlaying = false;

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
	// TOCA A MÚSICA
	if (!musicIsPlaying) 
	{
		gMusica.tocar("menuMusic", true);
		musicIsPlaying = true;
	}

	// VERIFICA TUDO
	telaMenu_verificar();

	// DESENHA TUDO
	telaMenu_desenhar();	
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
			status = sTelaInstructions;
			break;
		case 2: // CREDITS
			frameCounterSplash.freeze();
			status = sTelaSplash;
			break;
		case 3: // EXIT			
			gEventos.emitirEventoDeSaida();
			break;
		}
	}
}

void Jogo::telaInstructions_inicializar()
{
	// INICIALIZA A PICTURE
	if (!gRecursos.carregouSpriteSheet("instructions"))
	{
		gRecursos.carregarSpriteSheet("instructions", "imagens/spr_instructions.png");
	}
	instructionsPicture.setSpriteSheet("instructions");
}

void Jogo::telaInstructions_executar()
{
	// LISTENS TO KEYBOARD INPUT
	if (gTeclado.pressionou[TECLA_ESPACO] || gTeclado.pressionou[TECLA_ENTER])
	{
		status = sTelaMenu;
	}

	// DESENHA A TELA
	telaInstructions_desenhar();
}

void Jogo::telaInstructions_desenhar()
{
	// DESENHA A PICTURE
	instructionsPicture.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
}

void Jogo::telaMenu_desenhar()
{
	// DESENHA O MENU BACKGROUND
	menuBackground.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	// DESENHA O SELECTION FISH
	selectionFish.desenhar(200, selectionFishY);
}

void Jogo::telaJogo_inicializar()
{
	// CARREGA OS SONS
	if (!gRecursos.carregouAudio("sound_dead"))
	{
		gRecursos.carregarAudio("sound_dead", "som/sound_dead.mp3");
	}
	if (!gRecursos.carregouAudio("sound_enemyShot"))
	{
		gRecursos.carregarAudio("sound_enemyShot", "som/sound_enemyShot.mp3");
	}
	if (!gRecursos.carregouAudio("sound_explosion"))
	{
		gRecursos.carregarAudio("sound_explosion", "som/sound_explosion.mp3");
	}
	if (!gRecursos.carregouAudio("sound_gotStuff"))
	{
		gRecursos.carregarAudio("sound_gotStuff", "som/sound_gotStuff.mp3");
	}
	if (!gRecursos.carregouAudio("sound_playerShot"))
	{
		gRecursos.carregarAudio("sound_playerShot", "som/sound_playerShot.mp3");
	}
	if (!gRecursos.carregouAudio("sound_playerSpecialShot"))
	{
		gRecursos.carregarAudio("sound_playerSpecialShot", "som/sound_playerSpecialShot.mp3");
	}
	if (!gRecursos.carregouAudio("sound_tq"))
	{
		gRecursos.carregarAudio("sound_tq", "som/sound_tq.mp3");
	}

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
	if (!gRecursos.carregouSpriteSheet("popupScoreBg"))
	{
		gRecursos.carregarSpriteSheet("popupScoreBg", "imagens/spr_popupScoreBg.png");
	}	
	popupBackground.setSpriteSheet("popupScoreBg");

	// INICIALIZA O PLAYER
	player.inicializar();

	// INICIALIZA A POPUP
	popupNeedsDrawing = false;

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
	// QUERO MESMO PARAR A MÚSICA?
	if (musicIsPlaying) 
	{ 
		musicIsPlaying = false;
		gMusica.parar();
	}

	// ATUALIZA O FRAMECOUNTER
	frameCounterJogo.tick();

	// VERIFICA TUDO
	telaJogo_verificar();

	// DESENHA TUDO
	telaJogo_desenhar();	
}

void Jogo::telaJogo_verificar()
{
	// Verifica se quer skippar o popup
	if (popupNeedsDrawing)
	{
		if (gTeclado.pressionou[TECLA_ESPACO])
		{
			popupNeedsDrawing = false;
			player.unfreeze();
			score.clearAllScores();
			score.stopDisplayingResults();
			
			if (score.getNumberOfLives() < 1)
			{
				// reseta o número de lives
				score.resetLives();

				// volta para o menu
				status = sTelaMenu;
			}
		}
	}

	// SE O PLAYER ESTÁ NA SUPERFÍCIE, DESLIGA OS SPAWNERS
	if (player.isPlayerOnSurface())
	{
		// desliga os spawners
		divers.turnOffSpawner();
		airBubbles.turnOffSpawner();
		enemyFishes.turnOffSpawner();
		enemySubs.turnOffSpawner();

		if (gameStarted == true) 
		{
			// MORTE POR SUBMERGÊNCIA
			telaJogo_mortePorSubmergencia();
		}
	}
	else
	{
		// liga os spawners
		divers.turnOnSpawner();
		airBubbles.turnOnSpawner();
		enemyFishes.turnOnSpawner();
		enemySubs.turnOnSpawner();

		gameStarted = true;
	}	

	// RACIONALIZA SE DEVE COMER OXYGEN
	if (!player.isPlayerOnSurface() && !(score.getFillStatus() == enumFrozen))
	{
		score.drainOxygen();
	}

	// RACIONALIZA SE MORREU POR ASFIXIA
	if (score.getOxygenLeft() < 0)
	{
		// MORTE POR ASFIXIA.
		if (gameStarted == true)
		{
			telaJogo_mortePorAsfixia();
		}
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
			som.setAudio("sound_tq");
			som.tocar();

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
			som.setAudio("sound_tq");
			som.tocar();

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
			som.setAudio("sound_tq");
			som.tocar();

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
			som.setAudio("sound_tq");
			som.tocar();

			score.obteveThreeQuest();
			telaJogo_clearAllThreats();
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

	// SE FOI PRESSIONADO O BOTÃO DE GRID RESET
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

		// dá play no som
		if (player.getShotType() == shotRegular)
		{
			som.setAudio("sound_playerShot");
		}
		else
		{
			som.setAudio("sound_playerSpecialShot");
		}
		som.tocar();

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

			// dá play no som			
			som.setAudio("sound_enemyShot");
			som.tocar();
		}
	}

	// SPAWNER: DIVERS
	if (frameCounterJogo.getFrameNumber() % 180 == 0) // 180 -> a cada 3 segundos
	{
		if (rand() % 4 == 0) // 4 -> uma chance em quatro
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
				//airBubbles.spawnNewRandomAirBubble();
			}
		}
	}

	// SPAWNER: ENEMY FISH
	if (frameCounterJogo.getFrameNumber() % 120 == 0) // 120 -> a cada 2 segundos
	{
		if (rand() % 2 == 0) // 2 -> uma chance em dois
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
		if (rand() % 2 == 0) // 2 -> uma chance em dois
		{
			if (enemySubs.isSpawnerTurnedOn()) // se o spawner está ligado
			{
				enemySubs.spawnNewRandomEnemySub();
			}
		}
	}

	// COLLISION: PLAYER X DIVERS
	telaJogo_collisionPlayerDiver();
	// COLLISION: PLAYER X AIR BUBBLE
	telaJogo_collisionPlayerBubble();
	// COLLISION: PLAYER X ENEMY FISH
	telaJogo_collisionPlayerFish();
	// COLLISION: PLAYER X ENEMY SUB
	telaJogo_collisionPlayerSub();
	// COLLISION: PLAYER X ENEMY TIRO
	telaJogo_collisionPlayerEnemyTiro();
	// COLLISION: TIRO PLAYER X DIVERS
	telaJogo_collisionFriendlyTiroDiver();
	// COLLISION: TIRO PLAYER X ENEMY FISH
	telaJogo_collisionFriendlyTiroFish();
	// COLLISION: TIRO PLAYER X ENEMY SUB
	telaJogo_collisionFriendlyTiroSub();
	// COLLISION: TIRO ENEMY X DIVERS
	telaJogo_collisionEnemyTiroDiver();
	// COLLISION: TIRO ENEMY X ENEMY FISH
	telaJogo_collisionEnemyTiroFish();
	// COLLISION: TIRO ENEMY X ENEMY SUB
	telaJogo_collisionEnemyTiroSub();
	// COLLISION: ENEMY FISH X DIVER
	telaJogo_collisionFishDiver();
	// COLLISION: ENEMY FISH X ENEMY FISH
	telaJogo_collisionFishFish();
	// COLLISION: ENEMY FISH X ENEMY SUB
	telaJogo_collisionFishSub();
	// COLLISION: ENEMY SUB X DIVER
	telaJogo_collisionSubDiver();
	// COLLISION: ENEMY SUB X ENEMY SUB
	telaJogo_collisionSubSub();
}

void Jogo::telaJogo_mortePorSubmergencia()
{
	// dá play no som
	som.setAudio("sound_dead");
	som.tocar();

	// paralisa o jogo por enquanto
	gameStarted = false;

	// volta a chamar a popup
	popupNeedsDrawing = true;

	// limpa todos os elementos do oceano, bons ou maus
	telaJogo_clearAll();

	// desenha o score information
	score.setDeathBonus(true);
	score.startDisplayingResults();

	// remove uma vida
	score.removeALife();

	// reinicia o player
	player.inicializar();

	// congela o movimento do player por enquanto
	player.freeze();
}

void Jogo::telaJogo_mortePorAsfixia()
{
	// dá play no som
	som.setAudio("sound_dead");
	som.tocar();

	// paralisa o jogo por enquanto
	gameStarted = false;

	// volta a chamar a popup
	popupNeedsDrawing = true;

	// limpa todos os elementos do oceano, bons ou maus
	telaJogo_clearAll();

	// desenha o score information
	score.setDeathBonus(false);
	score.startDisplayingResults();

	// remove uma vida
	score.removeALife();

	// reinicia o player
	player.inicializar();

	// congela o movimento do player por enquanto
	player.freeze();
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

	// ATUALIZA O SPRITE DAS GRID SLOTS COM RELAÇÃO A O QUE A ARRAY GUARDA
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
	if (popupNeedsDrawing)
	{
		popupBackground.desenhar(gJanela.getLargura() / 2, (gJanela.getAltura() / 2) - 50);
	}

	// DESENHA A JOGO INTERFACE
	score.desenhar();
}

void Jogo::telaJogo_clearAll()
{
	enemyFishes.clearEverything();
	enemySubs.clearEverything();
	tirosEnemy.clearEverything();
	tirosPlayer.clearEverything();
	divers.clearEverything();
	airBubbles.clearEverything();
}

void Jogo::telaJogo_clearAllThreats()
{
	// mata todos os inimigos fish em tela
	for (int i = (enemyFishes.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		// adiciona o enemy fish ao score
		score.matouUmEnemyFishSemGrid();

		// cria uma explosão
		Explosion test;
		test.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
		explosions.adicionaExplosionNaLista(test);

		// destrói o enemy fish
		enemyFishes.removeEnemyFishAtIndex(i);
	}

	// mata todos os inimigos sub em tela
	for (int i = (enemySubs.getNumeroTotalUtilizado() - 1 ); i >= 0; i--)
	{
		// adiciona o enemy sub ao score
		score.matouUmEnemySubSemGrid();

		// cria uma explosão
		Explosion test2;
		test2.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
		explosions.adicionaExplosionNaLista(test2);

		// destrói o enemy sub
		enemySubs.removeEnemySubAtIndex(i);
	}

	// limpa a array de tiros inimigos
	tirosEnemy.clearEverything();
	
	// limpa a array de tiros meus
	tirosPlayer.clearEverythingButBlueFreezers();
}

void Jogo::telaJogo_collisionPlayerDiver()
{
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

			// dá play no som
			som.setAudio("sound_gotStuff");
			som.tocar();

			// adiciona um diver ao score
			score.pegouUmDiver();

			// destrói o diver
			divers.removeDiverAtIndex(i);
		}
	}
}

void Jogo::telaJogo_collisionPlayerBubble()
{
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

			// dá play no som
			som.setAudio("sound_gotStuff");
			som.tocar();

			// acrescenta um pouco de oxigênio de volta ao jogo
			score.pegouUmaAirBubble();

			// destrói a air bubble
			airBubbles.removeAirBubbleAtIndex(i);
		}
	}
}

void Jogo::telaJogo_collisionPlayerFish()
{
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
			if(score.getContentBarContext() == barOxygen)
			{
				score.reduceOxygenByAmount(400);
			}

			// dá play no som
			som.setAudio("sound_explosion");
			som.tocar();

			// cria uma explosão
			Explosion test;
			test.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
			explosions.adicionaExplosionNaLista(test);

			// destrói o enemy fish
			enemyFishes.removeEnemyFishAtIndex(i);
		}
	}
}

void Jogo::telaJogo_collisionPlayerSub()
{
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
			if (score.getContentBarContext() == barOxygen)
			{
				score.reduceOxygenByAmount(600);
			}

			// dá play no som
			som.setAudio("sound_explosion");
			som.tocar();

			// cria uma explosão
			Explosion test;
			test.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
			explosions.adicionaExplosionNaLista(test);

			// destrói o enemy sub
			enemySubs.removeEnemySubAtIndex(i);
		}
	}
}

void Jogo::telaJogo_collisionPlayerEnemyTiro()
{
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
			if (score.getContentBarContext() == barOxygen)
			{
				score.reduceOxygenByAmount(650);
			}

			// dá play no som
			som.setAudio("sound_explosion");
			som.tocar();

			// destrói o enemy tiro
			tirosEnemy.getTiroAtIndex(i).destruir();
			tirosEnemy.removeTiroAtIndex(i);
		}
	}
}

void Jogo::telaJogo_collisionFriendlyTiroDiver()
{
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

				// destrói o tiro
				if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosPlayer.getTiroAtIndex(j).destruir();
					tirosPlayer.removeTiroAtIndex(j);
				}

				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão
				Explosion test;
				test.inicializar(divers.getDiverAtIndex(i).getX(), divers.getDiverAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}
}

void Jogo::telaJogo_collisionFriendlyTiroFish()
{
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

				// destrói o tiro
				if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotRed)
				{					
					tirosPlayer.getTiroAtIndex(j).destruir();
					tirosPlayer.removeTiroAtIndex(j);
				}

				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão
				Explosion test;
				test.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destrói o enemy fish
				enemyFishes.removeEnemyFishAtIndex(i);
			}
		}
	}
}

void Jogo::telaJogo_collisionFriendlyTiroSub()
{
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

				// destrói o tiro
				if (tirosPlayer.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosPlayer.getTiroAtIndex(j).destruir();
					tirosPlayer.removeTiroAtIndex(j);
				}

				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão
				Explosion test;
				test.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destrói o enemy sub
				enemySubs.removeEnemySubAtIndex(i);
			}
		}
	}
}

void Jogo::telaJogo_collisionEnemyTiroDiver()
{
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

				// destrói o tiro
				if (tirosEnemy.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosEnemy.getTiroAtIndex(j).destruir();
					tirosEnemy.removeTiroAtIndex(j);
				}

				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão
				Explosion test;
				test.inicializar(divers.getDiverAtIndex(i).getX(), divers.getDiverAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}
}

void Jogo::telaJogo_collisionEnemyTiroFish()
{
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

				// destrói o tiro
				if (tirosEnemy.getTiroAtIndex(j).getShotType() != shotRed)
				{
					tirosEnemy.getTiroAtIndex(j).destruir();
					tirosEnemy.removeTiroAtIndex(j);
				}

				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão
				Explosion test;
				test.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destrói o enemy fish
				enemyFishes.removeEnemyFishAtIndex(i);
			}
		}
	}
}

void Jogo::telaJogo_collisionEnemyTiroSub()
{
	for (int i = (enemySubs.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (tirosEnemy.getNumeroTotalUtilizado() - 1); j >= 0; j--)
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
					tirosEnemy.getTiroAtIndex(j).destruir();
					tirosEnemy.removeTiroAtIndex(j);
				}

				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão
				Explosion test;
				test.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destrói o enemy fish
				enemySubs.removeEnemySubAtIndex(i);
			}
		}
	}
}

void Jogo::telaJogo_collisionFishDiver()
{
	for (int i = (divers.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (enemyFishes.getNumeroTotalUtilizado() - 1); j >= 0; j--)
		{
			if (uniTestarColisao(
				divers.getDiverAtIndex(i).getSprite(),
				divers.getDiverAtIndex(i).getX(),
				divers.getDiverAtIndex(i).getY(),
				0,
				enemyFishes.getEnemyFishAtIndex(j).getSprite(),
				enemyFishes.getEnemyFishAtIndex(j).getX(),
				enemyFishes.getEnemyFishAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM ENEMY FISH COM UM DIVER!
				
				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão
				Explosion test;
				test.inicializar(divers.getDiverAtIndex(i).getX(), divers.getDiverAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}
}

void Jogo::telaJogo_collisionFishFish()
{
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
				// verificação necessária por motivos óbvios
				if (!(enemyFishes.getEnemyFishAtIndex(i).verificaSemelhanca(enemyFishes.getEnemyFishAtIndex(j))))
				{
					// cria uma explosão
					Explosion test;
					test.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
					explosions.adicionaExplosionNaLista(test);

					// destrói o enemy fish i
					enemyFishes.removeEnemyFishAtIndex(i);

					// dá play no som
					som.setAudio("sound_explosion");
					som.tocar();

					// cria uma explosão
					Explosion test2;
					test2.inicializar(enemyFishes.getEnemyFishAtIndex(j).getX(), enemyFishes.getEnemyFishAtIndex(j).getY());
					explosions.adicionaExplosionNaLista(test2);

					// destrói o enemy fish j
					enemyFishes.removeEnemyFishAtIndex(j);
				}
			}
		}
	}
}

void Jogo::telaJogo_collisionFishSub()
{
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

				// cria uma explosão
				Explosion test;
				test.inicializar(enemyFishes.getEnemyFishAtIndex(i).getX(), enemyFishes.getEnemyFishAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destrói o enemy fish
				enemyFishes.removeEnemyFishAtIndex(i);

				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão
				Explosion test2;
				test2.inicializar(enemySubs.getEnemySubAtIndex(j).getX(), enemySubs.getEnemySubAtIndex(j).getY());
				explosions.adicionaExplosionNaLista(test2);

				// destrói o enemy sub
				enemySubs.removeEnemySubAtIndex(j);
			}
		}
	}
}

void Jogo::telaJogo_collisionSubDiver()
{
	for (int i = (divers.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (enemySubs.getNumeroTotalUtilizado() - 1); j >= 0; j--)
		{
			if (uniTestarColisao(
				divers.getDiverAtIndex(i).getSprite(),
				divers.getDiverAtIndex(i).getX(),
				divers.getDiverAtIndex(i).getY(),
				0,
				enemySubs.getEnemySubAtIndex(j).getSprite(),
				enemySubs.getEnemySubAtIndex(j).getX(),
				enemySubs.getEnemySubAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM ENEMY SUB COM UM DIVER!

				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão
				Explosion test;
				test.inicializar(divers.getDiverAtIndex(i).getX(), divers.getDiverAtIndex(i).getY());
				explosions.adicionaExplosionNaLista(test);

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}
}

void Jogo::telaJogo_collisionSubSub()
{
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
				// verificação necessária por motivos óbvios
				if (!(enemySubs.getEnemySubAtIndex(i).verificaSemelhanca(enemySubs.getEnemySubAtIndex(j))))
				{
					// cria uma explosão
					Explosion test;
					test.inicializar(enemySubs.getEnemySubAtIndex(i).getX(), enemySubs.getEnemySubAtIndex(i).getY());
					explosions.adicionaExplosionNaLista(test);

					// destrói o enemy sub I
					enemySubs.removeEnemySubAtIndex(i);

					// dá play no som
					som.setAudio("sound_explosion");
					som.tocar();

					// cria uma explosão
					Explosion test2;
					test2.inicializar(enemySubs.getEnemySubAtIndex(j).getX(), enemySubs.getEnemySubAtIndex(j).getY());
					explosions.adicionaExplosionNaLista(test2);

					// destrói o enemy sub J
					enemySubs.removeEnemySubAtIndex(j);
				}
			}
		}
	}
}