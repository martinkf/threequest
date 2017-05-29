#include "TelaJogo.h"

TelaJogo::TelaJogo()
{
}

TelaJogo::~TelaJogo()
{
}

void TelaJogo::inicializar()
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
	
	// INICIALIZA O BACKGROUND
	if (!gRecursos.carregouSpriteSheet("gameBackground"))
	{
		gRecursos.carregarSpriteSheet("gameBackground", "imagens/spr_gameBackground.png", 0, 2);
	}
	gameBackground.setSpriteSheet("gameBackground");
	gameBackground.setVelocidadeAnimacao(0.5);

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

	// INICIALIZA A ENEMY ARRAY
	enemies.inicializar();

	// INICIALIZA A EXPLOSION ARRAY
	explosions.inicializar();

	// INICIALIZA A SCOREKEEPING
	score.inicializar();

	// ATRIBUTO: goBackPls
	goBackPls = false;
}

void TelaJogo::draw()
{
	executar();
	desenhar();
}

void TelaJogo::executar()
{
	// ATUALIZA O FRAMECOUNTER
	frameCounterJogo.tick();

	// AVANÇA A ANIMAÇÃO DO BACKGROUND
	gameBackground.avancarAnimacao();

	// VERIFICA SE QUER DISMISS O SCORE POPUP
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

				// notifica para voltar para o menu
				goBackPls = true;
			}
		}
	}

	// SE O PLAYER ESTÁ NA SUPERFÍCIE, DESLIGA OS SPAWNERS
	if (player.getSurfaceStatus())
	{
		// desliga os spawners
		divers.turnOffSpawner();
		airBubbles.turnOffSpawner();
		enemies.turnOffSpawner();

		if (gameStarted == true)
		{
			// MORTE POR SUBMERGÊNCIA
			mortePorSubmergencia();
		}
	}
	else
	{
		// liga os spawners
		divers.turnOnSpawner();
		airBubbles.turnOnSpawner();
		enemies.turnOnSpawner();

		gameStarted = true;
	}

	// RACIONALIZA SE DEVE COMER OXYGEN
	if (!player.getSurfaceStatus() && !(score.getFillStatus() == enumFrozen))
	{
		score.drainOxygen();
	}

	// RACIONALIZA SE MORREU POR ASFIXIA
	if (score.getOxygenLeft() < 0)
	{
		// MORTE POR ASFIXIA.
		if (gameStarted == true)
		{
			mortePorAsfixia();
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
	if (player.getShootStatus())
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
	for (int i = (enemies.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		if (enemies.getEnemyAtIndex(i).getShootStatus())
		{
			// cria o tiro
			Tiro tiro = Tiro();
			int tiroX = enemies.getEnemyAtIndex(i).getX();
			if (enemies.getEnemyAtIndex(i).getDirection() == facingLeft)
			{
				tiroX += 5;
			}
			else // facing right
			{
				tiroX -= 5;
			}

			tiro.inicializar(
				enemies.getEnemyAtIndex(i).getColor(),
				tiroX,
				enemies.getEnemyAtIndex(i).getY(),
				enemies.getEnemyAtIndex(i).getDirection()
			);
			tirosEnemy.adicionaTiroNaLista(tiro);

			// unset the wants-to-shoot flag
			Enemy test = Enemy();
			test = enemies.getEnemyAtIndex(i);
			test.makeNotWantToShoot();
			enemies.addEnemyAtIndex(test, i);

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
				airBubbles.spawnNewRandomAirBubble();
			}
		}
	}

	// SPAWNER: ENEMY
	if (frameCounterJogo.getFrameNumber() % 60 == 0) // 60 -> a cada 1 segundo
	{
		if (rand() % 2 == 0) // 2 -> uma chance em dois
		{
			if (enemies.isSpawnerTurnedOn()) // se o spawner está ligado
			{
				enemies.spawnNewRandomEnemy();
			}
		}
	}
	
	// COLLISION: PLAYER X DIVERS
	collisionPlayerDiver();
	// COLLISION: PLAYER X AIR BUBBLE
	collisionPlayerBubble();
	// COLLISION: PLAYER X ENEMY
	collisionPlayerEnemy();
	// COLLISION: PLAYER X ENEMY TIRO
	collisionPlayerEnemyTiro();
	// COLLISION: TIRO PLAYER X DIVERS
	collisionFriendlyTiroDiver();
	// COLLISION: TIRO PLAYER X ENEMY
	collisionFriendlyTiroEnemy();
	// COLLISION: TIRO ENEMY X DIVERS
	collisionEnemyTiroDiver();
	// COLLISION: TIRO ENEMY X ENEMY
	collisionEnemyTiroEnemy();
	// COLLISION: ENEMY X DIVER
	collisionEnemyDiver();
	// COLLISION: ENEMY X ENEMY
	collisionEnemyEnemy();
}

void TelaJogo::desenhar()
{
	// DESENHA O BACKGROUND
	gameBackground.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

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

	// DESENHA A ENEMY ARRAY
	enemies.atualizar();
	enemies.desenhar();

	// DESENHA O PLAYER
	player.atualizar();
	player.desenhar();

	// DESENHA A EXPLOSIONS ARRAY
	explosions.atualizar();
	explosions.desenhar();

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

void TelaJogo::mortePorSubmergencia()
{
	// dá play no som
	som.setAudio("sound_dead");
	som.tocar();

	// paralisa o jogo por enquanto
	gameStarted = false;

	// volta a chamar a popup
	popupNeedsDrawing = true;

	// limpa todos os elementos do oceano, bons ou maus
	clearAll();

	// desenha o score information
	score.setDeathBonus(true);
	score.startDisplayingResults();

	// troca o score overlay para o oxigênio
	score.setContentBarContext(barOxygen);
	scoreOverlay.setSpriteSheet("scoreOverlay");

	// remove uma vida
	score.removeALife();

	// reinicia o player
	player.inicializar();

	// congela o movimento do player por enquanto
	player.freeze();
}

void TelaJogo::mortePorAsfixia()
{
	// dá play no som
	som.setAudio("sound_dead");
	som.tocar();

	// paralisa o jogo por enquanto
	gameStarted = false;

	// volta a chamar a popup
	popupNeedsDrawing = true;

	// limpa todos os elementos do oceano, bons ou maus
	clearAll();

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

void TelaJogo::clearAll()
{
	enemies.clearEverything();
	tirosEnemy.clearEverything();
	tirosPlayer.clearEverything();
	divers.clearEverything();
	airBubbles.clearEverything();
}

void TelaJogo::clearAllThreats()
{
	// mata todos os inimigos em tela
	for (int i = (enemies.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		if (enemies.getEnemyAtIndex(i).getEnemyType() == enemyFish)
		{
			// adiciona o enemy fish ao score
			score.matouUmEnemyFishSemGrid();
		}
		else
		{
			// adiciona o enemy sub ao score
			score.matouUmEnemySubSemGrid();
		}

		// cria uma explosão		
		explosions.adicionaNovaExplosion(enemies.getEnemyAtIndex(i).getX(), enemies.getEnemyAtIndex(i).getY());

		// destrói o enemy
		enemies.removeEnemyAtIndex(i);
	}	

	// limpa a array de tiros inimigos
	tirosEnemy.clearEverything();

	// limpa a array de tiros meus
	tirosPlayer.clearEverythingButBlueFreezers();
}

void TelaJogo::collisionPlayerDiver()
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

void TelaJogo::collisionPlayerBubble()
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
			airBubbles.getAirBubbleAtIndex(i).destruir();
			airBubbles.removeAirBubbleAtIndex(i);
		}
	}
}

void TelaJogo::collisionPlayerEnemy()
{
	for (int i = (enemies.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		if (uniTestarColisao(
			enemies.getEnemyAtIndex(i).getSprite(),
			enemies.getEnemyAtIndex(i).getX(),
			enemies.getEnemyAtIndex(i).getY(),
			0,
			player.getSprite(),
			player.getX(),
			player.getY(),
			0
		))
		{
			// COLIDIU UM ENEMY COM O PLAYER!

			// remove um pouco de o2 do player
			if (score.getContentBarContext() == barOxygen)
			{
				score.reduceOxygenByAmount(600);
			}

			// dá play no som
			som.setAudio("sound_explosion");
			som.tocar();

			// cria uma explosão			
			explosions.adicionaNovaExplosion(enemies.getEnemyAtIndex(i).getX(), enemies.getEnemyAtIndex(i).getY());

			// destrói o enemy
			enemies.removeEnemyAtIndex(i);
		}
	}
}

void TelaJogo::collisionPlayerEnemyTiro()
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

			// cria uma explosão
			explosions.adicionaNovaExplosion(((player.getX() + tirosEnemy.getTiroAtIndex(i).getX()) / 2), tirosEnemy.getTiroAtIndex(i).getY());

			// destrói o enemy tiro
			tirosEnemy.getTiroAtIndex(i).destruir();
			tirosEnemy.removeTiroAtIndex(i);
		}
	}
}

void TelaJogo::collisionFriendlyTiroDiver()
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
				explosions.adicionaNovaExplosion(divers.getDiverAtIndex(i).getX(), divers.getDiverAtIndex(i).getY());

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}
}

void TelaJogo::collisionFriendlyTiroEnemy()
{
	for (int i = (enemies.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (tirosPlayer.getNumeroTotalUtilizado() - 1); j >= 0; j--)
		{
			if (uniTestarColisao(
				enemies.getEnemyAtIndex(i).getSprite(),
				enemies.getEnemyAtIndex(i).getX(),
				enemies.getEnemyAtIndex(i).getY(),
				0,
				tirosPlayer.getTiroAtIndex(j).getSprite(),
				tirosPlayer.getTiroAtIndex(j).getX(),
				tirosPlayer.getTiroAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM TIRO PLAYER COM UM ENEMY!

				// adiciona o enemy ao score e ao three grid
				if (tirosPlayer.getTiroAtIndex(j).getShotType() == shotBlue)
				{
					// se foi um Blue Freezer, adiciona ao score (mas não ao grid)
					if (enemies.getEnemyAtIndex(i).getEnemyType() == enemyFish)
					{
						score.matouUmEnemyFishSemGrid();
					}
					else
					{
						score.matouUmEnemySubSemGrid();
					}
				}
				else
				{
					// qualquer outro tiro adiciona ao score e também ao grid
					if (enemies.getEnemyAtIndex(i).getEnemyType() == enemyFish)
					{
						score.matouUmEnemyFish(enemies.getEnemyAtIndex(i).getColor());
					}
					else
					{
						score.matouUmEnemySub(enemies.getEnemyAtIndex(i).getColor());
					}					
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
				explosions.adicionaNovaExplosion(enemies.getEnemyAtIndex(i).getX(), enemies.getEnemyAtIndex(i).getY());

				// destrói o enemy
				enemies.removeEnemyAtIndex(i);
			}
		}
	}
}

void TelaJogo::collisionEnemyTiroDiver()
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
				explosions.adicionaNovaExplosion(divers.getDiverAtIndex(i).getX(), divers.getDiverAtIndex(i).getY());

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}
}

void TelaJogo::collisionEnemyTiroEnemy()
{
	for (int i = (enemies.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (tirosEnemy.getNumeroTotalUtilizado() - 1); j >= 0; j--)
		{
			if (uniTestarColisao(
				enemies.getEnemyAtIndex(i).getSprite(),
				enemies.getEnemyAtIndex(i).getX(),
				enemies.getEnemyAtIndex(i).getY(),
				0,
				tirosEnemy.getTiroAtIndex(j).getSprite(),
				tirosEnemy.getTiroAtIndex(j).getX(),
				tirosEnemy.getTiroAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM ENEMY TIRO COM UM ENEMY!

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
				explosions.adicionaNovaExplosion(enemies.getEnemyAtIndex(i).getX(), enemies.getEnemyAtIndex(i).getY());

				// destrói o enemy fish
				enemies.removeEnemyAtIndex(i);
			}
		}
	}
}

void TelaJogo::collisionEnemyDiver()
{
	for (int i = (divers.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (enemies.getNumeroTotalUtilizado() - 1); j >= 0; j--)
		{
			if (uniTestarColisao(
				divers.getDiverAtIndex(i).getSprite(),
				divers.getDiverAtIndex(i).getX(),
				divers.getDiverAtIndex(i).getY(),
				0,
				enemies.getEnemyAtIndex(j).getSprite(),
				enemies.getEnemyAtIndex(j).getX(),
				enemies.getEnemyAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM ENEMY COM UM DIVER!

				// dá play no som
				som.setAudio("sound_explosion");
				som.tocar();

				// cria uma explosão				
				explosions.adicionaNovaExplosion(divers.getDiverAtIndex(i).getX(), divers.getDiverAtIndex(i).getY());

				// destrói o diver
				divers.removeDiverAtIndex(i);
			}
		}
	}
}

void TelaJogo::collisionEnemyEnemy()
{
	for (int i = (enemies.getNumeroTotalUtilizado() - 1); i >= 0; i--)
	{
		for (int j = (enemies.getNumeroTotalUtilizado() - 1); j >= 0; j--)
		{
			if (uniTestarColisao(
				enemies.getEnemyAtIndex(i).getSprite(),
				enemies.getEnemyAtIndex(i).getX(),
				enemies.getEnemyAtIndex(i).getY(),
				0,
				enemies.getEnemyAtIndex(j).getSprite(),
				enemies.getEnemyAtIndex(j).getX(),
				enemies.getEnemyAtIndex(j).getY(),
				0
			))
			{
				// COLIDIU UM ENEMY COM UM ENEMY!
				// verificação necessária por motivos óbvios
				if (!(enemies.getEnemyAtIndex(i).verificaSemelhanca(enemies.getEnemyAtIndex(j))))
				{
					// cria uma explosão					
					explosions.adicionaNovaExplosion(enemies.getEnemyAtIndex(i).getX(), enemies.getEnemyAtIndex(i).getY());

					// destrói o enemy i
					enemies.removeEnemyAtIndex(i);

					// dá play no som
					som.setAudio("sound_explosion");
					som.tocar();

					// cria outra explosão					
					explosions.adicionaNovaExplosion(enemies.getEnemyAtIndex(j).getX(), enemies.getEnemyAtIndex(j).getY());

					// destrói o enemy fish j
					enemies.removeEnemyAtIndex(j);
				}
			}
		}
	}
}

void TelaJogo::comingIn()
{
	goBackPls = false;
}

bool TelaJogo::wantsToGoBack()
{
	return goBackPls;
}