#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Time.h"
#include "Component.h"
#include <memory>

dae::GameObject::GameObject()
{
	auto tempTransform = std::make_unique<TransformComponent>(this);
	m_Transform = tempTransform.get();
	AddComponent(std::move(tempTransform));
}

dae::GameObject::~GameObject()
{
	SetParent(nullptr, false);
	for (GameObject* child : m_Children)
	{
		child->SetParent(nullptr, false);
	}
}

void dae::GameObject::Start()
{
	for (std::unique_ptr<Component>& component : m_ComponentsVector)
	{
		component->Start();
	}
}

void dae::GameObject::Update()
{
	for (std::unique_ptr<Component>& component : m_ComponentsVector)
	{
		component->Update();
	}
}

void dae::GameObject::LateUpdate()
{
	for (std::unique_ptr<Component>& component : m_ComponentsVector)
	{
		component->LateUpdate();
	}
	std::erase_if(m_ComponentsVector, [](const std::unique_ptr<Component>& component)
		{
			return component->IsMarkedDestroy();
		});
}

void dae::GameObject::Render() const
{
	for (const std::unique_ptr<Component>& component : m_ComponentsVector)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> newComponent)
{
	m_ComponentsVector.emplace_back(std::move(newComponent));
}


void dae::GameObject::SetWorldPosition(float x, float y)
{
	m_Transform->SetWorldPosition(x, y, 0.0f);
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_Parent == parent) return;
	if (parent == nullptr) SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		}
		SetPositionDirty();
	}
	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	std::erase_if(m_Children, [&](GameObject* go)
		{ 
			return go == child;
		});
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_Children.emplace_back(child);
}

void dae::GameObject::SetLocalPosition(const glm::vec3& position)
{
	m_Transform->SetLocalPosition(position.x, position.y, 0.f);
	SetPositionDirty();
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;
	for (GameObject* go : m_Children)
	{
		go->SetPositionDirty();
	}
}

void dae::GameObject::UpdateWorldPosition()
{
	if(m_PositionIsDirty)
	{
		if (m_Parent == nullptr)
		{
			auto localPosition = m_Transform->GetLocalPosition();
			m_Transform->SetWorldPosition(localPosition.x, localPosition.y, 0.f);
		}
		else
		{
			auto newWorldPosition = m_Parent->GetWorldPosition() + m_Transform->GetLocalPosition();
			m_Transform->SetWorldPosition(newWorldPosition.x, newWorldPosition.y, 0.f);
		}
		m_PositionIsDirty = false;
	}
}

bool dae::GameObject::IsChild(GameObject* child)
{
	for (GameObject* go : m_Children)
	{
		if (go == child) return true;
	}

	return false;
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	UpdateWorldPosition();
	return m_Transform->GetWorldPosition();
}

dae::TransformComponent* dae::GameObject::GetTransform()
{
	UpdateWorldPosition();
	return m_Transform;
}
