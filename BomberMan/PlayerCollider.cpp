#include "PlayerCollider.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "Hash.h"
#include "Renderer.h"
#include <Events.h>

game::PlayerCollider::PlayerCollider(RamCoreEngine::GameObject* gameObject, const float width, const float height, bool isTrigger) :
	Component(gameObject),
	Collider(gameObject, width, height, isTrigger),
	m_pLivesComponent{}
{
	
}

void game::PlayerCollider::Start()
{
	m_pLivesComponent = GetGameObject()->GetComponent<LivesComponent>();
}

void game::PlayerCollider::Render() const
{
	if (m_DebugRender)
	{
		glm::vec3 pos = GetTransform()->GetWorldPosition();
		SDL_Color color = { 0, 0, 255, 255 };
		RamCoreEngine::Renderer::GetInstance().DrawRectangle(pos.x, pos.y, RamCoreEngine::Collider::GetColliderWidth(), GetColliderHeight(), color);
	}
}


void game::PlayerCollider::OnTriggerOverlap(Collider* other)
{
	if (other->GetTag() == make_sdbm_hash("Enemy"))
	{
		m_pLivesComponent->LoseLive();
	}
}
