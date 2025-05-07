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

void LoadPlayerGamePad(RamCoreEngine::Scene* scene)
{
	// --------GAMEPAD-----------
	auto playerInputObjectGamepad = std::make_unique<RamCoreEngine::GameObject>();
	playerInputObjectGamepad->SetTag(make_sdbm_hash("Player"));
	auto playerInputGamepadSpriteSheet = std::make_unique<RamCoreEngine::SpriteSheetComponent>(playerInputObjectGamepad.get(), "PlayerMove.png", 4, 4, 0.2f, false);
	auto playerInputGamepadSpriteSetter = std::make_unique<game::PlayerSpriteComponent>(playerInputObjectGamepad.get());
	auto playerInputGamepadCollider = std::make_unique<game::PlayerCollider>(playerInputObjectGamepad.get(), 28.f, 28.f, true);
	playerInputObjectGamepad->SetWorldPosition(48, 144);
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

	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveLeftCommand), RamCoreEngine::KeyState::Pressed, 0x004, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveRightCommand), RamCoreEngine::KeyState::Pressed, 0x008, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveUpCommand), RamCoreEngine::KeyState::Pressed, 0x001, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveDownCommand), RamCoreEngine::KeyState::Pressed, 0x002, 0);
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(loseLivesCommandGamepad), RamCoreEngine::KeyState::Up, 0x1000, 0);
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommandGamepad), RamCoreEngine::KeyState::Up, 0x2000, 0);
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommandGamepad), RamCoreEngine::KeyState::Up, 0x4000, 0);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(spawnBombCommandGamepad), RamCoreEngine::KeyState::Up, 0x8000, 0);

	scene->Add(std::move(playerInputObjectGamepad));
	// --------END GAMEPAD-----------
}

void LoadPlayerKeyboard(RamCoreEngine::Scene* scene)
{
	// --------KEYBOARD-----------
	//display lives
	//auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//display Player
	//auto playerKeyboardTextObject = std::make_unique<RamCoreEngine::GameObject>();
	//playerKeyboardTextObject->SetWorldPosition(50, 275);
	//auto playerTextKeyboard = std::make_unique<RamCoreEngine::TextComponent>(playerKeyboardTextObject.get(), "Player Two:", font);
	//playerTextKeyboard->ChangeFontSize(20);
	//playerKeyboardTextObject->AddComponent(std::move(playerTextKeyboard));
	//scene->Add(std::move(playerKeyboardTextObject));



	// ------- INPUT KEYBOARD ---------

	auto playerInputObjectKeyboard = std::make_unique<RamCoreEngine::GameObject>();
	playerInputObjectKeyboard->SetTag(make_sdbm_hash("Player"));

	auto playerInputKeyboardSpriteSheet = std::make_unique<RamCoreEngine::SpriteSheetComponent>(playerInputObjectKeyboard.get(), "PlayerMove.png", 4, 4, 0.2f, false);
	auto playerInputKeyboardSpriteSetter = std::make_unique<game::PlayerSpriteComponent>(playerInputObjectKeyboard.get());
	auto playerInputKeyboardCollider = std::make_unique<game::PlayerCollider>(playerInputObjectKeyboard.get(), 28.f, 28.f, true);
	playerInputKeyboardCollider->SetDebugRendering(true);
	playerInputObjectKeyboard->SetWorldPosition(48, 112);
	playerInputObjectKeyboard->AddComponent(std::move(playerInputKeyboardSpriteSheet));
	playerInputObjectKeyboard->AddComponent(std::move(playerInputKeyboardSpriteSetter));
	playerInputObjectKeyboard->AddComponent(std::move(playerInputKeyboardCollider));

	//lives
	//auto playerLivesKeyboard = std::make_unique<game::LivesComponent>(playerInputObjectKeyboard.get(), 3);
	//playerLivesKeyboard->GetActorDiedSubject()->AddObserver(playerLivesTextChange);
	//playerInputObjectKeyboard->AddComponent(std::move(playerLivesKeyboard));


	auto moveLeftCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObjectKeyboard.get());
	moveLeftCommandKeyboard->SetSpeed({ -50.f, 0.f });
	auto moveRightCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObjectKeyboard.get());
	moveRightCommandKeyboard->SetSpeed({ 50.f, 0.f });
	auto moveUpCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObjectKeyboard.get());
	moveUpCommandKeyboard->SetSpeed({ 0.f, -50.f });
	auto moveDownCommandKeyboard = std::make_unique<game::MoveCommand>(playerInputObjectKeyboard.get());
	moveDownCommandKeyboard->SetSpeed({ 0.f, 50.f });

	auto loseLivesCommandKeyboard = std::make_unique<game::LoseLiveCommand>(playerInputObjectKeyboard.get());
	auto gainSmallScoreCommandKeyboard = std::make_unique<game::GainPointsCommand>(playerInputObjectKeyboard.get());
	gainSmallScoreCommandKeyboard->SetGainScore(10);
	auto gainBigScoreCommandKeyboard = std::make_unique<game::GainPointsCommand>(playerInputObjectKeyboard.get());
	gainBigScoreCommandKeyboard->SetGainScore(100);

	auto spawnBombCommandKeyboard = std::make_unique<game::SpawnBombCommand>(playerInputObjectKeyboard.get());

	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveLeftCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_a, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveRightCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_d, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveUpCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_w, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(moveDownCommandKeyboard), RamCoreEngine::KeyState::Pressed, SDLK_s, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(loseLivesCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_q, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_e, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_r, -1);
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(spawnBombCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_f, -1);

	scene->Add(std::move(playerInputObjectKeyboard));

	// --------END KEYBOARD-----------

	
}


void LoadStartScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();

	auto backgroundObject = std::make_unique<RamCoreEngine::GameObject>();
	backgroundObject->SetWorldPosition(100, 300);
	auto background = std::make_unique<RamCoreEngine::TextureComponent>(backgroundObject.get(), "background.tga");
	auto backgroundTwo = std::make_unique<RamCoreEngine::TextureComponent>(backgroundObject.get(), "background.tga", true);
	backgroundTwo->SetCustomPosition(glm::vec2(740, 300));
	backgroundObject->AddComponent(std::move(background));
	backgroundObject->AddComponent(std::move(backgroundTwo));
	scene->Add(std::move(backgroundObject));

	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto startButtonTextObject = std::make_unique<RamCoreEngine::GameObject>();
	startButtonTextObject->SetWorldPosition(500, 275);
	auto startButtonText = std::make_unique<RamCoreEngine::TextComponent>(startButtonTextObject.get(), "Press E on keyboard or ??? (gamepad start not working yet) on gamepad to start game", font);
	startButtonText->ChangeFontSize(20);
	startButtonTextObject->AddComponent(std::move(startButtonText));
	scene->Add(std::move(startButtonTextObject));

	auto logoObject = std::make_unique<RamCoreEngine::GameObject>();
	auto logo = std::make_unique<RamCoreEngine::TextureComponent>(logoObject.get(), "logo.tga");
	logoObject->SetWorldPosition(500, 180);
	logoObject->AddComponent(std::move(logo));

	scene->Add(std::move(logoObject));

	auto playerStartButtonObjectKeyboard = std::make_unique<RamCoreEngine::GameObject>();
	auto startGameCommandKeyboard = std::make_unique<game::StartGameCommand>(playerStartButtonObjectKeyboard.get());

	auto playerStartButtonObjectGamepad = std::make_unique<RamCoreEngine::GameObject>();
	auto startGameCommandGamepad = std::make_unique<game::StartGameCommand>(playerStartButtonObjectGamepad.get());

	
	//RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(startGameCommandGamepad), RamCoreEngine::KeyState::Up, 0x8000, 0); //TODO: Issues with input that keeps going after game start
	RamCoreEngine::InputManager::GetInstance().AddBinding(std::move(startGameCommandKeyboard), RamCoreEngine::KeyState::Up, SDLK_e, -1);

	scene->Add(std::move(playerStartButtonObjectKeyboard));
	scene->Add(std::move(playerStartButtonObjectGamepad));

	// --------TUTORIAL TEXT----------
	auto tutorialControls = std::make_unique<RamCoreEngine::GameObject>();
	tutorialControls->SetWorldPosition(500, 360);
	auto tutorialText = std::make_unique<RamCoreEngine::TextComponent>(tutorialControls.get(), "Controls", font);
	tutorialControls->AddComponent(std::move(tutorialText));
	scene->Add(std::move(tutorialControls));

	auto tutorialObjectGamepad = std::make_unique<RamCoreEngine::GameObject>();
	tutorialObjectGamepad->SetWorldPosition(500, 400);
	auto tutorialTextGamepad = std::make_unique<RamCoreEngine::TextComponent>(tutorialObjectGamepad.get(), "Use D-Pad to move, Y to place bomb, kill Balloom to get score", font);
	tutorialTextGamepad->ChangeFontSize(15);
	tutorialObjectGamepad->AddComponent(std::move(tutorialTextGamepad));
	scene->Add(std::move(tutorialObjectGamepad));

	auto tutorialObjectKeyboard = std::make_unique<RamCoreEngine::GameObject>();
	tutorialObjectKeyboard->SetWorldPosition(500, 420);
	auto tutorialTextKeyboard = std::make_unique<RamCoreEngine::TextComponent>(tutorialObjectKeyboard.get(), "Use WASD to move, F to place bomb, kill Balloom to get score", font);
	tutorialTextKeyboard->ChangeFontSize(15);
	tutorialObjectKeyboard->AddComponent(std::move(tutorialTextKeyboard));
	scene->Add(std::move(tutorialObjectKeyboard));

	auto tutorialNotes = std::make_unique<RamCoreEngine::GameObject>();
	tutorialNotes->SetWorldPosition(500, 450);
	auto tutorialNotesText = std::make_unique<RamCoreEngine::TextComponent>(tutorialNotes.get(), "only keyboard player can get killed by balloom for now", font);
	tutorialNotesText->ChangeFontSize(20);
	tutorialNotes->AddComponent(std::move(tutorialNotesText));
	scene->Add(std::move(tutorialNotes));

	RamCoreEngine::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/TitleScreen.mp3", 30, -1);//50 volume
}

void LoadGameScene()
{
	auto scene = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene();

	//auto backgroundObject = std::make_unique<RamCoreEngine::GameObject>();
	//auto background = std::make_unique<RamCoreEngine::TextureComponent>(backgroundObject.get(), "background.tga");
	//backgroundObject->SetWorldPosition(0, 0);
	//backgroundObject->AddComponent(std::move(background));
	//
	//scene->Add(std::move(backgroundObject));

	//auto logoObject = std::make_unique<RamCoreEngine::GameObject>();
	//auto logo = std::make_unique<RamCoreEngine::TextureComponent>(logoObject.get(), "logo.tga");
	//logoObject->SetWorldPosition(216, 180);
	//logoObject->AddComponent(std::move(logo));
	//
	//scene->Add(std::move(logoObject));
	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	//auto assignmentTextObject = std::make_unique<RamCoreEngine::GameObject>();
	//
	//auto assignmentText = std::make_unique<RamCoreEngine::TextComponent>(assignmentTextObject.get(), "Programming 4 Assignment", font);
	//assignmentTextObject->SetWorldPosition(80, 50);
	//assignmentTextObject->AddComponent(std::move(assignmentText));
	//scene->Add(std::move(assignmentTextObject));

	auto fpsObject = std::make_unique<RamCoreEngine::GameObject>();
	auto fpsText = std::make_unique<RamCoreEngine::TextComponent>(fpsObject.get(), "FPS:", font);
	fpsObject->SetWorldPosition(80, 32);
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
	// playerObject->SetWorldPosition(120, 300);
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
	// secondPlayerObject->SetWorldPosition(100, 300);
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
	gridObject->SetWorldPosition(0, 0);
	auto gridView = std::make_unique<game::GridComponent>(gridObject.get(), 31, 13, 992, 476, 32.f, 64.f);
	gridObject->AddComponent(std::move(gridView));

	auto playerLivesTextObject = std::make_unique<RamCoreEngine::GameObject>();
	playerLivesTextObject->SetWorldPosition(700, 30);
	std::string lives = "Lives: " + std::to_string(game::GameManager::GetInstance().GetTotalLives());
	auto playerLivesText = std::make_unique<RamCoreEngine::TextComponent>(playerLivesTextObject.get(), lives, font);
	//playerLivesText->ChangeFontSize(18);
	playerLivesTextObject->AddComponent(std::move(playerLivesText));
	//auto playerLivesTextChange = std::make_unique<game::LivesTextComponent>(playerLivesTextObject.get());
	//playerLivesTextObject->AddComponent(std::move(playerLivesTextChange)); // moves after observer is set
	scene->Add(std::move(playerLivesTextObject));

	//display score
	auto playerScoreTextObject = std::make_unique<RamCoreEngine::GameObject>();
	playerScoreTextObject->SetWorldPosition(500, 32);
	std::string score = "Current score: " + std::to_string(game::GameManager::GetInstance().GetTotalScore());
	auto playerScoreText = std::make_unique<RamCoreEngine::TextComponent>(playerScoreTextObject.get(), score, font);
	playerScoreText->ChangeFontSize(32);
	playerScoreTextObject->AddComponent(std::move(playerScoreText));
	auto playerScoreTextChange = std::make_unique<game::ScoreTextComponent>(playerScoreTextObject.get());

	//please do smth about not passing a lot of pointers in functions
	LoadPlayerGamePad(scene);
	LoadPlayerKeyboard(scene);
	//LoadEnemies(scene, gridObject.get(), playerKeyboardCollider);

	// --------ENEMIES----------
	auto enemyBalloomOne = std::make_unique<RamCoreEngine::GameObject>();
	enemyBalloomOne->SetTag(make_sdbm_hash("Enemy"));
	enemyBalloomOne->SetWorldPosition(48, 304);
	enemyBalloomOne->SetParent(gridObject.get(), true);
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
	enemyOnealOne->SetWorldPosition(48, 336);
	enemyOnealOne->SetParent(gridObject.get(), true);
	auto enemyOnealOneMovement = std::make_unique<game::EnemyMovementComponent>(enemyOnealOne.get(), 15.f, 200, true, 100.f);
	enemyOnealOneMovement->SetDebugRendering(true);
	enemyOnealOneMovement->GetEnemyDiedSubject()->AddObserver(playerScoreTextChange.get());
	auto enemyOnealOneCollider = std::make_unique<RamCoreEngine::BaseColliderComponent>(enemyOnealOne.get(), 25.f, 25.f, false);
	auto enemyOnealOneSprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemyOnealOne.get(), "Oneal.png", 4, 3, 0.2f, false);

	enemyOnealOne->AddComponent(std::move(enemyOnealOneMovement));
	enemyOnealOne->AddComponent(std::move(enemyOnealOneCollider));
	enemyOnealOne->AddComponent(std::move(enemyOnealOneSprite));

	scene->Add(std::move(enemyOnealOne));

	
	playerScoreTextObject->AddComponent(std::move(playerScoreTextChange)); // moves after observer is set

	scene->Add(std::move(gridObject));
	
	scene->Add(std::move(playerScoreTextObject));

	// --------SOUND----------
	RamCoreEngine::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("ExplodeBombSFX"), "../Data/Sound/BombExplodes.wav");
	RamCoreEngine::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainBGM.mp3", 0, -1); //50 volume
}

void load()
{
	// ------------ FileReading (TODO: IMPLEMENT) --------------
	game::GameManager::GetInstance().SetLives(3);


	
	//auto& sceneStart = RamCoreEngine::SceneManager::GetInstance().CreateScene("Start", true);
	//sceneStart.SetLoadingFunction(LoadStartScene);
	auto& sceneGame = RamCoreEngine::SceneManager::GetInstance().CreateScene("Game", true);
	sceneGame.SetLoadingFunction(LoadGameScene);

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

