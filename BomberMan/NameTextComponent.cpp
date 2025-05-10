#include "NameTextComponent.h"
#include "GameManager.h"
#include "GameObject.h"
#include "TextComponent.h"

game::NameTextComponent::NameTextComponent(RamCoreEngine::GameObject* gameObject):
	Component(gameObject)
{
	
}

void game::NameTextComponent::Start()
{
	m_TextComponent = GetGameObject()->GetComponent<RamCoreEngine::TextComponent>();
}

void game::NameTextComponent::Notify(Event event, RamCoreEngine::GameObject* ) 
{
	if (event.id == make_sdbm_hash("NameChanged"))
	{
		std::string newName = game::GameManager::GetInstance().GetName();
		m_TextComponent->ChangeText(newName);

	}
}
