#include "LivesTextComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "GameManager.h"

game::LivesTextComponent::LivesTextComponent(RamCoreEngine::GameObject* gameObject):
	Component(gameObject)
{
}

void game::LivesTextComponent::Start()
{
	m_TextComponent = GetGameObject()->GetComponent<RamCoreEngine::TextComponent>();
}

void game::LivesTextComponent::Notify(Event event, RamCoreEngine::GameObject*)
{
	if (event.id == make_sdbm_hash("PlayerDied"))
	{
		int newLives = GameManager::GetInstance().GetTotalLives();
		m_TextComponent->ChangeText("Lives: " + std::to_string(newLives));
	}
	
}

