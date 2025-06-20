#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"
#include "MovementComponent.h"
#include "RotatingMovingPointComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MovementCommand.h"
#include "LivesComponent.h"
#include "LivesTextComponent.h"
#include "LoseLiveCommand.h"
#include "Subject.h"
#include "ScoreComponent.h"
#include "ScoreTextComponent.h"
#include "GainPointsCommand.h"
#include "Achievements.h"
#include "SpriteSheetComponent.h"
#include "GridComponent.h"
#include "SpawnBombCommand.h"
#include "PlayerSpriteComponent.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include <iostream>
#include <LoggingSoundSystem.h>
#include <SDLSoundSystem.h>
#include "StartGameCommand.h"
#include "BaseColliderComponent.h"
#include "EnemyMovementComponent.h"
#include "PlayerCollider.h"
#include "Hash.h"
#include "GameManager.h"
#include "LoadingScreenComponent.h"
#include "Renderer.h"
#include "ButtonsComponent.h"
#include "ButtonsCommand.h"
#include "OnScreenKeyboardComponent.h"
#include "OnScreenKeyboardCommand.h"
#include "NameTextComponent.h"
#include "PressScreenKeyboardCommand.h"
#include "LevelLoader.h"
#include "SaveScoreReleaseCommand.h"
#include "SaveScoreHoldCommand.h"
#include "SaveScoreComponent.h"
#include "SpawnBombComponent.h"
#include "ExplodeBombCommand.h"
#include "HighScoresTextComponent.h"
#include "ReturnToStartCommand.h"
#include "EnemyMovementCommand.h"
#include "EnemyCollider.h"
#include "TimerLevelComponent.h"
#include "SkipLevelCommand.h"
#include "MuteSoundCommand.h"

void LoadPlayer(RamCoreEngine::Scene* scene, game::GridComponent* gridComp, int index, bool loadKeyboard)
{
	auto playerInputObject = std::make_unique<RamCoreEngine::GameObject>();
	playerInputObject->SetTag(make_sdbm_hash("Player"));

	auto playerInputSpriteSheet = std::make_unique<RamCoreEngine::SpriteSheetComponent>(playerInputObject.get(), "PlayerMove.png", 4, 4, 0.1f, false);
	auto playerInputSpriteSetter = std::make_unique<game::PlayerSpriteComponent>(playerInputObject.get(), 2.4f);
	auto playerInputCollider = std::make_unique<game::PlayerCollider>(playerInputObject.get(), 28.f, 28.f, true);
	auto playerInputSpawnBombComponent = std::make_unique<game::SpawnBombComponent>(playerInputObject.get(), 0.3f, 0.5f);

	gridComp->GetGridSubject()->AddObserver(playerInputSpawnBombComponent.get());

	//playerInputCollider->SetDebugRendering(true);
	playerInputObject->SetLocalPosition(glm::vec3(48, 112 + 32*index, 0.f)); //move one down if second player
	playerInputObject->AddComponent(std::move(playerInputSpriteSheet));
	playerInputObject->AddComponent(std::move(playerInputSpriteSetter));
	playerInputObject->AddComponent(std::move(playerInputCollider));
	playerInputObject->AddComponent(std::move(playerInputSpawnBombComponent));

	auto moveLeftCommand = std::make_unique<game::MoveCommand>(playerInputObject.get(), 0.2f);
	moveLeftCommand->SetSpeed({ -80.f, 0.f });
	auto moveRightCommand = std::make_unique<game::MoveCommand>(playerInputObject.get(), 0.2f);
	moveRightCommand->SetSpeed({ 80.f, 0.f });
	auto moveUpCommand = std::make_unique<game::MoveCommand>(playerInputObject.get(), 0.2f);
	moveUpCommand->SetSpeed({ 0.f, -80.f });
	auto moveDownCommand = std::make_unique<game::MoveCommand>(playerInputObject.get(), 0.2f);
	moveDownCommand->SetSpeed({ 0.f, 80.f });

	//auto loseLivesCommandKeyboard = std::make_unique<game::LoseLiveCommand>(playerInputObjectKeyboard.get());
	//auto gainSmallScoreCommandKeyboard = std::make_unique<game::GainPointsCommand>(playerInputObjectKeyboard.get());
	//gainSmallScoreCommandKeyboard->SetGainScore(10);
	//auto gainBigScoreCommandKeyboard = std::make_unique<game::GainPointsCommand>(playerInputObjectKeyboard.get());
	//gainBigScoreCommandKeyboard->SetGainScore(100);

	auto spawnBombCommand = std::make_unique<game::SpawnBombCommand>(playerInputObject.get());
	auto explodeBombCommand = std::make_unique<game::ExplodeBombCommand>(playerInputObject.get());

	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveLeftCommand), RamCoreEngine::KeyState::Pressed, 0x004, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveRightCommand), RamCoreEngine::KeyState::Pressed, 0x008, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveUpCommand), RamCoreEngine::KeyState::Pressed, 0x001, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveDownCommand), RamCoreEngine::KeyState::Pressed, 0x002, index);
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(loseLivesCommand), RamCoreEngine::KeyState::Up, SDLK_q, -1);
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommand), RamCoreEngine::KeyState::Up, SDLK_e, -1);
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommand), RamCoreEngine::KeyState::Up, SDLK_r, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(spawnBombCommand), RamCoreEngine::KeyState::Up, 0x8000, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(explodeBombCommand), RamCoreEngine::KeyState::Up, 0x4000, index);

	if (loadKeyboard) 
	{
		auto moveLeftCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObject.get(), 0.2f);
		moveLeftCommandKeyboard->SetSpeed({ -80.f, 0.f });
		auto moveRightCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObject.get(), 0.2f);
		moveRightCommandKeyboard->SetSpeed({ 80.f, 0.f });
		auto moveUpCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObject.get(), 0.2f);
		moveUpCommandKeyboard->SetSpeed({ 0.f, -80.f });
		auto moveDownCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObject.get(), 0.2f);
		moveDownCommandKeyboard->SetSpeed({ 0.f, 80.f });

		auto spawnBombCommandKeyboard = std::make_unique<game::SpawnBombCommand>(playerInputObject.get());
		auto explodeBombCommandKeyboard = std::make_unique<game::ExplodeBombCommand>(playerInputObject.get());

		auto skipLevelCommandKeyboard = std::make_unique<game::SkipLevelCommand>();

		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveLeftCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_a, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveRightCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_d, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveUpCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_w, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveDownCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_s, -1);
		//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(loseLivesCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_q, -1);
		//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_e, -1);
		//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_r, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(spawnBombCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_f, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(explodeBombCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_e, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(skipLevelCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_F1, -1);
	}

	scene->Add(std::move(playerInputObject));
}

void LoadPlayerAsEnemy(RamCoreEngine::Scene* scene, RamCoreEngine::GameObject* gridObject, game::ScoreTextComponent* playerScoreTextChange, int index)
{
	const std::vector<std::pair<glm::vec2, int>> enemies = game::LevelLoader::GetInstance().GetEnemies();

	auto enemy = std::make_unique<RamCoreEngine::GameObject>();
	enemy->SetTag(make_sdbm_hash("Enemy"));
	enemy->SetParent(gridObject, true);
	enemy->SetLocalPosition(glm::vec3(enemies[0].first.x, enemies[0].first.y, 0));
	auto enemyCollider = std::make_unique<game::EnemyCollider>(enemy.get(), 20.f, 20.f, true);
	enemy->AddComponent(std::move(enemyCollider));
	auto enemySprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemy.get(), "Balloom.png", 4, 3, 0.2f, false);
	auto enemyMovement = std::make_unique<game::EnemyMovementComponent>(enemy.get(), 75.f, 100, true);
	//enemyMovement->SetDebugRendering(true);
	enemyMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange);
	enemy->AddComponent(std::move(enemyMovement));
	enemy->AddComponent(std::move(enemySprite));

	auto moveLeftCommand = std::make_unique<game::EnemyMovementCommand>(enemy.get());
	moveLeftCommand->SetDirection({ -1.f, 0.f });
	auto moveRightCommand = std::make_unique<game::EnemyMovementCommand>(enemy.get());
	moveRightCommand->SetDirection({ 1.f, 0.f });
	auto moveUpCommand = std::make_unique<game::EnemyMovementCommand>(enemy.get());
	moveUpCommand->SetDirection({ 0.f, -1.f });
	auto moveDownCommand = std::make_unique<game::EnemyMovementCommand>(enemy.get());
	moveDownCommand->SetDirection({ 0.f, 1.f });

	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveLeftCommand), RamCoreEngine::KeyState::Pressed, 0x004, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveRightCommand), RamCoreEngine::KeyState::Pressed, 0x008, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveUpCommand), RamCoreEngine::KeyState::Pressed, 0x001, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveDownCommand), RamCoreEngine::KeyState::Pressed, 0x002, index);

	scene->Add(std::move(enemy));
	game::GameManager::GetInstance().SetAmountEnemies(1); //only one enemy in versus
}

void LoadStartScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();

	auto backgroundObject = std::make_unique<RamCoreEngine::GameObject>();
	backgroundObject->SetLocalPosition(glm::vec3(256, 238, 0.f));
	auto background = std::make_unique<RamCoreEngine::TextureComponent>(backgroundObject.get(), "background.tga");
	backgroundObject->AddComponent(std::move(background));
	scene->Add(std::move(backgroundObject));

	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
	//UI Buttons
	auto startButtonsObject = std::make_unique<RamCoreEngine::GameObject>();
	//startButtonsObject->SetLocalPosition(glm::vec3(256, 360, 0.f))
	auto buttonOne = std::make_unique<RamCoreEngine::TextComponent>(startButtonsObject.get(), "Start Game (Single Player)", font, true);
	buttonOne->SetCustomPosition(glm::vec2(256, 100));
	startButtonsObject->AddComponent(std::move(buttonOne));
	auto buttonTwo = std::make_unique<RamCoreEngine::TextComponent>(startButtonsObject.get(), "Start Game (Co-op)", font, true);
	buttonTwo->SetCustomPosition(glm::vec2(256, 150));
	startButtonsObject->AddComponent(std::move(buttonTwo));
	auto buttonThree = std::make_unique<RamCoreEngine::TextComponent>(startButtonsObject.get(), "Start Game (Versus)", font, true);
	buttonThree->SetCustomPosition(glm::vec2(256, 200));
	startButtonsObject->AddComponent(std::move(buttonThree));
	auto buttonFour = std::make_unique<RamCoreEngine::TextComponent>(startButtonsObject.get(), "Look at High Scores", font, true);
	buttonFour->SetCustomPosition(glm::vec2(256, 250));
	startButtonsObject->AddComponent(std::move(buttonFour));
	auto uiHandler = std::make_unique<game::ButtonsComponent>(startButtonsObject.get(), uint8_t(18), uint8_t(25), 0);
	startButtonsObject->AddComponent(std::move(uiHandler));

	auto logoObject = std::make_unique<RamCoreEngine::GameObject>();
	auto logo = std::make_unique<RamCoreEngine::TextureComponent>(logoObject.get(), "logo.tga");
	logoObject->SetLocalPosition(glm::vec3(256, 50, 0));
	logoObject->AddComponent(std::move(logo));

	scene->Add(std::move(logoObject));

	//auto playerStartButtonObjectKeyboard = std::make_unique<RamCoreEngine::GameObject>();
	//auto startGameCommandKeyboard = std::make_unique<game::StartGameCommand>(playerStartButtonObjectKeyboard.get());

	//auto playerStartButtonObjectGamepad = std::make_unique<RamCoreEngine::GameObject>();
	//auto startGameCommandGamepad = std::make_unique<game::StartGameCommand>(playerStartButtonObjectGamepad.get());

	//
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(startGameCommandGamepad), RamCoreEngine::KeyState::Up, 0x8000, 0); 
	

	//scene->Add(std::move(playerStartButtonObjectKeyboard));
	//scene->Add(std::move(playerStartButtonObjectGamepad));

	//KEYBOARD
	auto moveDownKeyboard = std::make_unique<game::ButtonsCommand>(startButtonsObject.get());
	moveDownKeyboard->SetGoesDown(true);

	auto moveUpKeyboard = std::make_unique<game::ButtonsCommand>(startButtonsObject.get());
	moveUpKeyboard->SetGoesDown(false);

	auto startGameCommandKeyboard = std::make_unique<game::StartGameCommand>(startButtonsObject.get());

	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveDownKeyboard), RamCoreEngine::KeyState::Up, SDLK_s, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveUpKeyboard), RamCoreEngine::KeyState::Up, SDLK_w, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(startGameCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_f, -1);

	auto muteCommand = std::make_unique<game::MuteSoundCommand>();
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(muteCommand), RamCoreEngine::KeyState::Up, SDLK_F2, -1);

	//GAMEPAD
	auto moveDownGamepad = std::make_unique<game::ButtonsCommand>(startButtonsObject.get());
	moveDownGamepad->SetGoesDown(true);

	auto moveUpGamepad = std::make_unique<game::ButtonsCommand>(startButtonsObject.get());
	moveUpGamepad->SetGoesDown(false);

	auto startGameCommandGamepad = std::make_unique<game::StartGameCommand>(startButtonsObject.get());

	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveDownGamepad), RamCoreEngine::KeyState::Up, 0x0002, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveUpGamepad), RamCoreEngine::KeyState::Up, 0x0001, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(startGameCommandGamepad), RamCoreEngine::KeyState::Up, 0x8000, 0);

	scene->Add(std::move(startButtonsObject));

	// --------TUTORIAL TEXT----------
	auto tutorialControls = std::make_unique<RamCoreEngine::GameObject>();
	tutorialControls->SetLocalPosition(glm::vec3(256, 360, 0.f));
	auto tutorialText = std::make_unique<RamCoreEngine::TextComponent>(tutorialControls.get(), "Controls", font);
	tutorialControls->AddComponent(std::move(tutorialText));
	scene->Add(std::move(tutorialControls));

	auto tutorialObjectGamepad = std::make_unique<RamCoreEngine::GameObject>();
	tutorialObjectGamepad->SetLocalPosition(glm::vec3(256, 400, 0.f));
	auto tutorialTextGamepad = std::make_unique<RamCoreEngine::TextComponent>(tutorialObjectGamepad.get(), "Use D-Pad to move, Y to place bomb, X to remote explode bomb", font);
	tutorialTextGamepad->ChangeFontSize(17);
	tutorialObjectGamepad->AddComponent(std::move(tutorialTextGamepad));
	scene->Add(std::move(tutorialObjectGamepad));

	auto tutorialObjectKeyboard = std::make_unique<RamCoreEngine::GameObject>();
	tutorialObjectKeyboard->SetLocalPosition(glm::vec3(256, 420, 0.f));
	auto tutorialTextKeyboard = std::make_unique<RamCoreEngine::TextComponent>(tutorialObjectKeyboard.get(), "Use WASD to move, F to place bomb, E to remote explode bomb", font);
	tutorialTextKeyboard->ChangeFontSize(17);
	tutorialObjectKeyboard->AddComponent(std::move(tutorialTextKeyboard));
	scene->Add(std::move(tutorialObjectKeyboard));

	auto tutorialNotes = std::make_unique<RamCoreEngine::GameObject>();
	tutorialNotes->SetLocalPosition(glm::vec3(256, 450, 0.f));
	auto tutorialNotesText = std::make_unique<RamCoreEngine::TextComponent>(tutorialNotes.get(), "WASD/D-pad to control UI, F/Y to confirm button", font);
	tutorialNotesText->ChangeFontSize(18);
	tutorialNotes->AddComponent(std::move(tutorialNotesText));
	scene->Add(std::move(tutorialNotes));

	RamCoreEngine::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/TitleScreen.mp3", 30, -1);//30 volume
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("MoveUI"), "../Data/Sound/MoveVertical.mp3");
	game::GameManager::GetInstance().ResetStats(); //every time going to menu stops game so need to reset
	RamCoreEngine::ServiceLocator::GetSoundSystem().LoadAllSound();
}

void LoadGameScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();
	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto fpsObject = std::make_unique<RamCoreEngine::GameObject>();
	auto fpsText = std::make_unique<RamCoreEngine::TextComponent>(fpsObject.get(), "FPS:", font);
	fpsObject->SetLocalPosition(glm::vec3(150, 32, 0.f));
	fpsObject->AddComponent(std::move(fpsText));
	auto fpsCounter = std::make_unique<game::FpsComponent>(fpsObject.get());
	fpsObject->AddComponent(std::move(fpsCounter));
	scene->Add(std::move(fpsObject));

	auto timerLevelObject = std::make_unique<RamCoreEngine::GameObject>();
	timerLevelObject->SetLocalPosition(glm::vec3(60, 32, 0.f));
	auto timerText = std::make_unique<RamCoreEngine::TextComponent>(timerLevelObject.get(), "Time ", font);
	auto timerCounter = std::make_unique<game::TimerLevelComponent>(timerLevelObject.get(), 200.f, 10);
	timerLevelObject->AddComponent(std::move(timerText));
	timerLevelObject->AddComponent(std::move(timerCounter));
	scene->Add(std::move(timerLevelObject));

	//Input
	auto gridObject = std::make_unique<RamCoreEngine::GameObject>();
	gridObject->SetTag(make_sdbm_hash("Grid"));
	gridObject->SetLocalPosition(glm::vec3(0, 0, 0.f));
	auto gridView = std::make_unique<game::GridComponent>(gridObject.get(), 31, 13, 992, 476, 32.f, 64.f, 512);
	
	auto playerLivesTextObject = std::make_unique<RamCoreEngine::GameObject>();
	playerLivesTextObject->SetLocalPosition(glm::vec3(420, 30, 0.f));
	std::string lives = "Lives: " + std::to_string(game::GameManager::GetInstance().GetTotalLives());
	auto playerLivesText = std::make_unique<RamCoreEngine::TextComponent>(playerLivesTextObject.get(), lives, font);
	playerLivesText->ChangeFontSize(28);
	playerLivesTextObject->AddComponent(std::move(playerLivesText));
	scene->Add(std::move(playerLivesTextObject));

	//display score
	auto playerScoreTextObject = std::make_unique<RamCoreEngine::GameObject>();
	playerScoreTextObject->SetTag(make_sdbm_hash("ScoreText"));
	playerScoreTextObject->SetLocalPosition(glm::vec3(300, 30, 0.f));
	std::string score = std::to_string(game::GameManager::GetInstance().GetTotalScore());
	auto playerScoreText = std::make_unique<RamCoreEngine::TextComponent>(playerScoreTextObject.get(), score, font);
	playerScoreText->ChangeFontSize(28);
	playerScoreTextObject->AddComponent(std::move(playerScoreText));
	auto playerScoreTextChange = std::make_unique<game::ScoreTextComponent>(playerScoreTextObject.get());

	LoadPlayer(scene, gridView.get(), 0, true);

	bool spawnEnemies{ true };
	switch (game::GameManager::GetInstance().GetGameMode())
	{
	case game::GameMode::Single:

		break;
	case game::GameMode::Coop:
		LoadPlayer(scene, gridView.get(), 1, false);
		break;
	case game::GameMode::Versus:
		spawnEnemies = false;
		LoadPlayerAsEnemy(scene, gridObject.get(), playerScoreTextChange.get(), 1);
		break;
	}

	if (spawnEnemies)
	{
		// --------ENEMIES----------
		const std::vector<std::pair<glm::vec2, int>> enemies = game::LevelLoader::GetInstance().GetEnemies();
		game::GameManager::GetInstance().SetAmountEnemies(static_cast<int>(enemies.size()));

		for (size_t enemyCounter{}; enemyCounter < enemies.size(); ++enemyCounter)
		{
			glm::vec2 enemyPos = enemies[enemyCounter].first;
			auto enemy = std::make_unique<RamCoreEngine::GameObject>();
			enemy->SetTag(make_sdbm_hash("Enemy"));
			enemy->SetLocalPosition(glm::vec3(enemyPos.x, enemyPos.y, 0));
			enemy->SetParent(gridObject.get(), true);
			auto enemyCollider = std::make_unique<game::EnemyCollider>(enemy.get(), 25.f, 25.f, true);
			enemy->AddComponent(std::move(enemyCollider));

			int enemyType = enemies[enemyCounter].second;
			if (enemyType == 0)
			{
				auto enemyMovement = std::make_unique<game::EnemyMovementComponent>(enemy.get(), 50.f, 100, false);
				//enemyMovement->SetDebugRendering(true);
				enemyMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange.get());

				auto enemySprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemy.get(), "Balloom.png", 4, 3, 0.2f, false);
				enemy->AddComponent(std::move(enemyMovement));
				enemy->AddComponent(std::move(enemySprite));
			}

			else if (enemyType == 1)
			{
				auto enemyMovement = std::make_unique<game::EnemyMovementComponent>(enemy.get(), 60.f, 200, false, true, 100.f);
				//enemyMovement->SetDebugRendering(true);
				enemyMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange.get());

				auto enemySprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemy.get(), "Oneal.png", 4, 3, 0.2f, false);
				enemy->AddComponent(std::move(enemyMovement));
				enemy->AddComponent(std::move(enemySprite));
			}

			else if (enemyType == 2)
			{
				auto enemyMovement = std::make_unique<game::EnemyMovementComponent>(enemy.get(), 60.f, 400, false);
				//enemyMovement->SetDebugRendering(true);
				enemyMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange.get());

				auto enemySprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemy.get(), "Doll.png", 4, 3, 0.2f, false);
				enemy->AddComponent(std::move(enemyMovement));
				enemy->AddComponent(std::move(enemySprite));
			}
			else if (enemyType == 3)
			{
				auto enemyMovement = std::make_unique<game::EnemyMovementComponent>(enemy.get(), 100.f, 800, false, true, 100.f);
				//enemyMovement->SetDebugRendering(true);
				enemyMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange.get());

				auto enemySprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemy.get(), "Minvo.png", 4, 3, 0.2f, false);
				enemy->AddComponent(std::move(enemyMovement));
				enemy->AddComponent(std::move(enemySprite));
			}
			scene->Add(std::move(enemy));
		}
	}

	gridObject->AddComponent(std::move(gridView));
	playerScoreTextObject->AddComponent(std::move(playerScoreTextChange)); // moves after observer is set

	scene->Add(std::move(gridObject));
	scene->Add(std::move(playerScoreTextObject));

	SDL_Color color = { 56, 135, 0, 255 };
	RamCoreEngine::Renderer::GetInstance().SetBackgroundColor(color);

	// --------SOUND----------
	RamCoreEngine::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainBGM.mp3", 50, -1); //50 volume
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("ExplodeBombSFX"), "../Data/Sound/BombExplodes.wav");
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("MoveHor"), "../Data/Sound/MoveHorizontal.mp3");
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("MoveVer"), "../Data/Sound/MoveVertical.mp3");
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("KilledLastEnemy"), "../Data/Sound/KilledLastEnemy.mp3");
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("CollectedPU"), "../Data/Sound/PowerUp.mp3");
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("PlacedBomb"), "../Data/Sound/PlaceBomb.mp3");
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("Dying"), "../Data/Sound/Dying.mp3");
	RamCoreEngine::ServiceLocator::GetSoundSystem().LoadAllSound();

	auto muteCommand = std::make_unique<game::MuteSoundCommand>();
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(muteCommand), RamCoreEngine::KeyState::Up, SDLK_F2, -1);

}

void LoadLoadingScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();

	std::string levelRead = "../Data/Levels/Level" + std::to_string(game::GameManager::GetInstance().GetCurrentLevel()) + ".txt";
	game::LevelLoader::GetInstance().ReadFile(levelRead); //gonna load the level here, doesnt need to be done when level starts

	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	auto levelTextObject = std::make_unique<RamCoreEngine::GameObject>();
	levelTextObject->SetLocalPosition(glm::vec3(256, 238, 0.f));
	std::string level = "Stage " + std::to_string(game::GameManager::GetInstance().GetCurrentLevel());
	auto levelText = std::make_unique<RamCoreEngine::TextComponent>(levelTextObject.get(), level, font);
	levelText->ChangeFontSize(50);
	levelTextObject->AddComponent(std::move(levelText));
	auto loadScreen = std::make_unique<game::LoadingScreenComponent>(levelTextObject.get(), 2.6f);
	levelTextObject->AddComponent(std::move(loadScreen));

	scene->Add(std::move(levelTextObject));

	SDL_Color color = { 0, 0, 0, 255 };
	RamCoreEngine::Renderer::GetInstance().SetBackgroundColor(color);
	RamCoreEngine::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/StageStart.mp3", 50, -1); //50 volume

	auto muteCommand = std::make_unique<game::MuteSoundCommand>();
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(muteCommand), RamCoreEngine::KeyState::Up, SDLK_F2, -1);

	RamCoreEngine::ServiceLocator::GetSoundSystem().LoadAllSound();
}

void LoadEndScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();
	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 50);

	auto playerScoreTextObject = std::make_unique<RamCoreEngine::GameObject>();
	playerScoreTextObject->SetLocalPosition(glm::vec3(256, 50, 0.f));
	std::string score = "Your score: " + std::to_string(game::GameManager::GetInstance().GetTotalScore());
	auto playerScoreText = std::make_unique<RamCoreEngine::TextComponent>(playerScoreTextObject.get(), score, font);
	playerScoreText->ChangeFontSize(30);
	playerScoreTextObject->AddComponent(std::move(playerScoreText));
	auto playerScoreTextChange = std::make_unique<game::ScoreTextComponent>(playerScoreTextObject.get());
	scene->Add(std::move(playerScoreTextObject));

	auto onScreenKeyboardObject = std::make_unique<RamCoreEngine::GameObject>();
	onScreenKeyboardObject->SetLocalPosition(glm::vec3(256, 238, 0));
	auto nameTextComp = std::make_unique<RamCoreEngine::TextComponent>(onScreenKeyboardObject.get(), " ", font, true);
	nameTextComp->SetCustomPosition(glm::vec2(0, -120));
	auto nameTextChangeComp = std::make_unique<game::NameTextComponent>(onScreenKeyboardObject.get());
	auto onScreenKeyboardComp = std::make_unique<game::OnScreenKeyboardComponent>(onScreenKeyboardObject.get(), 13, 2, 20, 40, uint8_t(30), uint8_t(40));
	onScreenKeyboardComp->GetNameChangedEventSubject()->AddObserver(nameTextChangeComp.get());
	onScreenKeyboardObject->AddComponent(std::move(nameTextComp));
	onScreenKeyboardObject->AddComponent(std::move(nameTextChangeComp));
	onScreenKeyboardObject->AddComponent(std::move(onScreenKeyboardComp));

	auto saveBarObject = std::make_unique<RamCoreEngine::GameObject>();
	saveBarObject->SetLocalPosition(glm::vec3(256, 350, 0));
	auto saveBar = std::make_unique<game::SaveScoreComponent>(saveBarObject.get(), 100.f, 20.f, 50.f, "../Data/HighScores/highScores.txt");
	saveBarObject->AddComponent(std::move(saveBar));
	

	//------------KEYBOARD------------
	auto keyboardLeft = std::make_unique<game::OnScreenKeyboardCommand>(onScreenKeyboardObject.get());
	keyboardLeft->SetDirection(glm::vec2(-1, 0));
	auto keyboardRight = std::make_unique<game::OnScreenKeyboardCommand>(onScreenKeyboardObject.get());
	keyboardRight->SetDirection(glm::vec2(1, 0));
	auto keyboardUp = std::make_unique<game::OnScreenKeyboardCommand>(onScreenKeyboardObject.get());
	keyboardUp->SetDirection(glm::vec2(0, -1));
	auto keyboardDown = std::make_unique<game::OnScreenKeyboardCommand>(onScreenKeyboardObject.get());
	keyboardDown->SetDirection(glm::vec2(0, 1));

	auto keyboardClickAdd = std::make_unique<game::PressScreenKeyboardCommand>(onScreenKeyboardObject.get());
	auto keyboardClickRemove = std::make_unique<game::PressScreenKeyboardCommand>(onScreenKeyboardObject.get());
	keyboardClickRemove->SetShouldRemove(true);

	auto keyboardHoldSave = std::make_unique<game::SaveScoreHoldCommand>(saveBarObject.get());
	auto keyboardReleaseSave = std::make_unique<game::SaveScoreReleaseCommand>(saveBarObject.get());

	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(keyboardLeft), RamCoreEngine::KeyState::Up, SDLK_a, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(keyboardRight), RamCoreEngine::KeyState::Up, SDLK_d, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(keyboardUp), RamCoreEngine::KeyState::Up, SDLK_w, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(keyboardDown), RamCoreEngine::KeyState::Up, SDLK_s, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(keyboardClickAdd), RamCoreEngine::KeyState::Up, SDLK_e, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(keyboardClickRemove), RamCoreEngine::KeyState::Up, SDLK_q, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(keyboardHoldSave), RamCoreEngine::KeyState::Pressed, SDLK_f, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(keyboardReleaseSave), RamCoreEngine::KeyState::Up, SDLK_f, -1);

	//------------GAMEPAD------------
	auto gamepadLeft = std::make_unique<game::OnScreenKeyboardCommand>(onScreenKeyboardObject.get());
	gamepadLeft->SetDirection(glm::vec2(-1, 0));
	auto gamepadRight = std::make_unique<game::OnScreenKeyboardCommand>(onScreenKeyboardObject.get());
	gamepadRight->SetDirection(glm::vec2(1, 0));
	auto gamepadUp = std::make_unique<game::OnScreenKeyboardCommand>(onScreenKeyboardObject.get());
	gamepadUp->SetDirection(glm::vec2(0, -1));
	auto gamepadDown = std::make_unique<game::OnScreenKeyboardCommand>(onScreenKeyboardObject.get());
	gamepadDown->SetDirection(glm::vec2(0, 1));

	auto gamepadClickAdd = std::make_unique<game::PressScreenKeyboardCommand>(onScreenKeyboardObject.get());
	auto gamepadClickRemove = std::make_unique<game::PressScreenKeyboardCommand>(onScreenKeyboardObject.get());
	gamepadClickRemove->SetShouldRemove(true);

	auto gamepadHoldSave = std::make_unique<game::SaveScoreHoldCommand>(saveBarObject.get());
	auto gamepadReleaseSave = std::make_unique<game::SaveScoreReleaseCommand>(saveBarObject.get());

	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gamepadLeft), RamCoreEngine::KeyState::Up, 0x0004, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gamepadRight), RamCoreEngine::KeyState::Up, 0x0008, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gamepadUp), RamCoreEngine::KeyState::Up, 0x0001, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gamepadDown), RamCoreEngine::KeyState::Up, 0x0002, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gamepadClickAdd), RamCoreEngine::KeyState::Up, 0x8000, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gamepadClickRemove), RamCoreEngine::KeyState::Up, 0x2000, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gamepadHoldSave), RamCoreEngine::KeyState::Pressed, 0x4000, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gamepadReleaseSave), RamCoreEngine::KeyState::Up, 0x4000, 0);

	scene->Add(std::move(onScreenKeyboardObject));
	scene->Add(std::move(saveBarObject));

	auto controlObject = std::make_unique<RamCoreEngine::GameObject>();
	controlObject->SetLocalPosition(glm::vec3(256, 400, 0.f));
	auto controlsText = std::make_unique<RamCoreEngine::TextComponent>(controlObject.get(), "WASD/D-pad to control UI, Hold F/X to confirm", font);
	controlsText->ChangeFontSize(18);
	controlObject->AddComponent(std::move(controlsText));
	scene->Add(std::move(controlObject));

	auto addRemoveObject = std::make_unique<RamCoreEngine::GameObject>();
	addRemoveObject->SetLocalPosition(glm::vec3(256, 430, 0.f));
	auto addRemoveText = std::make_unique<RamCoreEngine::TextComponent>(addRemoveObject.get(), "Press E/Y to add letter, Press Q/B to remove letter", font);
	addRemoveText->ChangeFontSize(18);
	addRemoveObject->AddComponent(std::move(addRemoveText));
	scene->Add(std::move(addRemoveObject));

	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("MoveUI"), "../Data/Sound/MoveVertical.mp3");
	RamCoreEngine::ServiceLocator::GetSoundSystem().LoadAllSound();
	
}

void LoadHighScoreScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();
	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto backgroundObject = std::make_unique<RamCoreEngine::GameObject>();
	backgroundObject->SetLocalPosition(glm::vec3(256, 238, 0.f));
	auto background = std::make_unique<RamCoreEngine::TextureComponent>(backgroundObject.get(), "background.tga");
	backgroundObject->AddComponent(std::move(background));
	scene->Add(std::move(backgroundObject));

	auto highScores = std::make_unique<RamCoreEngine::GameObject>();
	highScores->SetLocalPosition(glm::vec3(256, 150, 0.f));
	auto highScoresText = std::make_unique<game::HighScoresTextComponent>(highScores.get(), "../Data/HighScores/highScores.txt", 50.f);
	highScores->AddComponent(std::move(highScoresText));

	scene->Add(std::move(highScores));

	auto returnToStartKeyboard = std::make_unique<game::ReturnToStartCommand>();
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(returnToStartKeyboard), RamCoreEngine::KeyState::Up, SDLK_e, -1);

	auto returnToStartGamepad = std::make_unique<game::ReturnToStartCommand>();
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(returnToStartGamepad), RamCoreEngine::KeyState::Up, 0x8000, 0);

	auto tutorialNotes = std::make_unique<RamCoreEngine::GameObject>();
	tutorialNotes->SetLocalPosition(glm::vec3(256, 450, 0.f));
	auto tutorialNotesText = std::make_unique<RamCoreEngine::TextComponent>(tutorialNotes.get(), "Press E on keyboard or Y on gamepad to return to start", font);
	tutorialNotesText->ChangeFontSize(18);
	tutorialNotes->AddComponent(std::move(tutorialNotesText));
	scene->Add(std::move(tutorialNotes));
}

void load()
{
	game::GameManager::GetInstance().SetMaxLives(3);
	
	auto& sceneStart = RamCoreEngine::SceneManager::GetInstance().CreateScene(make_sdbm_hash("Start"), true);
	sceneStart.SetLoadingFunction(LoadStartScene);
	auto& sceneLoading = RamCoreEngine::SceneManager::GetInstance().CreateScene(make_sdbm_hash("LoadingScreen"), false);
	sceneLoading.SetLoadingFunction(LoadLoadingScene);
	auto& sceneGame = RamCoreEngine::SceneManager::GetInstance().CreateScene(make_sdbm_hash("Level"), false);
	sceneGame.SetLoadingFunction(LoadGameScene);
	auto& sceneEnd = RamCoreEngine::SceneManager::GetInstance().CreateScene(make_sdbm_hash("EndScreen"), false);
	sceneEnd.SetLoadingFunction(LoadEndScene);
	auto& sceneHighScore = RamCoreEngine::SceneManager::GetInstance().CreateScene(make_sdbm_hash("HighScoreScreen"), false);
	sceneHighScore.SetLoadingFunction(LoadHighScoreScene);

	// ------------ SOUND --------------
#if _DEBUG

	RamCoreEngine::ServiceLocator::RegisterSoundSystem(std::make_unique<RamCoreEngine::LoggingSoundSystem>(std::make_unique<RamCoreEngine::SDLSoundSystem>()));
#else
	RamCoreEngine::ServiceLocator::RegisterSoundSystem(std::make_unique<RamCoreEngine::SDLSoundSystem>());
#endif
}

int main(int, char* [])
{
	RamCoreEngine::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}

