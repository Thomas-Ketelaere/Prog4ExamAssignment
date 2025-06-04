#pragma once
#include "Component.h"
#include <string>
#include <vector>

namespace RamCoreEngine
{
	class TextComponent;
}

namespace game
{
	class HighScoresTextComponent final : public RamCoreEngine::Component
	{
	public:
		HighScoresTextComponent(RamCoreEngine::GameObject* gameObject, const std::string& saveFileName, float offsetYBetween);

	private:
		std::vector<RamCoreEngine::TextComponent*> m_pHighScoreTexts;
		const size_t m_MaxPlayersInFile{ 5 };
	};
}


