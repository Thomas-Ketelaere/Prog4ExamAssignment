#include "PlayerSpriteComponent.h"
#include "GameObject.h"
#include "SpriteSheetComponent.h"

#include "Renderer.h" //TODO: remove after testing
#include "LivesComponent.h"

dae::PlayerSpriteComponent::PlayerSpriteComponent(GameObject* gameObject):
	Component(gameObject)
{

}

void dae::PlayerSpriteComponent::Start()
{
	m_pSpriteSheetComponent = GetGameObject()->GetComponent<SpriteSheetComponent>();
}

void dae::PlayerSpriteComponent::Render() const//TODO: remove after testing
{
	//glm::vec3 pos = GetTransform()->GetWorldPosition();
	//SDL_Color color = { 0, 0, 255, 255 };
	//Renderer::GetInstance().DrawRectangle(pos.x, pos.y, 32, 32, color);
}

void dae::PlayerSpriteComponent::Update()
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

int dae::PlayerSpriteComponent::GetWidthSprite() const
{
	return m_pSpriteSheetComponent->GetWidthSprite();
}

int dae::PlayerSpriteComponent::GetHeightSprite() const
{
	return m_pSpriteSheetComponent->GetHeightSprite();
}

void dae::PlayerSpriteComponent::SetDirectionSprite(glm::vec2 direction)
{
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

void dae::PlayerSpriteComponent::StartDying()
{
	if (!m_IsDying)
	{
		m_IsDying = true;
		//play dead animation
		GetGameObject()->GetComponent<LivesComponent>()->LoseLive();
	}
}
