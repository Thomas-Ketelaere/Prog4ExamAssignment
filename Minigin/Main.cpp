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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundObject = std::make_unique<dae::GameObject>();
	auto background = std::make_unique<dae::TextureComponent>(backgroundObject.get(), "background.tga");
	backgroundObject.get()->SetWorldPosition(0, 0);
	backgroundObject.get()->AddComponent(std::move(background));

	scene.Add(std::move(backgroundObject));

	auto logoObject = std::make_unique<dae::GameObject>();
	auto logo = std::make_unique<dae::TextureComponent>(logoObject.get(), "logo.tga");
	logoObject.get()->SetWorldPosition(216, 180);
	logoObject.get()->AddComponent(std::move(logo));

	scene.Add(std::move(logoObject));


	auto assignmentTextObject = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto assignmentText = std::make_unique<dae::TextComponent>(assignmentTextObject.get(), "Programming 4 Assignment", font);
	assignmentTextObject.get()->SetWorldPosition(80, 50);
	assignmentTextObject.get()->AddComponent(std::move(assignmentText));

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
	auto playerObject = std::make_unique<dae::GameObject>();
	auto player = std::make_unique<dae::TextureComponent>(playerObject.get(), "Bomberman.png");
	playerObject->SetWorldPosition(120, 300);
	playerObject->AddComponent(std::move(player));

	auto playerMovement = std::make_unique<dae::MovementComponent>(playerObject.get());
	playerMovement->SetSpeed(20.f, 0.f);
	playerMovement->SetRotation(3.f, 140, 300);
	playerObject->AddComponent(std::move(playerMovement));



	//PLAYER ROTATION AROUND OTHER PLAYER
	auto secondPlayerObject = std::make_unique<dae::GameObject>();
	secondPlayerObject->SetParent(playerObject.get(), false);
	auto secondPlayer = std::make_unique<dae::TextureComponent>(secondPlayerObject.get(), "Bomberman.png");
	//secondPlayerObject->SetWorldPosition(100, 300);
	glm::vec3 secondPlayerLocPos = { 30, 0, 0 };
	secondPlayerObject->SetLocalPosition(secondPlayerLocPos);
	secondPlayerObject->AddComponent(std::move(secondPlayer));
	
	auto secondPlayerMovement = std::make_unique<dae::MovementComponent>(secondPlayerObject.get());
	secondPlayerMovement->SetRotation(-5.f, playerObject->GetWorldPosition().x, playerObject->GetWorldPosition().y);
	secondPlayerObject->AddComponent(std::move(secondPlayerMovement));
	
	auto secondPlayerRotatePoint = std::make_unique<dae::RotatingMovingPointComponent>(secondPlayerObject.get());
	secondPlayerObject->AddComponent(std::move(secondPlayerRotatePoint));
	
	scene.Add(std::move(playerObject));
	scene.Add(std::move(secondPlayerObject));

	auto trashCashObject = std::make_unique<dae::GameObject>();
	auto trashCash = std::make_unique<dae::TrashCashComponent>(trashCashObject.get());
	trashCashObject->AddComponent(std::move(trashCash));
	scene.Add(std::move(trashCashObject));

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}