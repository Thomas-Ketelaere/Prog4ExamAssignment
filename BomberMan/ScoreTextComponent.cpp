#include "ScoreTextComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "GameManager.h"

game::ScoreTextComponent::ScoreTextComponent(RamCoreEngine::GameObject* gameObject):
	Component(gameObject)
{
}

void game::ScoreTextComponent::Start()
{
	m_TextComponent = GetGameObject()->GetComponent<RamCoreEngine::TextComponent>();
}

void game::ScoreTextComponent::Notify(Event event, RamCoreEngine::GameObject*)
{
	if (event.id == make_sdbm_hash("EnemyDied"))
	{
		int newScore = game::GameManager::GetInstance().GetTotalScore();
		m_TextComponent->ChangeText(std::to_string(newScore));
	}
}
