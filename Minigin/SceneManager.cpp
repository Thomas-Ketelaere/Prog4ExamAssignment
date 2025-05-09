#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include <stdexcept>
#include "ServiceLocator.h"
#include "ColliderManager.h"

void RamCoreEngine::SceneManager::Start()
{
	//for (auto& scene : m_Scenes)
	//{
	//	scene->Start();
	//}
	m_pCurrentScene->Start();
}

void RamCoreEngine::SceneManager::Update()
{
	//for(auto& scene : m_Scenes)
	//{
	//	scene->Update();
	//}
	m_pCurrentScene->Update();
}

void RamCoreEngine::SceneManager::FixedUpdate() // should have float FixedTime
{

}

void RamCoreEngine::SceneManager::LateUpdate()
{
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->LateUpdate();
	//}
	m_pCurrentScene->LateUpdate();
	if (m_pCurrentScene->IsMarkedReload())
	{
		InputManager::GetInstance().ClearBindings();
		RamCoreEngine::ServiceLocator::GetSoundSystem().UnloadAllSound();
		RamCoreEngine::ServiceLocator::GetSoundSystem().UnloadMusic();
		ColliderManager::GetInstance().ClearColliders();
		m_pCurrentScene->ReloadScene();
		m_pCurrentScene->Start();
		InputManager::GetInstance().Start();
	}
	
	for (auto& scene : m_Scenes)
	{
		if (scene->IsMarkedDestroy())
		{
			scene->RemoveAll();
		}
	}
}

void RamCoreEngine::SceneManager::Render()
{
	m_pCurrentScene->Render();
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
}

void RamCoreEngine::SceneManager::LoadScene(const std::string& sceneToLoadName)
{
	//TODO: IMPROVE
	for (auto& scene : m_Scenes)
	{
		if (scene->GetName() == sceneToLoadName)
		{
			if (m_pCurrentScene->GetName() == scene->GetName())
			{
				throw std::runtime_error("trying to load and destroy already existing/current scene. Use 'ReloadScene' instead.");
			}
			auto* previousScene = m_pCurrentScene;
			//TODO: dont destroy on load (if necessary)
			InputManager::GetInstance().ClearBindings();
			RamCoreEngine::ServiceLocator::GetSoundSystem().UnloadAllSound();
			RamCoreEngine::ServiceLocator::GetSoundSystem().UnloadMusic();
			ColliderManager::GetInstance().ClearColliders();
			m_pCurrentScene = scene.get();
			scene->LoadScene();
			scene->Start();
			InputManager::GetInstance().Start();
			previousScene->Destroy();
			return;
		}
	}

	throw std::runtime_error("Scene not found");
}

void RamCoreEngine::SceneManager::ReloadScene()
{
	m_pCurrentScene->MarkForReload();
	
}

RamCoreEngine::Scene& RamCoreEngine::SceneManager::CreateScene(const std::string& name, bool setAsCurrentScene)
{
	auto scene = std::make_unique<Scene>(name);
	if (setAsCurrentScene)
	{
		m_pCurrentScene = scene.get();
	}
	m_Scenes.push_back(std::move(scene));
	return *m_Scenes.back();
}
