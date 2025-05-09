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
	class HandleUIComponent final : public RamCoreEngine::Component
	{
	public:
		HandleUIComponent(RamCoreEngine::GameObject* gameObject, uint8_t smallFontSize, uint8_t bigFontSize, unsigned int startIndex, std::vector<std::string> sceneNamesToLoad); //TODO: make hash map for scenes

		void Start() override;

		void ChangeIndex(bool up);
		void ButtonPressed();
	private:
		std::vector < std::pair< RamCoreEngine::TextComponent*, std::string>> m_pTextComponents;
		uint8_t m_SmallFontSize;
		uint8_t m_BigFontSize;
		unsigned int m_Index;
	};
}


