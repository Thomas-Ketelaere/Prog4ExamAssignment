#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include <stdexcept>

void dae::SceneManager::Start()
{
	//for (auto& scene : m_Scenes)
	//{
	//	scene->Start();
	//}
	m_pCurrentScene->Start();
}

void dae::SceneManager::Update()
{
	//for(auto& scene : m_Scenes)
	//{
	//	scene->Update();
	//}
	m_pCurrentScene->Update();
}

void dae::SceneManager::FixedUpdate() // should have float FixedTime
{

}

void dae::SceneManager::LateUpdate()
{
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->LateUpdate();
	//}
	m_pCurrentScene->LateUpdate();
	if (m_pCurrentScene->IsMarkedReload())
	{
		InputManager::GetInstance().ClearBindings();
		m_pCurrentScene->ReloadScene();
		m_pCurrentScene->Start();
	}
	std::erase_if(m_Scenes, [](const std::unique_ptr<Scene>& scene)
		{
			return scene->IsMarkedDestroy();
		});
}

void dae::SceneManager::Render()
{
	m_pCurrentScene->Render();
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
}

void dae::SceneManager::LoadScene(const std::string& sceneToLoadName)
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
			auto previousScene = m_pCurrentScene;
			//TODO: dont destroy on load (if necessary)
			InputManager::GetInstance().ClearBindings();
			m_pCurrentScene = scene.get();
			scene->LoadScene();
			scene->Start();
			previousScene->Destroy();
		}
	}
}

void dae::SceneManager::ReloadScene()
{
	m_pCurrentScene->MarkForReload();
	
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name, bool setAsCurrentScene)
{
	auto scene = std::make_unique<Scene>(name);
	if (setAsCurrentScene)
	{
		m_pCurrentScene = scene.get();
	}
	m_Scenes.push_back(std::move(scene));
	return *m_Scenes.back();
}
