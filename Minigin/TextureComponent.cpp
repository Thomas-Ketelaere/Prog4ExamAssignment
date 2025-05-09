#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

RamCoreEngine::TextureComponent::TextureComponent(GameObject* gameObject, const std::string& fullPath, bool useCustomPosition) :
	Component(gameObject),
	m_UseCustomPosition{ useCustomPosition },
	m_CustomPosition{}
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fullPath);
}

void RamCoreEngine::TextureComponent::Render() const
{
	if (m_UseCustomPosition)
	{
		const auto& worldPos = GetTransform()->GetWorldPosition();
		glm::vec2 pos{};
		pos.x = m_CustomPosition.x + worldPos.x;
		pos.y = m_CustomPosition.y + worldPos.y;
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
	else
	{
		const auto& worldPos = GetTransform()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, worldPos.x, worldPos.y);
	}
	
}
