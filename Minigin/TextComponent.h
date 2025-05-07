#pragma once
#include "Component.h"
#include <string>
#include <memory>

namespace RamCoreEngine
{
	class Font;
	class Texture2D;
	class TextComponent final : public Component
	{
	public:
		TextComponent(GameObject* gameObject, const std::string& text, Font* font);
		
		virtual void Update() override;
		virtual void Render() const override;

		void ChangeText(const std::string& newText);
		void ChangeFontSize(uint8_t newSize);

	private:
		Font* m_Font;
		std::unique_ptr<Texture2D> m_TextTexture;
		std::string m_Text;
		bool m_NeedsUpdate;
	};
}


