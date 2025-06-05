#include "ButtonsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "SceneManager.h"
#include "GameManager.h"

game::ButtonsComponent::ButtonsComponent(RamCoreEngine::GameObject* gameObject, uint8_t smallFontSize, uint8_t bigFontSize, unsigned int startIndex, std::vector<std::string> sceneNamesToLoad):
	Component(gameObject),
	m_SmallFontSize{smallFontSize},
	m_BigFontSize{bigFontSize},
	m_Index{startIndex}
{
	auto textComps = GetGameObject()->GetAllComponents<RamCoreEngine::TextComponent>();
	for (unsigned int compCounter{}; compCounter < textComps.size(); ++compCounter)
	{
		m_pTextComponents.emplace_back(std::make_pair(textComps[compCounter], sceneNamesToLoad[compCounter]));
	}
}

void game::ButtonsComponent::Start()
{
	for (auto& textComp : m_pTextComponents)
	{
		textComp.first->ChangeFontSize(m_SmallFontSize);
	}

	m_pTextComponents[m_Index].first->ChangeFontSize(m_BigFontSize);
}

void game::ButtonsComponent::ChangeIndex(bool up)
{
	if (up)
	{
		++m_Index;
	}
	else
	{
		if (m_Index == 0)
		{
			m_Index = int(m_pTextComponents.size() - 1);
		}
		else
		{
			--m_Index;
		}
		
	}

	if (m_Index == m_pTextComponents.size())
	{
		m_Index = 0;
	}

	for (auto& textComp : m_pTextComponents)
	{
		textComp.first->ChangeFontSize(m_SmallFontSize);
	}

	m_pTextComponents[m_Index].first->ChangeFontSize(m_BigFontSize);
}

void game::ButtonsComponent::ButtonPressed()
{
	if (m_Index == 0)
	{
		GameManager::GetInstance().SetGameMode(GameMode::Single);
	}
	else if (m_Index == 1)
	{
		GameManager::GetInstance().SetGameMode(GameMode::Coop);
	}
	else if (m_Index == 2)
	{
		GameManager::GetInstance().SetGameMode(GameMode::Versus);
	}
	std::string& sceneNameToLoad = m_pTextComponents[m_Index].second;
	RamCoreEngine::SceneManager::GetInstance().LoadScene(sceneNameToLoad);
}
