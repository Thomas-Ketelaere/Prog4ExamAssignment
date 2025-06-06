#include "PlayerSpriteComponent.h"
#include "GameObject.h"
#include "SpriteSheetComponent.h"
#include "GameManager.h"
#include "Timer.h"

game::PlayerSpriteComponent::PlayerSpriteComponent(RamCoreEngine::GameObject* gameObject, float timeToDie):
	Component(gameObject),
	m_TimeToDie{timeToDie}
{

}

void game::PlayerSpriteComponent::Start()
{
	m_pSpriteSheetComponent = GetGameObject()->GetComponent<RamCoreEngine::SpriteSheetComponent>();
}
void game::PlayerSpriteComponent::Update()
{
	if (!m_IsDying)
	{
		if (m_Move)
		{
			m_pSpriteSheetComponent->ShouldAnimate(true);
			m_Move = false; // gets overriden if a button gets pressed and so it will animate again
		}

		else
		{
			m_pSpriteSheetComponent->ShouldAnimate(false);
			m_pSpriteSheetComponent->SetColumn(3);
		}
	}
	else
	{
		m_AccumulatedTime += RamCoreEngine::Time::GetInstance().m_DeltaTime;
		if (m_AccumulatedTime >= m_TimeToDie)
		{
			game::GameManager::GetInstance().LoseLive();
		}
	}
}

int game::PlayerSpriteComponent::GetWidthSprite() const
{
	return m_pSpriteSheetComponent->GetWidthSprite();
}

int game::PlayerSpriteComponent::GetHeightSprite() const
{
	return m_pSpriteSheetComponent->GetHeightSprite();
}

void game::PlayerSpriteComponent::SetDirectionSprite(glm::vec2 direction)
{
	if (m_IsDying)
	{
		return;
	}
	if (direction.y > 0)
	{
		m_pSpriteSheetComponent->SetRow(2);
	}

	else if (direction.y < 0)
	{
		m_pSpriteSheetComponent->SetRow(3);
	}

	else if (direction.x > 0)
	{
		m_pSpriteSheetComponent->SetRow(1);
	}

	else if (direction.x < 0)
	{
		m_pSpriteSheetComponent->SetRow(0);
	}

	m_Move = true;
}

void game::PlayerSpriteComponent::StartDying()
{
	if (!m_IsDying)
	{
		m_IsDying = true;
		m_pSpriteSheetComponent->Destroy();
		auto dyingSpriteSheet = std::make_unique<RamCoreEngine::SpriteSheetComponent>(GetGameObject(), "PlayerDying.png", 8, 1, 0.3f, true);
		m_pSpriteSheetComponent = dyingSpriteSheet.get();
		GetGameObject()->AddComponent(std::move(dyingSpriteSheet));
		
	}
}
