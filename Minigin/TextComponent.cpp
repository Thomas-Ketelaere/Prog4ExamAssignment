#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "ResourceManager.h"

dae::TextComponent::TextComponent(GameObject* gameObject, const std::string& text, Font* font):
	Component(gameObject),
	m_Text{ text },
	m_Font{ std::move(font) },
	m_NeedsUpdate{ true },
	m_TextTexture(nullptr)
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_unique<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = GetTransform()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::ChangeText(const std::string& newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;

}

void dae::TextComponent::ChangeFontSize(uint8_t newSize)
{
	m_Font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", newSize);
}
