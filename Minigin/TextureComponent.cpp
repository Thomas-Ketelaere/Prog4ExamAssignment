#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(GameObject* gameObject, const std::string& fullPath):
	Component(gameObject)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fullPath);
}

void dae::TextureComponent::Render() const
{
	const auto& transform = GetTransform()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, transform.x, transform.y);
}
