#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Time.h"
#include "Component.h"
#include <memory>

RamCoreEngine::GameObject::GameObject()
{
	auto tempTransform = std::make_unique<TransformComponent>(this);
	m_Transform = tempTransform.get();
	AddComponent(std::move(tempTransform));
}

RamCoreEngine::GameObject::~GameObject()
{
	SetParent(nullptr, false);
	for (GameObject* child : m_Children)
	{
		child->SetParent(nullptr, false);
	}
}

void RamCoreEngine::GameObject::Start()
{
	for (std::unique_ptr<Component>& component : m_ComponentsVector)
	{
		component->Start();
	}
}

void RamCoreEngine::GameObject::Update()
{
	for (std::unique_ptr<Component>& component : m_ComponentsVector)
	{
		component->Update();
	}
}

void RamCoreEngine::GameObject::LateUpdate()
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

void RamCoreEngine::GameObject::Render() const
{
	for (const std::unique_ptr<Component>& component : m_ComponentsVector)
	{
		component->Render();
	}
}

void RamCoreEngine::GameObject::AddComponent(std::unique_ptr<Component> newComponent)
{
	m_ComponentsVector.emplace_back(std::move(newComponent));
}


void RamCoreEngine::GameObject::SetWorldPosition(float x, float y)
{
	m_Transform->SetWorldPosition(x, y, 0.0f);
}

void RamCoreEngine::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
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

void RamCoreEngine::GameObject::RemoveChild(GameObject* child)
{
	std::erase_if(m_Children, [&](GameObject* go)
		{ 
			return go == child;
		});
}

void RamCoreEngine::GameObject::AddChild(GameObject* child)
{
	m_Children.emplace_back(child);
}

void RamCoreEngine::GameObject::SetLocalPosition(const glm::vec3& position)
{
	m_Transform->SetLocalPosition(position.x, position.y, 0.f);
	SetPositionDirty();
}

void RamCoreEngine::GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;
	for (GameObject* go : m_Children)
	{
		go->SetPositionDirty();
	}
}

void RamCoreEngine::GameObject::UpdateWorldPosition()
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

bool RamCoreEngine::GameObject::IsChild(GameObject* child)
{
	for (GameObject* go : m_Children)
	{
		if (go == child) return true;
	}

	return false;
}

const glm::vec3& RamCoreEngine::GameObject::GetWorldPosition()
{
	UpdateWorldPosition();
	return m_Transform->GetWorldPosition();
}

RamCoreEngine::TransformComponent* RamCoreEngine::GameObject::GetTransform()
{
	UpdateWorldPosition();
	return m_Transform;
}
