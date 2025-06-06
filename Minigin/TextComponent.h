#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include <glm.hpp>

namespace RamCoreEngine
{
	class Font;
	class Texture2D;
	class TextComponent final : public Component
	{
	public:
		TextComponent(GameObject* gameObject, const std::string& text, Font* font, bool useCustomPosition = false);
		~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
		
		virtual void Update() override;
		virtual void Render() const override;

		void ChangeText(const std::string& newText);
		void ChangeFontSize(uint8_t newSize);

		void SetCustomPosition(const glm::vec2 customPosition) { m_CustomPosition = customPosition; }

	private:
		Font* m_Font;
		std::unique_ptr<Texture2D> m_TextTexture;
		glm::vec2 m_CustomPosition;
		std::string m_Text;
		bool m_NeedsUpdate;
		bool m_UseCustomPosition;
	};
}


