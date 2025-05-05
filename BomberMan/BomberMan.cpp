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

void LoadPlayerGamePad(dae::Scene* scene, dae::GameObject* levelParent, dae::LivesTextComponent* playerLivesTextChange)
{
	// --------GAMEPAD-----------
	auto playerInputObjectGamepad = std::make_unique<dae::GameObject>();
	playerInputObjectGamepad->SetTag(make_sdbm_hash("Player"));
	playerInputObjectGamepad->SetParent(levelParent, true);
	auto playerInputGamepadSpriteSheet = std::make_unique<dae::SpriteSheetComponent>(playerInputObjectGamepad.get(), "PlayerMove.png", 4, 4, 0.2f, false);
	auto playerInputGamepadSpriteSetter = std::make_unique<dae::PlayerSpriteComponent>(playerInputObjectGamepad.get());
	auto playerInputGamepadCollider = std::make_unique<dae::PlayerCollider>(playerInputObjectGamepad.get(), 28.f, 28.f, true);
	playerInputObjectGamepad->SetWorldPosition(48, 144);
	playerInputObjectGamepad->AddComponent(std::move(playerInputGamepadSpriteSheet));
	playerInputObjectGamepad->AddComponent(std::move(playerInputGamepadSpriteSetter));
	playerInputObjectGamepad->AddComponent(std::move(playerInputGamepadCollider));

	//lives
	auto playerLivesKeyboard = std::make_unique<dae::LivesComponent>(playerInputObjectGamepad.get(), 3);
	playerLivesKeyboard->GetActorDiedSubject()->AddObserver(playerLivesTextChange);
	playerInputObjectGamepad->AddComponent(std::move(playerLivesKeyboard));

	// ------- INPUT GAMEPAD ---------

	auto moveLeftCommand = std::make_unique<dae::MoveCommand>(playerInputObjectGamepad.get());
	moveLeftCommand->SetSpeed({ -50.f, 0.f });
	auto moveRightCommand = std::make_unique<dae::MoveCommand>(playerInputObjectGamepad.get());
	moveRightCommand->SetSpeed({ 50.f, 0.f });
	auto moveUpCommand = std::make_unique<dae::MoveCommand>(playerInputObjectGamepad.get());
	moveUpCommand->SetSpeed({ 0.f, -50.f });
	auto moveDownCommand = std::make_unique<dae::MoveCommand>(playerInputObjectGamepad.get());
	moveDownCommand->SetSpeed({ 0.f, 50.f });



	//auto loseLivesCommandGamepad = std::make_unique<dae::LoseLiveCommand>(playerInputObjectGamepad.get());
	//auto gainSmallScoreCommandGamepad = std::make_unique<dae::GainPointsCommand>(playerInputObjectGamepad.get());
	//gainSmallScoreCommandGamepad->SetGainScore(10);
	//auto gainBigScoreCommandGamepad = std::make_unique<dae::GainPointsCommand>(playerInputObjectGamepad.get());
	//gainBigScoreCommandGamepad->SetGainScore(100);

	auto spawnBombCommandGamepad = std::make_unique<dae::SpawnBombCommand>(playerInputObjectGamepad.get());

	dae::InputManager::GetInstance().AddBinding(std::move(moveLeftCommand), dae::KeyState::Pressed, 0x004, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(moveRightCommand), dae::KeyState::Pressed, 0x008, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(moveUpCommand), dae::KeyState::Pressed, 0x001, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(moveDownCommand), dae::KeyState::Pressed, 0x002, 0);
	//dae::InputManager::GetInstance().AddBinding(std::move(loseLivesCommandGamepad), dae::KeyState::Up, 0x1000, 0);
	//dae::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommandGamepad), dae::KeyState::Up, 0x2000, 0);
	//dae::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommandGamepad), dae::KeyState::Up, 0x4000, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(spawnBombCommandGamepad), dae::KeyState::Up, 0x8000, 0);

	scene->Add(std::move(playerInputObjectGamepad));
	// --------END GAMEPAD-----------
}

void LoadPlayerKeyboard(dae::Scene* scene, dae::GameObject* levelParent, dae::LivesTextComponent* playerLivesTextChange)
{
	// --------KEYBOARD-----------
	//display lives
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//display Player
	//auto playerKeyboardTextObject = std::make_unique<dae::GameObject>();
	//playerKeyboardTextObject->SetWorldPosition(50, 275);
	//auto playerTextKeyboard = std::make_unique<dae::TextComponent>(playerKeyboardTextObject.get(), "Player Two:", font);
	//playerTextKeyboard->ChangeFontSize(20);
	//playerKeyboardTextObject->AddComponent(std::move(playerTextKeyboard));
	//scene->Add(std::move(playerKeyboardTextObject));

	//display score
	auto playerKeyboardScoreTextObject = std::make_unique<dae::GameObject>();
	playerKeyboardScoreTextObject->SetWorldPosition(500, 32);
	auto playerScoreTextKeyboard = std::make_unique<dae::TextComponent>(playerKeyboardScoreTextObject.get(), "Current score: 0", font);
	playerScoreTextKeyboard->ChangeFontSize(32);
	playerKeyboardScoreTextObject->AddComponent(std::move(playerScoreTextKeyboard));
	auto playerScoreTextChangeKeyboard = std::make_unique<dae::ScoreTextComponent>(playerKeyboardScoreTextObject.get());

	// ------- INPUT KEYBOARD ---------

	auto playerInputObjectKeyboard = std::make_unique<dae::GameObject>();
	playerInputObjectKeyboard->SetParent(levelParent, true);
	auto playerInputKeyboardSpriteSheet = std::make_unique<dae::SpriteSheetComponent>(playerInputObjectKeyboard.get(), "PlayerMove.png", 4, 4, 0.2f, false);
	auto playerInputKeyboardSpriteSetter = std::make_unique<dae::PlayerSpriteComponent>(playerInputObjectKeyboard.get());
	auto playerInputKeyboardCollider = std::make_unique<dae::PlayerCollider>(playerInputObjectKeyboard.get(), 28.f, 28.f, true);
	playerInputKeyboardCollider->SetDebugRendering(true);
	playerInputObjectKeyboard->SetWorldPosition(48, 112);
	playerInputObjectKeyboard->AddComponent(std::move(playerInputKeyboardSpriteSheet));
	playerInputObjectKeyboard->AddComponent(std::move(playerInputKeyboardSpriteSetter));
	playerInputObjectKeyboard->AddComponent(std::move(playerInputKeyboardCollider));

	//lives
	auto playerLivesKeyboard = std::make_unique<dae::LivesComponent>(playerInputObjectKeyboard.get(), 3);
	playerLivesKeyboard->GetActorDiedSubject()->AddObserver(playerLivesTextChange);
	playerInputObjectKeyboard->AddComponent(std::move(playerLivesKeyboard));

	//score
	auto playerScoreKeyboard = std::make_unique<dae::ScoreComponent>(playerInputObjectKeyboard.get());
	playerScoreKeyboard->GetActorScoreSubject()->AddObserver(playerScoreTextChangeKeyboard.get());
	playerScoreKeyboard->GetActorScoreSubject()->AddObserver(&dae::Achievements::GetInstance());
	dae::ScoreComponent* scoreComponentPlayerKeyboard = playerScoreKeyboard.get();
	playerKeyboardScoreTextObject->AddComponent(std::move(playerScoreTextChangeKeyboard)); // moves after observer is set
	playerInputObjectKeyboard->AddComponent(std::move(playerScoreKeyboard));

	auto moveLeftCommandKeyboard = std::make_unique<dae::MoveCommand>(playerInputObjectKeyboard.get());
	moveLeftCommandKeyboard->SetSpeed({ -50.f, 0.f });
	auto moveRightCommandKeyboard = std::make_unique<dae::MoveCommand>(playerInputObjectKeyboard.get());
	moveRightCommandKeyboard->SetSpeed({ 50.f, 0.f });
	auto moveUpCommandKeyboard = std::make_unique<dae::MoveCommand>(playerInputObjectKeyboard.get());
	moveUpCommandKeyboard->SetSpeed({ 0.f, -50.f });
	auto moveDownCommandKeyboard = std::make_unique<dae::MoveCommand>(playerInputObjectKeyboard.get());
	moveDownCommandKeyboard->SetSpeed({ 0.f, 50.f });

	auto loseLivesCommandKeyboard = std::make_unique<dae::LoseLiveCommand>(playerInputObjectKeyboard.get());
	auto gainSmallScoreCommandKeyboard = std::make_unique<dae::GainPointsCommand>(playerInputObjectKeyboard.get());
	gainSmallScoreCommandKeyboard->SetGainScore(10);
	auto gainBigScoreCommandKeyboard = std::make_unique<dae::GainPointsCommand>(playerInputObjectKeyboard.get());
	gainBigScoreCommandKeyboard->SetGainScore(100);

	auto spawnBombCommandKeyboard = std::make_unique<dae::SpawnBombCommand>(playerInputObjectKeyboard.get());

	dae::InputManager::GetInstance().AddBinding(std::move(moveLeftCommandKeyboard), dae::KeyState::Pressed, SDLK_a, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(moveRightCommandKeyboard), dae::KeyState::Pressed, SDLK_d, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(moveUpCommandKeyboard), dae::KeyState::Pressed, SDLK_w, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(moveDownCommandKeyboard), dae::KeyState::Pressed, SDLK_s, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(loseLivesCommandKeyboard), dae::KeyState::Up, SDLK_q, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommandKeyboard), dae::KeyState::Up, SDLK_e, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommandKeyboard), dae::KeyState::Up, SDLK_r, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(spawnBombCommandKeyboard), dae::KeyState::Up, SDLK_f, -1);

	scene->Add(std::move(playerInputObjectKeyboard));
	scene->Add(std::move(playerKeyboardScoreTextObject));

	// --------END KEYBOARD-----------

	// --------ENEMIES----------
	auto enemy = std::make_unique<dae::GameObject>();
	enemy->SetTag(make_sdbm_hash("Enemy"));
	enemy->SetWorldPosition(48, 304);
	enemy->SetParent(levelParent, true);
	auto enemyMovement = std::make_unique<dae::EnemyMovementComponent>(enemy.get(), 15.f, "Balloom");
	enemyMovement->SetDebugRendering(true);
	enemyMovement->GetEnemyDiedSubject()->AddObserver(scoreComponentPlayerKeyboard);
	auto enemyCollider = std::make_unique<dae::BaseColliderComponent>(enemy.get(), 25.f, 25.f, false);
	auto enemySprite = std::make_unique<dae::SpriteSheetComponent>(enemy.get(), "Balloom.png", 4, 3, 0.2f, false);

	enemy->AddComponent(std::move(enemyMovement));
	enemy->AddComponent(std::move(enemyCollider));
	enemy->AddComponent(std::move(enemySprite));

	scene->Add(std::move(enemy));
}


void LoadStartScene()
{
	auto scene = dae::SceneManager::GetInstance().GetCurrentScene();

	auto backgroundObject = std::make_unique<dae::GameObject>();
	backgroundObject->SetWorldPosition(100, 300);
	auto background = std::make_unique<dae::TextureComponent>(backgroundObject.get(), "background.tga");
	auto backgroundTwo = std::make_unique<dae::TextureComponent>(backgroundObject.get(), "background.tga", true);
	backgroundTwo->SetCustomPosition(glm::vec2(740, 300));
	backgroundObject->AddComponent(std::move(background));
	backgroundObject->AddComponent(std::move(backgroundTwo));
	scene->Add(std::move(backgroundObject));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto startButtonTextObject = std::make_unique<dae::GameObject>();
	startButtonTextObject->SetWorldPosition(500, 275);
	auto startButtonText = std::make_unique<dae::TextComponent>(startButtonTextObject.get(), "Press E on keyboard or ??? (gamepad start not working yet) on gamepad to start game", font);
	startButtonText->ChangeFontSize(20);
	startButtonTextObject->AddComponent(std::move(startButtonText));
	scene->Add(std::move(startButtonTextObject));

	auto logoObject = std::make_unique<dae::GameObject>();
	auto logo = std::make_unique<dae::TextureComponent>(logoObject.get(), "logo.tga");
	logoObject->SetWorldPosition(500, 180);
	logoObject->AddComponent(std::move(logo));

	scene->Add(std::move(logoObject));

	auto playerStartButtonObjectKeyboard = std::make_unique<dae::GameObject>();
	auto startGameCommandKeyboard = std::make_unique<dae::StartGameCommand>(playerStartButtonObjectKeyboard.get());

	auto playerStartButtonObjectGamepad = std::make_unique<dae::GameObject>();
	auto startGameCommandGamepad = std::make_unique<dae::StartGameCommand>(playerStartButtonObjectGamepad.get());

	
	//dae::InputManager::GetInstance().AddBinding(std::move(startGameCommandGamepad), dae::KeyState::Up, 0x8000, 0); //TODO: Issues with input that keeps going after game start
	dae::InputManager::GetInstance().AddBinding(std::move(startGameCommandKeyboard), dae::KeyState::Up, SDLK_e, -1);

	scene->Add(std::move(playerStartButtonObjectKeyboard));
	scene->Add(std::move(playerStartButtonObjectGamepad));

	// --------TUTORIAL TEXT----------
	auto tutorialControls = std::make_unique<dae::GameObject>();
	tutorialControls->SetWorldPosition(500, 360);
	auto tutorialText = std::make_unique<dae::TextComponent>(tutorialControls.get(), "Controls", font);
	tutorialControls->AddComponent(std::move(tutorialText));
	scene->Add(std::move(tutorialControls));

	auto tutorialObjectGamepad = std::make_unique<dae::GameObject>();
	tutorialObjectGamepad->SetWorldPosition(500, 400);
	auto tutorialTextGamepad = std::make_unique<dae::TextComponent>(tutorialObjectGamepad.get(), "Use D-Pad to move, Y to place bomb, kill Balloom to get score", font);
	tutorialTextGamepad->ChangeFontSize(15);
	tutorialObjectGamepad->AddComponent(std::move(tutorialTextGamepad));
	scene->Add(std::move(tutorialObjectGamepad));

	auto tutorialObjectKeyboard = std::make_unique<dae::GameObject>();
	tutorialObjectKeyboard->SetWorldPosition(500, 420);
	auto tutorialTextKeyboard = std::make_unique<dae::TextComponent>(tutorialObjectKeyboard.get(), "Use WASD to move, F to place bomb, kill Balloom to get score", font);
	tutorialTextKeyboard->ChangeFontSize(15);
	tutorialObjectKeyboard->AddComponent(std::move(tutorialTextKeyboard));
	scene->Add(std::move(tutorialObjectKeyboard));

	auto tutorialNotes = std::make_unique<dae::GameObject>();
	tutorialNotes->SetWorldPosition(500, 450);
	auto tutorialNotesText = std::make_unique<dae::TextComponent>(tutorialNotes.get(), "only keyboard player can get killed by balloom for now", font);
	tutorialNotesText->ChangeFontSize(20);
	tutorialNotes->AddComponent(std::move(tutorialNotesText));
	scene->Add(std::move(tutorialNotes));

	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/TitleScreen.mp3", 30, -1);//50 volume
}

void LoadGameScene()
{
	auto scene = dae::SceneManager::GetInstance().GetCurrentScene();

	//auto backgroundObject = std::make_unique<dae::GameObject>();
	//auto background = std::make_unique<dae::TextureComponent>(backgroundObject.get(), "background.tga");
	//backgroundObject->SetWorldPosition(0, 0);
	//backgroundObject->AddComponent(std::move(background));
	//
	//scene->Add(std::move(backgroundObject));

	//auto logoObject = std::make_unique<dae::GameObject>();
	//auto logo = std::make_unique<dae::TextureComponent>(logoObject.get(), "logo.tga");
	//logoObject->SetWorldPosition(216, 180);
	//logoObject->AddComponent(std::move(logo));
	//
	//scene->Add(std::move(logoObject));
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	//auto assignmentTextObject = std::make_unique<dae::GameObject>();
	//
	//auto assignmentText = std::make_unique<dae::TextComponent>(assignmentTextObject.get(), "Programming 4 Assignment", font);
	//assignmentTextObject->SetWorldPosition(80, 50);
	//assignmentTextObject->AddComponent(std::move(assignmentText));
	//scene->Add(std::move(assignmentTextObject));

	auto fpsObject = std::make_unique<dae::GameObject>();
	auto fpsText = std::make_unique<dae::TextComponent>(fpsObject.get(), "FPS:", font);
	fpsObject->SetWorldPosition(80, 32);
	fpsObject->AddComponent(std::move(fpsText));

	auto fpsCounter = std::make_unique<dae::FpsComponent>(fpsObject.get());
	fpsObject->AddComponent(std::move(fpsCounter));

	//auto fpsMovement = std::make_unique<dae::MovementComponent>();
	//fpsMovement->SetSpeed(5.f, 0.f);
	//auto fpsRotPos = glm::vec3{ 216, 180, 0 };
	//fpsMovement->SetRotationSpeed(1.f, fpsRotPos);
	//fpsObject->AddComponent(std::move(fpsMovement));

	scene->Add(std::move(fpsObject));


	//PLAYER SINGLE SPRITE
	// auto playerObject = std::make_unique<dae::GameObject>();
	// auto player = std::make_unique<dae::TextureComponent>(playerObject.get(), "Bomberman.png");
	// playerObject->SetWorldPosition(120, 300);
	// playerObject->AddComponent(std::move(player));
	// 
	// auto playerMovement = std::make_unique<dae::MovementComponent>(playerObject.get());
	// //playerMovement->SetSpeed(20.f, 0.f);
	// playerMovement->SetRotation(3.f, 170, 300);
	// playerObject->AddComponent(std::move(playerMovement));
	// 
	// 
	// 
	// //PLAYER ROTATION AROUND OTHER PLAYER
	// auto secondPlayerObject = std::make_unique<dae::GameObject>();
	// secondPlayerObject->SetParent(playerObject.get(), false);
	// auto secondPlayer = std::make_unique<dae::TextureComponent>(secondPlayerObject.get(), "Bomberman.png");
	// secondPlayerObject->SetWorldPosition(100, 300);
	// glm::vec3 secondPlayerLocPos = { 40, 0, 0 };
	// secondPlayerObject->SetLocalPosition(secondPlayerLocPos);
	// secondPlayerObject->AddComponent(std::move(secondPlayer));
	// 
	// auto secondPlayerMovement = std::make_unique<dae::MovementComponent>(secondPlayerObject.get());
	// secondPlayerMovement->SetRotation(-50.f, playerObject->GetWorldPosition().x, playerObject->GetWorldPosition().y);
	// secondPlayerObject->AddComponent(std::move(secondPlayerMovement));
	// 
	// auto secondPlayerRotatePoint = std::make_unique<dae::RotatingMovingPointComponent>(secondPlayerObject.get());
	// secondPlayerObject->AddComponent(std::move(secondPlayerRotatePoint));
	// 
	// 
	// 
	// scene->Add(std::move(playerObject));
	// scene->Add(std::move(secondPlayerObject));

	//auto trashCashObject = std::make_unique<dae::GameObject>();
	//auto trashCash = std::make_unique<dae::TrashCashComponent>(trashCashObject.get());
	//trashCashObject->AddComponent(std::move(trashCash));
	//scene->Add(std::move(trashCashObject));

	//Input
	auto gridObject = std::make_unique<dae::GameObject>();
	gridObject->SetTag(make_sdbm_hash("Grid"));
	gridObject->SetWorldPosition(0, 0);
	auto gridView = std::make_unique<dae::GridComponent>(gridObject.get(), 31, 13, 992, 476, 32.f, 64.f);
	gridObject->AddComponent(std::move(gridView));



	auto playerLivesTextObject = std::make_unique<dae::GameObject>();
	playerLivesTextObject->SetWorldPosition(700, 30);
	auto playerLivesText = std::make_unique<dae::TextComponent>(playerLivesTextObject.get(), "Lives: 3", font);
	//playerLivesText->ChangeFontSize(18);
	playerLivesTextObject->AddComponent(std::move(playerLivesText));
	auto playerLivesTextChange = std::make_unique<dae::LivesTextComponent>(playerLivesTextObject.get());

	//please do smth about not passing a lot of pointers in functions
	LoadPlayerGamePad(scene, gridObject.get(), playerLivesTextChange.get());
	LoadPlayerKeyboard(scene, gridObject.get(), playerLivesTextChange.get());
	//LoadEnemies(scene, gridObject.get(), playerKeyboardCollider);

	playerLivesTextObject->AddComponent(std::move(playerLivesTextChange)); // moves after observer is set

	scene->Add(std::move(gridObject));
	scene->Add(std::move(playerLivesTextObject));

	// --------SOUND----------
	dae::ServiceLocator::GetSoundSystem().AddSound(make_sdbm_hash("ExplodeBombSFX"), "../Data/Sound/BombExplodes.wav");
	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainBGM.mp3", 0, -1); //50 volume
}

void load()
{
	//auto& sceneStart = dae::SceneManager::GetInstance().CreateScene("Start", true);
	//sceneStart.SetLoadingFunction(LoadStartScene);
	auto& sceneGame = dae::SceneManager::GetInstance().CreateScene("Game", true);
	sceneGame.SetLoadingFunction(LoadGameScene);

#if _DEBUG

	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
#endif
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}

