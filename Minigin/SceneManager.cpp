#include "SceneManager.h"
#include "Scene.h"

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
}

void dae::SceneManager::Render()
{
	m_pCurrentScene->Render();
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
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
