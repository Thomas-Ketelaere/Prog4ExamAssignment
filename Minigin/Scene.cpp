#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : 
	m_Name{ name },
	m_Destroy{}
{
}

void dae::Scene::ReloadScene()
{
	m_Objects.clear();
	m_LoadingFunction();
	m_Reload = false;
}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void dae::Scene::Start()
{
	for (auto& object : m_Objects)
	{
		object->Start();
	}
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
	std::erase_if(m_Objects, [](const std::unique_ptr<GameObject>& object)
		{
			return object->IsMarkedDestroy();
		});
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

