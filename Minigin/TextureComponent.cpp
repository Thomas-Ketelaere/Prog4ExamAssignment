#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(GameObject* gameObject, const std::string& fullPath, bool useCustomPosition) :
	Component(gameObject),
	m_UseCustomPosition{ useCustomPosition },
	m_CustomPosition{}
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fullPath);
}

void dae::TextureComponent::Render() const
{
	if (m_UseCustomPosition)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_CustomPosition.x, m_CustomPosition.y);
	}
	else
	{
		const auto& transform = GetTransform()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, transform.x, transform.y);
	}
	
}
