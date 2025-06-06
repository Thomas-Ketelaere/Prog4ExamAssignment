#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace RamCoreEngine;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(unsigned int name) :
	m_Name{ name },
	m_Destroy{},
	m_ShouldReload{}
{
}

void RamCoreEngine::Scene::ReloadScene()
{
	RemoveAll();
	m_LoadingFunction();
	m_ShouldReload = false;
}

Scene::~Scene() = default;

std::vector<GameObject*> RamCoreEngine::Scene::GetAllObjectsWithTag(unsigned int tag)
{
	std::vector<GameObject*> objectsWithTag;
	for (auto& gameObject : m_Objects)
	{
		if (tag == gameObject->GetTag())
		{
			objectsWithTag.emplace_back(gameObject.get());
		}
	}
	return objectsWithTag;
}

GameObject* RamCoreEngine::Scene::GetFirstObjectWithTag(unsigned int tag)
{

	auto it = std::find_if(m_Objects.begin(), m_Objects.end(), [&](std::unique_ptr<GameObject>& gameObject)
		{
			return tag == gameObject->GetTag();
		});

	if (it != m_Objects.end())
	{
		return it->get();
	}
	return nullptr;
}

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
	m_Destroy = false;
}

void RamCoreEngine::Scene::Start()
{
	for (auto& object : m_Objects)
	{
		object->Start();
	}
}

void Scene::Update()
{
	//for(auto& object : m_Objects)
	//{
	//	object->Update();
	//}

	for (size_t objectCounter{}; objectCounter < m_Objects.size(); ++objectCounter)
	{
		m_Objects[objectCounter]->Update();
	}
}

void RamCoreEngine::Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
	std::erase_if(m_Objects, [](const std::unique_ptr<GameObject>& object)
		{
			if (object->IsMarkedDestroy())
			{
				object->OnDestroy();
				return true;
			}
			return false;
		});
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

