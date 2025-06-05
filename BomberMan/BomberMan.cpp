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

void LoadPlayerGamePad(RamCoreEngine::Scene* scene, int index)
{
	// --------GAMEPAD-----------
	auto playerInputObjectGamepad = std::make_unique<RamCoreEngine::GameObject>();
	playerInputObjectGamepad->SetTag(make_sdbm_hash("Player"));
	auto playerInputGamepadSpriteSheet = std::make_unique<RamCoreEngine::SpriteSheetComponent>(playerInputObjectGamepad.get(), "PlayerMove.png", 4, 4, 0.2f, false);
	auto playerInputGamepadSpriteSetter = std::make_unique<game::PlayerSpriteComponent>(playerInputObjectGamepad.get());
	auto playerInputGamepadCollider = std::make_unique<game::PlayerCollider>(playerInputObjectGamepad.get(), 28.f, 28.f, true);
	playerInputObjectGamepad->SetLocalPosition(glm::vec3(48, 144, 0.f));
	playerInputObjectGamepad->AddComponent(std::move(playerInputGamepadSpriteSheet));
	playerInputObjectGamepad->AddComponent(std::move(playerInputGamepadSpriteSetter));
	playerInputObjectGamepad->AddComponent(std::move(playerInputGamepadCollider));

	//lives
	/*auto playerLivesKeyboard = std::make_unique<game::LivesComponent>(playerInputObjectGamepad.get(), 3);
	playerLivesKeyboard->GetActorDiedSubject()->AddObserver(playerLivesTextChange);
	playerInputObjectGamepad->AddComponent(std::move(playerLivesKeyboard));*/

	// ------- INPUT GAMEPAD ---------

	auto moveLeftCommand = std::make_unique<game::MoveCommand>(playerInputObjectGamepad.get());
	moveLeftCommand->SetSpeed({ -50.f, 0.f });
	auto moveRightCommand = std::make_unique<game::MoveCommand>(playerInputObjectGamepad.get());
	moveRightCommand->SetSpeed({ 50.f, 0.f });
	auto moveUpCommand = std::make_unique<game::MoveCommand>(playerInputObjectGamepad.get());
	moveUpCommand->SetSpeed({ 0.f, -50.f });
	auto moveDownCommand = std::make_unique<game::MoveCommand>(playerInputObjectGamepad.get());
	moveDownCommand->SetSpeed({ 0.f, 50.f });



	//auto loseLivesCommandGamepad = std::make_unique<game::LoseLiveCommand>(playerInputObjectGamepad.get());
	//auto gainSmallScoreCommandGamepad = std::make_unique<game::GainPointsCommand>(playerInputObjectGamepad.get());
	//gainSmallScoreCommandGamepad->SetGainScore(10);
	//auto gainBigScoreCommandGamepad = std::make_unique<game::GainPointsCommand>(playerInputObjectGamepad.get());
	//gainBigScoreCommandGamepad->SetGainScore(100);

	auto spawnBombCommandGamepad = std::make_unique<game::SpawnBombCommand>(playerInputObjectGamepad.get());

	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveLeftCommand), RamCoreEngine::KeyState::Pressed, 0x004, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveRightCommand), RamCoreEngine::KeyState::Pressed, 0x008, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveUpCommand), RamCoreEngine::KeyState::Pressed, 0x001, index);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveDownCommand), RamCoreEngine::KeyState::Pressed, 0x002, index);
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(loseLivesCommandGamepad), RamCoreEngine::KeyState::Up, 0x1000, 0);
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommandGamepad), RamCoreEngine::KeyState::Up, 0x2000, 0);
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommandGamepad), RamCoreEngine::KeyState::Up, 0x4000, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(spawnBombCommandGamepad), RamCoreEngine::KeyState::Up, 0x8000, index);

	scene->Add(std::move(playerInputObjectGamepad));
	// --------END GAMEPAD-----------
}

void LoadPlayer(RamCoreEngine::Scene* scene, game::GridComponent* gridComp, int index)
{
	//display lives
	//auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//display Player
	//auto playerKeyboardTextObject = std::make_unique<RamCoreEngine::GameObject>();
	//playerKeyboardTextObject->SetLocalPosition(50, 275);
	//auto playerTextKeyboard = std::make_unique<RamCoreEngine::TextComponent>(playerKeyboardTextObject.get(), "Player Two:", font);
	//playerTextKeyboard->ChangeFontSize(20);
	//playerKeyboardTextObject->AddComponent(std::move(playerTextKeyboard));
	//scene->Add(std::move(playerKeyboardTextObject));


	auto playerInputObject = std::make_unique<RamCoreEngine::GameObject>();
	playerInputObject->SetTag(make_sdbm_hash("Player"));

	auto playerInputSpriteSheet = std::make_unique<RamCoreEngine::SpriteSheetComponent>(playerInputObject.get(), "PlayerMove.png", 4, 4, 0.2f, false);
	auto playerInputSpriteSetter = std::make_unique<game::PlayerSpriteComponent>(playerInputObject.get());
	auto playerInputCollider = std::make_unique<game::PlayerCollider>(playerInputObject.get(), 28.f, 28.f, true);
	auto playerInputSpawnBombComponent = std::make_unique<game::SpawnBombComponent>(playerInputObject.get());

	gridComp->GetGridSubject()->AddObserver(playerInputSpawnBombComponent.get());

	playerInputCollider->SetDebugRendering(true);
	playerInputObject->SetLocalPosition(glm::vec3(48, 112 + 32*index, 0.f)); //move one down if second player
	playerInputObject->AddComponent(std::move(playerInputSpriteSheet));
	playerInputObject->AddComponent(std::move(playerInputSpriteSetter));
	playerInputObject->AddComponent(std::move(playerInputCollider));
	playerInputObject->AddComponent(std::move(playerInputSpawnBombComponent));

	//lives
	//auto playerLivesKeyboard = std::make_unique<game::LivesComponent>(playerInputObjectKeyboard.get(), 3);
	//playerLivesKeyboard->GetActorDiedSubject()->AddObserver(playerLivesTextChange);
	//playerInputObjectKeyboard->AddComponent(std::move(playerLivesKeyboard));


	auto moveLeftCommand = std::make_unique<game::MoveCommand>(playerInputObject.get());
	moveLeftCommand->SetSpeed({ -100.f, 0.f });
	auto moveRightCommand = std::make_unique<game::MoveCommand>(playerInputObject.get());
	moveRightCommand->SetSpeed({ 100.f, 0.f });
	auto moveUpCommand = std::make_unique<game::MoveCommand>(playerInputObject.get());
	moveUpCommand->SetSpeed({ 0.f, -100.f });
	auto moveDownCommand = std::make_unique<game::MoveCommand>(playerInputObject.get());
	moveDownCommand->SetSpeed({ 0.f, 100.f });

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

	if (index == 0) // if first controller, also set it for keyboard
	{
		auto moveLeftCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObject.get());
		moveLeftCommandKeyboard->SetSpeed({ -100.f, 0.f });
		auto moveRightCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObject.get());
		moveRightCommandKeyboard->SetSpeed({ 100.f, 0.f });
		auto moveUpCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObject.get());
		moveUpCommandKeyboard->SetSpeed({ 0.f, -100.f });
		auto moveDownCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObject.get());
		moveDownCommandKeyboard->SetSpeed({ 0.f, 100.f });

		auto spawnBombCommandKeyboard = std::make_unique<game::SpawnBombCommand>(playerInputObject.get());
		auto explodeBombCommandKeyboard = std::make_unique<game::ExplodeBombCommand>(playerInputObject.get());

		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveLeftCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_a, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveRightCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_d, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveUpCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_w, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveDownCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_s, -1);
		//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(loseLivesCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_q, -1);
		//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_e, -1);
		//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_r, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(spawnBombCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_f, -1);
		RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(explodeBombCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_e, -1);
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
	auto enemyCollider = std::make_unique<RamCoreEngine::BaseColliderComponent>(enemy.get(), 25.f, 25.f, false);
	enemy->AddComponent(std::move(enemyCollider));
	auto enemySprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemy.get(), "Balloom.png", 4, 3, 0.2f, false);
	auto enemyMovement = std::make_unique<game::EnemyMovementComponent>(enemy.get(), 15.f, 100, true);
	enemyMovement->SetDebugRendering(true);
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

	//auto startButtonTextObject = std::make_unique<RamCoreEngine::GameObject>();
	//startButtonTextObject->SetLocalPosition(glm::vec3(500, 275, 0.f));
	//auto startButtonText = std::make_unique<RamCoreEngine::TextComponent>(startButtonTextObject.get(), "Press E on keyboard or ??? (gamepad start not working yet) on gamepad to start game", font);
	//startButtonText->ChangeFontSize(20);
	//startButtonTextObject->AddComponent(std::move(startButtonText));
	//scene->Add(std::move(startButtonTextObject));
	
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
	std::vector<std::string> scenesToLoad{}; //TODO: make hash maps
	scenesToLoad.emplace_back("LoadingScreen"); //for this maybe set enum in game manager??
	scenesToLoad.emplace_back("LoadingScreen"); //for this maybe set enum in game manager??
	scenesToLoad.emplace_back("LoadingScreen"); //for this maybe set enum in game manager??
	scenesToLoad.emplace_back("HighScoreScreen"); //for this maybe set enum in game manager??
	auto uiHandler = std::make_unique<game::ButtonsComponent>(startButtonsObject.get(), uint8_t(18), uint8_t(25), 0, scenesToLoad);
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
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(startGameCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_e, -1);

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
	auto tutorialTextGamepad = std::make_unique<RamCoreEngine::TextComponent>(tutorialObjectGamepad.get(), "Use D-Pad to move, Y to place bomb, kill Balloom to get score", font);
	tutorialTextGamepad->ChangeFontSize(15);
	tutorialObjectGamepad->AddComponent(std::move(tutorialTextGamepad));
	scene->Add(std::move(tutorialObjectGamepad));

	auto tutorialObjectKeyboard = std::make_unique<RamCoreEngine::GameObject>();
	tutorialObjectKeyboard->SetLocalPosition(glm::vec3(256, 420, 0.f));
	auto tutorialTextKeyboard = std::make_unique<RamCoreEngine::TextComponent>(tutorialObjectKeyboard.get(), "Use WASD to move, F to place bomb, kill Balloom to get score", font);
	tutorialTextKeyboard->ChangeFontSize(15);
	tutorialObjectKeyboard->AddComponent(std::move(tutorialTextKeyboard));
	scene->Add(std::move(tutorialObjectKeyboard));

	auto tutorialNotes = std::make_unique<RamCoreEngine::GameObject>();
	tutorialNotes->SetLocalPosition(glm::vec3(256, 450, 0.f));
	auto tutorialNotesText = std::make_unique<RamCoreEngine::TextComponent>(tutorialNotes.get(), "only keyboard player can get killed by balloom for now", font);
	tutorialNotesText->ChangeFontSize(20);
	tutorialNotes->AddComponent(std::move(tutorialNotesText));
	scene->Add(std::move(tutorialNotes));

	RamCoreEngine::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/TitleScreen.mp3", 0, -1);//30 volume
	game::GameManager::GetInstance().ResetStats(); //every time going to menu stops game so need to reset
}

void LoadGameScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();

	
	//auto backgroundObject = std::make_unique<RamCoreEngine::GameObject>();
	//auto background = std::make_unique<RamCoreEngine::TextureComponent>(backgroundObject.get(), "background.tga");
	//backgroundObject->SetLocalPosition(0, 0);
	//backgroundObject->AddComponent(std::move(background));
	//
	//scene->Add(std::move(backgroundObject));

	//auto logoObject = std::make_unique<RamCoreEngine::GameObject>();
	//auto logo = std::make_unique<RamCoreEngine::TextureComponent>(logoObject.get(), "logo.tga");
	//logoObject->SetLocalPosition(216, 180);
	//logoObject->AddComponent(std::move(logo));
	//
	//scene->Add(std::move(logoObject));
	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//auto assignmentTextObject = std::make_unique<RamCoreEngine::GameObject>();
	//
	//auto assignmentText = std::make_unique<RamCoreEngine::TextComponent>(assignmentTextObject.get(), "Programming 4 Assignment", font);
	//assignmentTextObject->SetLocalPosition(80, 50);
	//assignmentTextObject->AddComponent(std::move(assignmentText));
	//scene->Add(std::move(assignmentTextObject));

	auto fpsObject = std::make_unique<RamCoreEngine::GameObject>();
	auto fpsText = std::make_unique<RamCoreEngine::TextComponent>(fpsObject.get(), "FPS:", font);
	fpsObject->SetLocalPosition(glm::vec3(40, 32, 0.f));
	fpsObject->AddComponent(std::move(fpsText));

	auto fpsCounter = std::make_unique<game::FpsComponent>(fpsObject.get());
	fpsObject->AddComponent(std::move(fpsCounter));

	//auto fpsMovement = std::make_unique<game::MovementComponent>();
	//fpsMovement->SetSpeed(5.f, 0.f);
	//auto fpsRotPos = glm::vec3{ 216, 180, 0 };
	//fpsMovement->SetRotationSpeed(1.f, fpsRotPos);
	//fpsObject->AddComponent(std::move(fpsMovement));

	scene->Add(std::move(fpsObject));


	//PLAYER SINGLE SPRITE
	// auto playerObject = std::make_unique<RamCoreEngine::GameObject>();
	// auto player = std::make_unique<RamCoreEngine::TextureComponent>(playerObject.get(), "Bomberman.png");
	// playerObject->SetLocalPosition(120, 300);
	// playerObject->AddComponent(std::move(player));
	// 
	// auto playerMovement = std::make_unique<game::MovementComponent>(playerObject.get());
	// //playerMovement->SetSpeed(20.f, 0.f);
	// playerMovement->SetRotation(3.f, 170, 300);
	// playerObject->AddComponent(std::move(playerMovement));
	// 
	// 
	// 
	// //PLAYER ROTATION AROUND OTHER PLAYER
	// auto secondPlayerObject = std::make_unique<RamCoreEngine::GameObject>();
	// secondPlayerObject->SetParent(playerObject.get(), false);
	// auto secondPlayer = std::make_unique<RamCoreEngine::TextureComponent>(secondPlayerObject.get(), "Bomberman.png");
	// secondPlayerObject->SetLocalPosition(100, 300);
	// glm::vec3 secondPlayerLocPos = { 40, 0, 0 };
	// secondPlayerObject->SetLocalPosition(secondPlayerLocPos);
	// secondPlayerObject->AddComponent(std::move(secondPlayer));
	// 
	// auto secondPlayerMovement = std::make_unique<game::MovementComponent>(secondPlayerObject.get());
	// secondPlayerMovement->SetRotation(-50.f, playerObject->GetWorldPosition().x, playerObject->GetWorldPosition().y);
	// secondPlayerObject->AddComponent(std::move(secondPlayerMovement));
	// 
	// auto secondPlayerRotatePoint = std::make_unique<game::RotatingMovingPointComponent>(secondPlayerObject.get());
	// secondPlayerObject->AddComponent(std::move(secondPlayerRotatePoint));
	// 
	// 
	// 
	// scene->Add(std::move(playerObject));
	// scene->Add(std::move(secondPlayerObject));

	//auto trashCashObject = std::make_unique<RamCoreEngine::GameObject>();
	//auto trashCash = std::make_unique<game::TrashCashComponent>(trashCashObject.get());
	//trashCashObject->AddComponent(std::move(trashCash));
	//scene->Add(std::move(trashCashObject));

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
	//auto playerLivesTextChange = std::make_unique<game::LivesTextComponent>(playerLivesTextObject.get());
	//playerLivesTextObject->AddComponent(std::move(playerLivesTextChange)); // moves after observer is set
	scene->Add(std::move(playerLivesTextObject));

	//display score
	auto playerScoreTextObject = std::make_unique<RamCoreEngine::GameObject>();
	playerScoreTextObject->SetLocalPosition(glm::vec3(230, 30, 0.f));
	std::string score = "Current score: " + std::to_string(game::GameManager::GetInstance().GetTotalScore());
	auto playerScoreText = std::make_unique<RamCoreEngine::TextComponent>(playerScoreTextObject.get(), score, font);
	playerScoreText->ChangeFontSize(28);
	playerScoreTextObject->AddComponent(std::move(playerScoreText));
	auto playerScoreTextChange = std::make_unique<game::ScoreTextComponent>(playerScoreTextObject.get());

	//LoadPlayerGamePad(scene, 0);
	LoadPlayer(scene, gridView.get(), 0);
	//LoadEnemies(scene, gridObject.get(), playerKeyboardCollider);

	bool spawnEnemies{ true };
	switch (game::GameManager::GetInstance().GetGameMode())
	{
	case game::GameMode::Single:

		break;
	case game::GameMode::Coop:
		LoadPlayer(scene, gridView.get(), 1);
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
		game::GameManager::GetInstance().SetAmountEnemies(int(enemies.size()));

		for (size_t enemyCounter{}; enemyCounter < enemies.size(); ++enemyCounter)
		{
			glm::vec2 enemyPos = enemies[enemyCounter].first;
			auto enemy = std::make_unique<RamCoreEngine::GameObject>();
			enemy->SetTag(make_sdbm_hash("Enemy"));
			enemy->SetParent(gridObject.get(), true);
			enemy->SetLocalPosition(glm::vec3(enemyPos.x, enemyPos.y, 0));
			auto enemyCollider = std::make_unique<RamCoreEngine::BaseColliderComponent>(enemy.get(), 25.f, 25.f, false);
			enemy->AddComponent(std::move(enemyCollider));

			int enemyType = enemies[enemyCounter].second;
			if (enemyType == 0)
			{
				auto enemyMovement = std::make_unique<game::EnemyMovementComponent>(enemy.get(), 15.f, 100, false);
				enemyMovement->SetDebugRendering(true);
				enemyMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange.get());

				auto enemySprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemy.get(), "Balloom.png", 4, 3, 0.2f, false);
				enemy->AddComponent(std::move(enemyMovement));
				enemy->AddComponent(std::move(enemySprite));
			}

			else if (enemyType == 1)
			{
				auto enemyMovement = std::make_unique<game::EnemyMovementComponent>(enemy.get(), 10.f, 200, false, true, 100.f);
				enemyMovement->SetDebugRendering(true);
				enemyMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange.get());

				auto enemySprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemy.get(), "Oneal.png", 4, 3, 0.2f, false);
				enemy->AddComponent(std::move(enemyMovement));
				enemy->AddComponent(std::move(enemySprite));
			}

			scene->Add(std::move(enemy));
		}
	}
	


	/*auto enemyBalloomOne = std::make_unique<RamCoreEngine::GameObject>();
	enemyBalloomOne->SetTag(make_sdbm_hash("Enemy"));
	enemyBalloomOne->SetParent(gridObject.get(), true);
	enemyBalloomOne->SetLocalPosition(glm::vec3(48, 304, 0));
	auto enemyBalloomOneMovement = std::make_unique<game::EnemyMovementComponent>(enemyBalloomOne.get(), 15.f, 100);
	enemyBalloomOneMovement->SetDebugRendering(true);
	enemyBalloomOneMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange.get());
	auto enemyBalloomOneCollider = std::make_unique<RamCoreEngine::BaseColliderComponent>(enemyBalloomOne.get(), 25.f, 25.f, false);
	auto enemyBalloomOneSprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemyBalloomOne.get(), "Balloom.png", 4, 3, 0.2f, false);
	
	enemyBalloomOne->AddComponent(std::move(enemyBalloomOneMovement));
	enemyBalloomOne->AddComponent(std::move(enemyBalloomOneCollider));
	enemyBalloomOne->AddComponent(std::move(enemyBalloomOneSprite));
	
	scene->Add(std::move(enemyBalloomOne));


	auto enemyOnealOne = std::make_unique<RamCoreEngine::GameObject>();
	enemyOnealOne->SetTag(make_sdbm_hash("Enemy"));
	enemyOnealOne->SetParent(gridObject.get(), true);
	enemyOnealOne->SetLocalPosition(glm::vec3(48, 336, 0));
	auto enemyOnealOneMovement = std::make_unique<game::EnemyMovementComponent>(enemyOnealOne.get(), 10.f, 200, true, 100.f);
	enemyOnealOneMovement->SetDebugRendering(true);
	enemyOnealOneMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange.get());
	auto enemyOnealOneCollider = std::make_unique<RamCoreEngine::BaseColliderComponent>(enemyOnealOne.get(), 25.f, 25.f, false);
	auto enemyOnealOneSprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemyOnealOne.get(), "Oneal.png", 4, 3, 0.2f, false);

	enemyOnealOne->AddComponent(std::move(enemyOnealOneMovement));
	enemyOnealOne->AddComponent(std::move(enemyOnealOneCollider));
	enemyOnealOne->AddComponent(std::move(enemyOnealOneSprite));

	scene->Add(std::move(enemyOnealOne));*/

	gridObject->AddComponent(std::move(gridView));
	playerScoreTextObject->AddComponent(std::move(playerScoreTextChange)); // moves after observer is set

	scene->Add(std::move(gridObject));
	scene->Add(std::move(playerScoreTextObject));

	SDL_Color color = { 56, 135, 0, 255 };
	RamCoreEngine::Renderer::GetInstance().SetBackgroundColor(color);

	// --------SOUND----------
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("ExplodeBombSFX"), "../Data/Sound/BombExplodes.wav");
	RamCoreEngine::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainBGM.mp3", 0, -1); //50 volume
}

void LoadLoadingScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();

	std::string levelRead = "../Data/Levels/Level" + std::to_string(game::GameManager::GetInstance().GetCurrentLevel()) + ".txt";
	game::LevelLoader::GetInstance().ReadFile(levelRead); //gonna load the level here, doesnt need to be done when level starts

	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	auto levelTextObject = std::make_unique<RamCoreEngine::GameObject>();
	levelTextObject->SetLocalPosition(glm::vec3(256, 238, 0.f));
	std::string level = "Level: " + std::to_string(game::GameManager::GetInstance().GetCurrentLevel());
	auto levelText = std::make_unique<RamCoreEngine::TextComponent>(levelTextObject.get(), level, font);
	levelText->ChangeFontSize(50);
	levelTextObject->AddComponent(std::move(levelText));
	auto loadScreen = std::make_unique<game::LoadingScreenComponent>(levelTextObject.get(), 3.f);
	levelTextObject->AddComponent(std::move(loadScreen));

	scene->Add(std::move(levelTextObject));

	SDL_Color color = { 0, 0, 0, 255 };
	RamCoreEngine::Renderer::GetInstance().SetBackgroundColor(color);
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
	saveBarObject->SetLocalPosition(glm::vec3(256, 400, 0));
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
	
}

void LoadHighScoreScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();

	auto backgroundObject = std::make_unique<RamCoreEngine::GameObject>();
	backgroundObject->SetLocalPosition(glm::vec3(256, 238, 0.f));
	auto background = std::make_unique<RamCoreEngine::TextureComponent>(backgroundObject.get(), "background.tga");
	backgroundObject->AddComponent(std::move(background));
	scene->Add(std::move(backgroundObject));

	auto highScores = std::make_unique<RamCoreEngine::GameObject>();
	highScores->SetLocalPosition(glm::vec3(256, 100, 0.f));
	auto highScoresText = std::make_unique<game::HighScoresTextComponent>(highScores.get(), "../Data/HighScores/highScores.txt", 50.f);
	highScores->AddComponent(std::move(highScoresText));

	scene->Add(std::move(highScores));

	auto returnToStartKeyboard = std::make_unique<game::ReturnToStartCommand>();
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(returnToStartKeyboard), RamCoreEngine::KeyState::Up, SDLK_e, -1);

	auto returnToStartGamepad = std::make_unique<game::ReturnToStartCommand>();
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(returnToStartGamepad), RamCoreEngine::KeyState::Up, 0x8000, 0);
}

void load()
{
	game::GameManager::GetInstance().SetMaxLives(3);

	auto& sceneStart = RamCoreEngine::SceneManager::GetInstance().CreateScene("Start", true);
	sceneStart.SetLoadingFunction(LoadStartScene);
	auto& sceneLoading = RamCoreEngine::SceneManager::GetInstance().CreateScene("LoadingScreen", false);
	sceneLoading.SetLoadingFunction(LoadLoadingScene);
	auto& sceneGame = RamCoreEngine::SceneManager::GetInstance().CreateScene("Level", false);
	sceneGame.SetLoadingFunction(LoadGameScene);
	auto& sceneEnd = RamCoreEngine::SceneManager::GetInstance().CreateScene("EndScreen", false);
	sceneEnd.SetLoadingFunction(LoadEndScene);
	auto& sceneHighScore = RamCoreEngine::SceneManager::GetInstance().CreateScene("HighScoreScreen", false);
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

