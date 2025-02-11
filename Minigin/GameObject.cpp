#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Time.h"
#include "Component.h"
#include <memory>

dae::GameObject::GameObject()
{
	auto tempTransform = std::make_unique<Transform>();
	m_Transform = tempTransform.get();
	AddComponent(std::move(tempTransform));
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start()
{
	for (std::shared_ptr<Component> component : m_ComponentsVector)
	{
		component->Start();
	}
}

void dae::GameObject::Update()
{
	float deltaTime = Time::GetInstance().m_DeltaTime;
	printf("%f\n", deltaTime);

	for (std::shared_ptr<Component> component : m_ComponentsVector)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<Component> component : m_ComponentsVector)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> newComponent)
{
	newComponent->m_pGameObject = this; // this component belongs to this game object
	newComponent->m_pTransform = m_Transform;
	m_ComponentsVector.emplace_back(std::move(newComponent));
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform->SetPosition(x, y, 0.0f);
}
