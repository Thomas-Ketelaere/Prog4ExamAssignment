#include "OnScreenKeyboardComponent.h"
#include <glm.hpp>
#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include <Subject.h>

game::OnScreenKeyboardComponent::OnScreenKeyboardComponent(RamCoreEngine::GameObject* gameObject, int columns, int rows, int offsetX, int offsetY, uint8_t smallFontSize, uint8_t bigFontSize) :
	Component(gameObject),
	m_BigFontSize{bigFontSize},
	m_SmallFontSize{smallFontSize},
	m_Index{},
	m_Columns{columns},
	m_Rows{rows},
	m_OffsetX{offsetX},
	m_OffsetY{offsetY}
{
	for (char c = 'a'; c <= 'z'; ++c)
	{
		m_Alphabet.emplace_back(c);
	}

	m_pNameChangedEvent = std::make_unique<RamCoreEngine::Subject>();
}

void game::OnScreenKeyboardComponent::Start()
{
	float currentOffsetHorizontal = -(m_Columns * m_OffsetX / 2.f); // columns * offset for full length, /2 so 0 is center and make it negative to have left side
	float currentOffsetVertical = -(m_Rows * m_OffsetY / 2.f); // rows * offset for full length, /2 so 0 is center and make it negative to have top side

	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	glm::vec2 worldPos = GetGameObject()->GetWorldPosition();

	if (static_cast<int>(m_Alphabet.size()) > m_Columns * m_Rows)
	{
		throw std::runtime_error("too many places for the aplhabet");
	}

	for (int rowCounter{}; rowCounter < m_Rows; ++rowCounter)
	{
		for (int columnCounter{}; columnCounter < m_Columns; ++columnCounter)
		{
			glm::vec2 customPos{ currentOffsetHorizontal, currentOffsetVertical };
			int index = rowCounter * m_Columns + columnCounter;
			std::string letter{ m_Alphabet[index] };
			auto textComp = std::make_unique<RamCoreEngine::TextComponent>(GetGameObject(), letter, font, true);
			textComp->SetCustomPosition(customPos);
			m_pLetters.emplace_back(textComp.get());
			GetGameObject()->AddComponent(std::move(textComp));
			currentOffsetHorizontal += m_OffsetX;
		}

		currentOffsetVertical += m_OffsetY;
		currentOffsetHorizontal = -(m_Columns * m_OffsetX / 2.f);
	}


	for (auto& textComp : m_pLetters)
	{
		textComp->ChangeFontSize(m_SmallFontSize);
	}

	m_pLetters[m_Index]->ChangeFontSize(m_BigFontSize);
}

void game::OnScreenKeyboardComponent::ButtonPressed(bool shouldRemove) 
{
	if (shouldRemove)
	{
		GameManager::GetInstance().RemoveLetterFromName();
	}
	else
	{
		GameManager::GetInstance().AddLetterToName(m_Alphabet[m_Index]);
	}
	
	Event e(make_sdbm_hash("NameChanged"));
	m_pNameChangedEvent->NotifyObservers(e, GetGameObject());
}

void game::OnScreenKeyboardComponent::ChangeSelected(glm::vec2 direction)
{
	int currentRow = m_Index / m_Columns;
	int currentCol = m_Index % m_Columns;

	currentCol += static_cast<int>(direction.x);
	currentRow += static_cast<int>(direction.y);

	if (currentCol >= m_Columns)
	{
		currentCol = 0;
	}
	else if (currentCol < 0)
	{
		currentCol = m_Columns - 1;
	}
	else if (currentRow >= m_Rows)
	{
		currentRow = 0;
	}
	else if(currentRow < 0)
	{
		currentRow = m_Rows - 1;
	}
	int newIndex = currentRow * m_Columns + currentCol;
	m_pLetters[m_Index]->ChangeFontSize(m_SmallFontSize);
	m_Index = newIndex;
	m_pLetters[m_Index]->ChangeFontSize(m_BigFontSize);
}
