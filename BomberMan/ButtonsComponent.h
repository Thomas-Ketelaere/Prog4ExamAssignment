#pragma once 
#include "Component.h"
#include <vector>
#include "string"

namespace RamCoreEngine
{
	class TextComponent;
}

namespace game
{
	class ButtonsComponent final : public RamCoreEngine::Component
	{
	public:
		ButtonsComponent(RamCoreEngine::GameObject* gameObject, uint8_t smallFontSize, uint8_t bigFontSize, unsigned int startIndex); 
		~ButtonsComponent() = default;
		ButtonsComponent(const ButtonsComponent& other) = delete;
		ButtonsComponent(ButtonsComponent&& other) = delete;
		ButtonsComponent& operator=(const ButtonsComponent& other) = delete;
		ButtonsComponent& operator=(ButtonsComponent&& other) = delete;

		void Start() override;

		void ChangeIndex(bool up);
		void ButtonPressed();
	private:
		std::vector<RamCoreEngine::TextComponent*> m_pTextComponents;
		uint8_t m_SmallFontSize;
		uint8_t m_BigFontSize;
		unsigned int m_Index;
	};
}


