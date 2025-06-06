#include "ButtonsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "SceneManager.h"
#include "GameManager.h"
#include <Hash.h>

game::ButtonsComponent::ButtonsComponent(RamCoreEngine::GameObject* gameObject, uint8_t smallFontSize, uint8_t bigFontSize, unsigned int startIndex):
	Component(gameObject),
	m_SmallFontSize{smallFontSize},
	m_BigFontSize{bigFontSize},
	m_Index{startIndex}
{
	auto textComps = GetGameObject()->GetAllComponents<RamCoreEngine::TextComponent>();
	for (size_t compCounter{}; compCounter < textComps.size(); ++compCounter)
	{
		m_pTextComponents.emplace_back(textComps[compCounter]);
	}
}

void game::ButtonsComponent::Start()
{
	for (auto& textComp : m_pTextComponents)
	{
		textComp->ChangeFontSize(m_SmallFontSize);
	}

	m_pTextComponents[m_Index]->ChangeFontSize(m_BigFontSize);
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
			m_Index = static_cast<int>(m_pTextComponents.size()) - 1;
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
		textComp->ChangeFontSize(m_SmallFontSize);
	}

	m_pTextComponents[m_Index]->ChangeFontSize(m_BigFontSize);
}

void game::ButtonsComponent::ButtonPressed()
{
	if (m_Index == 0)
	{
		GameManager::GetInstance().SetGameMode(GameMode::Single);
		RamCoreEngine::SceneManager::GetInstance().LoadScene(make_sdbm_hash("LoadingScreen"));
	}
	else if (m_Index == 1)
	{
		GameManager::GetInstance().SetGameMode(GameMode::Coop);
		RamCoreEngine::SceneManager::GetInstance().LoadScene(make_sdbm_hash("LoadingScreen"));
	}
	else if (m_Index == 2)
	{
		GameManager::GetInstance().SetGameMode(GameMode::Versus);
		RamCoreEngine::SceneManager::GetInstance().LoadScene(make_sdbm_hash("LoadingScreen"));
	}
	else if (m_Index == 3)
	{
		RamCoreEngine::SceneManager::GetInstance().LoadScene(make_sdbm_hash("HighScoreScreen"));
	}
}
