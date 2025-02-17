#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(const std::string& fullPath)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fullPath);
}

void dae::TextureComponent::Render() const
{
	const auto& transform = GetTransform()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, transform.x, transform.y);
}
