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
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"
#include "MovementComponent.h"
#include "RotatingMovingPointComponent.h"
#include "GameObject.h"
#include "TrashCashComponent.h"
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
#include <iostream>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundObject = std::make_unique<dae::GameObject>();
	auto background = std::make_unique<dae::TextureComponent>(backgroundObject.get(), "background.tga");
	backgroundObject->SetWorldPosition(0, 0);
	backgroundObject->AddComponent(std::move(background));

	scene.Add(std::move(backgroundObject));

	auto logoObject = std::make_unique<dae::GameObject>();
	auto logo = std::make_unique<dae::TextureComponent>(logoObject.get(), "logo.tga");
	logoObject->SetWorldPosition(216, 180);
	logoObject->AddComponent(std::move(logo));

	scene.Add(std::move(logoObject));

	
	auto assignmentTextObject = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto assignmentText = std::make_unique<dae::TextComponent>(assignmentTextObject.get(), "Programming 4 Assignment", font);
	assignmentTextObject->SetWorldPosition(80, 50);
	assignmentTextObject->AddComponent(std::move(assignmentText));

	scene.Add(std::move(assignmentTextObject));

	auto fpsObject = std::make_unique<dae::GameObject>();
	auto fpsText = std::make_unique<dae::TextComponent>(fpsObject.get(), "FPS:", font);
	fpsObject->SetWorldPosition(80, 100);
	fpsObject->AddComponent(std::move(fpsText));

	auto fpsCounter = std::make_unique<dae::FpsComponent>(fpsObject.get());
	fpsObject->AddComponent(std::move(fpsCounter));

	//auto fpsMovement = std::make_unique<dae::MovementComponent>();
	//fpsMovement->SetSpeed(5.f, 0.f);
	//auto fpsRotPos = glm::vec3{ 216, 180, 0 };
	//fpsMovement->SetRotationSpeed(1.f, fpsRotPos);
	//fpsObject->AddComponent(std::move(fpsMovement));

	scene.Add(std::move(fpsObject));


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
	// scene.Add(std::move(playerObject));
	// scene.Add(std::move(secondPlayerObject));

	//auto trashCashObject = std::make_unique<dae::GameObject>();
	//auto trashCash = std::make_unique<dae::TrashCashComponent>(trashCashObject.get());
	//trashCashObject->AddComponent(std::move(trashCash));
	//scene.Add(std::move(trashCashObject));

	//Input
	// --------GAMEPAD-----------
	auto playerInputObjectGamepad = std::make_unique<dae::GameObject>();
	auto playerInput = std::make_unique<dae::TextureComponent>(playerInputObjectGamepad.get(), "Bomberman.png");
	playerInputObjectGamepad->SetWorldPosition(400, 300);
	playerInputObjectGamepad->AddComponent(std::move(playerInput));

	//display Player
	auto playerGamepadTextObject = std::make_unique<dae::GameObject>();
	playerGamepadTextObject->SetWorldPosition(50, 175);
	auto playerTextGamepad = std::make_unique<dae::TextComponent>(playerGamepadTextObject.get(), "Player One:", font);
	playerTextGamepad->ChangeFontSize(20);
	playerGamepadTextObject->AddComponent(std::move(playerTextGamepad));
	scene.Add(std::move(playerGamepadTextObject));

	//display lives
	auto playerGamepadLivesTextObject = std::make_unique<dae::GameObject>();
	playerGamepadLivesTextObject->SetWorldPosition(50, 200);
	auto playerLivesTextGamepad = std::make_unique<dae::TextComponent>(playerGamepadLivesTextObject.get(), "Lives: 3", font);
	playerLivesTextGamepad->ChangeFontSize(18);
	playerGamepadLivesTextObject->AddComponent(std::move(playerLivesTextGamepad));
	auto playerLivesTextChangeGamepad = std::make_unique<dae::LivesTextComponent>(playerGamepadLivesTextObject.get());

	//display score
	auto playerGamepadScoreTextObject = std::make_unique<dae::GameObject>();
	playerGamepadScoreTextObject->SetWorldPosition(50, 220);
	auto playerScoreTextGamepad = std::make_unique<dae::TextComponent>(playerGamepadScoreTextObject.get(), "Current score: 0", font);
	playerScoreTextGamepad->ChangeFontSize(18);
	playerGamepadScoreTextObject->AddComponent(std::move(playerScoreTextGamepad));
	auto playerScoreTextChangeGamepad = std::make_unique<dae::ScoreTextComponent>(playerGamepadScoreTextObject.get());

	// ------- INPUT GAMEPAD ---------
	//lives
	auto playerLivesGamepad = std::make_unique<dae::LivesComponent>(playerInputObjectGamepad.get(), 3);
	playerLivesGamepad->GetActorDiedSubject()->AddObserver(playerLivesTextChangeGamepad.get());
	playerGamepadLivesTextObject->AddComponent(std::move(playerLivesTextChangeGamepad)); // moves after observer is set
	playerInputObjectGamepad->AddComponent(std::move(playerLivesGamepad));

	//score
	auto playerScoreGamepad = std::make_unique<dae::ScoreComponent>(playerInputObjectGamepad.get());
	playerScoreGamepad->GetActorScoreSubject()->AddObserver(playerScoreTextChangeGamepad.get());
	playerGamepadScoreTextObject->AddComponent(std::move(playerScoreTextChangeGamepad)); // moves after observer is set
	playerInputObjectGamepad->AddComponent(std::move(playerScoreGamepad));


	auto moveLeftCommand = std::make_unique<dae::MoveCommand>(playerInputObjectGamepad.get());
	moveLeftCommand->SetSpeed({ -50.f, 0.f });
	auto moveRightCommand = std::make_unique<dae::MoveCommand>(playerInputObjectGamepad.get());
	moveRightCommand->SetSpeed({ 50.f, 0.f });
	auto moveUpCommand = std::make_unique<dae::MoveCommand>(playerInputObjectGamepad.get());
	moveUpCommand->SetSpeed({ 0.f, -50.f });
	auto moveDownCommand = std::make_unique<dae::MoveCommand>(playerInputObjectGamepad.get());
	moveDownCommand->SetSpeed({ 0.f, 50.f });

	auto loseLivesCommandGamepad = std::make_unique<dae::LoseLiveCommand>(playerInputObjectGamepad.get());
	auto gainSmallScoreCommandGamepad = std::make_unique<dae::GainPointsCommand>(playerInputObjectGamepad.get());
	gainSmallScoreCommandGamepad->SetGainScore(10);
	auto gainBigScoreCommandGamepad = std::make_unique<dae::GainPointsCommand>(playerInputObjectGamepad.get());
	gainBigScoreCommandGamepad->SetGainScore(100);

	dae::InputManager::GetInstance().AddBinding(std::move(moveLeftCommand), dae::KeyState::Pressed, 0x004, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(moveRightCommand), dae::KeyState::Pressed, 0x008, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(moveUpCommand), dae::KeyState::Pressed, 0x001, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(moveDownCommand), dae::KeyState::Pressed, 0x002, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(loseLivesCommandGamepad), dae::KeyState::Up, 0x1000, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommandGamepad), dae::KeyState::Up, 0x2000, 0);
	dae::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommandGamepad), dae::KeyState::Up, 0x4000, 0);


	scene.Add(std::move(playerInputObjectGamepad));
	scene.Add(std::move(playerGamepadLivesTextObject));
	scene.Add(std::move(playerGamepadScoreTextObject));
	// --------END GAMEPAD-----------

	//display Player
	auto playerKeyboardTextObject = std::make_unique<dae::GameObject>();
	playerKeyboardTextObject->SetWorldPosition(50, 275);
	auto playerTextKeyboard = std::make_unique<dae::TextComponent>(playerKeyboardTextObject.get(), "Player Two:", font);
	playerTextKeyboard->ChangeFontSize(20);
	playerKeyboardTextObject->AddComponent(std::move(playerTextKeyboard));
	scene.Add(std::move(playerKeyboardTextObject));

	// --------KEYBOARD-----------
	//display lives
	auto playerKeyboardLivesTextObject = std::make_unique<dae::GameObject>();
	playerKeyboardLivesTextObject->SetWorldPosition(50, 300);
	auto playerLivesTextKeyboard = std::make_unique<dae::TextComponent>(playerKeyboardLivesTextObject.get(), "Lives: 3", font);
	playerLivesTextKeyboard->ChangeFontSize(18);
	playerKeyboardLivesTextObject->AddComponent(std::move(playerLivesTextKeyboard));
	auto playerLivesTextChangeKeyboard = std::make_unique<dae::LivesTextComponent>(playerKeyboardLivesTextObject.get());

	//display score
	auto playerKeyboardScoreTextObject = std::make_unique<dae::GameObject>();
	playerKeyboardScoreTextObject->SetWorldPosition(50, 320);
	auto playerScoreTextKeyboard = std::make_unique<dae::TextComponent>(playerKeyboardScoreTextObject.get(), "Current score: 0", font);
	playerScoreTextKeyboard->ChangeFontSize(18);
	playerKeyboardScoreTextObject->AddComponent(std::move(playerScoreTextKeyboard));
	auto playerScoreTextChangeKeyboard = std::make_unique<dae::ScoreTextComponent>(playerKeyboardScoreTextObject.get());

	// ------- INPUT KEYBOARD ---------

	auto playerInputObjectKeyboard = std::make_unique<dae::GameObject>();
	auto playerInputKeyboard = std::make_unique<dae::TextureComponent>(playerInputObjectKeyboard.get(), "Bomberman.png");
	playerInputObjectKeyboard->SetWorldPosition(450, 300);
	playerInputObjectKeyboard->AddComponent(std::move(playerInputKeyboard));

	//lives
	auto playerLivesKeyboard = std::make_unique<dae::LivesComponent>(playerInputObjectKeyboard.get(), 3);
	playerLivesKeyboard->GetActorDiedSubject()->AddObserver(playerLivesTextChangeKeyboard.get());
	playerKeyboardLivesTextObject->AddComponent(std::move(playerLivesTextChangeKeyboard)); // moves after observer is set
	playerInputObjectKeyboard->AddComponent(std::move(playerLivesKeyboard));

	//score
	auto playerScoreKeyboard = std::make_unique<dae::ScoreComponent>(playerInputObjectKeyboard.get());
	playerScoreKeyboard->GetActorScoreSubject()->AddObserver(playerScoreTextChangeKeyboard.get());
	playerScoreKeyboard->GetActorScoreSubject()->AddObserver(&dae::Achievements::GetInstance());
	playerKeyboardScoreTextObject->AddComponent(std::move(playerScoreTextChangeKeyboard)); // moves after observer is set
	playerInputObjectKeyboard->AddComponent(std::move(playerScoreKeyboard));

	auto moveLeftCommandKeyboard = std::make_unique<dae::MoveCommand>(playerInputObjectKeyboard.get());
	moveLeftCommandKeyboard->SetSpeed({ -25.f, 0.f });
	auto moveRightCommandKeyboard = std::make_unique<dae::MoveCommand>(playerInputObjectKeyboard.get());
	moveRightCommandKeyboard->SetSpeed({ 25.f, 0.f });
	auto moveUpCommandKeyboard = std::make_unique<dae::MoveCommand>(playerInputObjectKeyboard.get());
	moveUpCommandKeyboard->SetSpeed({ 0.f, -25.f });
	auto moveDownCommandKeyboard = std::make_unique<dae::MoveCommand>(playerInputObjectKeyboard.get());
	moveDownCommandKeyboard->SetSpeed({ 0.f, 25.f });

	auto loseLivesCommandKeyboard = std::make_unique<dae::LoseLiveCommand>(playerInputObjectKeyboard.get());
	auto gainSmallScoreCommandKeyboard = std::make_unique<dae::GainPointsCommand>(playerInputObjectKeyboard.get());
	gainSmallScoreCommandKeyboard->SetGainScore(10);
	auto gainBigScoreCommandKeyboard = std::make_unique<dae::GainPointsCommand>(playerInputObjectKeyboard.get());
	gainBigScoreCommandKeyboard->SetGainScore(100);

	dae::InputManager::GetInstance().AddBinding(std::move(moveLeftCommandKeyboard), dae::KeyState::Pressed, SDLK_a, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(moveRightCommandKeyboard), dae::KeyState::Pressed, SDLK_d, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(moveUpCommandKeyboard), dae::KeyState::Pressed, SDLK_w, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(moveDownCommandKeyboard), dae::KeyState::Pressed, SDLK_s, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(loseLivesCommandKeyboard), dae::KeyState::Up, SDLK_q, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(gainSmallScoreCommandKeyboard), dae::KeyState::Up, SDLK_e, -1);
	dae::InputManager::GetInstance().AddBinding(std::move(gainBigScoreCommandKeyboard), dae::KeyState::Up, SDLK_r, -1);

	scene.Add(std::move(playerInputObjectKeyboard));
	scene.Add(std::move(playerKeyboardLivesTextObject));
	scene.Add(std::move(playerKeyboardScoreTextObject));

	// --------END KEYBOARD-----------

	// --------TUTORIAL TEXT----------
	auto tutorialObjectGamepad = std::make_unique<dae::GameObject>();
	tutorialObjectGamepad->SetWorldPosition(50, 400);
	auto tutorialTextGamepad = std::make_unique<dae::TextComponent>(tutorialObjectGamepad.get(), "Use D-Pad to move, A to lose a life, B/X to gain small/big score from Balloom", font);
	tutorialTextGamepad->ChangeFontSize(15);
	tutorialObjectGamepad->AddComponent(std::move(tutorialTextGamepad));
	scene.Add(std::move(tutorialObjectGamepad));

	auto tutorialObjectKeyboard = std::make_unique<dae::GameObject>();
	tutorialObjectKeyboard->SetWorldPosition(50, 420);
	auto tutorialTextKeyboard = std::make_unique<dae::TextComponent>(tutorialObjectKeyboard.get(), "Use WASD to move, Q to lose a life, E/R to gain small/big score from Balloom", font);
	tutorialTextKeyboard->ChangeFontSize(15);
	tutorialObjectKeyboard->AddComponent(std::move(tutorialTextKeyboard));
	scene.Add(std::move(tutorialObjectKeyboard));

}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}