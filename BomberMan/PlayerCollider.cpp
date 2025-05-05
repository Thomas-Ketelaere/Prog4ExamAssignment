#include "PlayerCollider.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "Hash.h"
#include "Renderer.h"
#include <Events.h>

dae::PlayerCollider::PlayerCollider(GameObject* gameObject, const float width, const float height, bool isTrigger) :
	Component(gameObject),
	Collider(gameObject, width, height, isTrigger),
	m_pLivesComponent{}
{
	
}

void dae::PlayerCollider::Start()
{
	m_pLivesComponent = GetGameObject()->GetComponent<LivesComponent>();
}

void dae::PlayerCollider::Render() const
{
	if (m_DebugRender)
	{
		glm::vec3 pos = GetTransform()->GetWorldPosition();
		SDL_Color color = { 0, 0, 255, 255 };
		Renderer::GetInstance().DrawRectangle(pos.x, pos.y, dae::Collider::GetColliderWidth(), GetColliderHeight(), color);
	}
}


void dae::PlayerCollider::OnTriggerOverlap(Collider* other)
{
	if (other->GetTag() == make_sdbm_hash("Enemy"))
	{
		m_pLivesComponent->LoseLive();
	}
}
