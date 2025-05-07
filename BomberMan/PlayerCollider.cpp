#include "PlayerCollider.h"
#include "GameObject.h"
#include "GameManager.h"
#include "Hash.h"
#include "Renderer.h"
#include <Events.h>

game::PlayerCollider::PlayerCollider(RamCoreEngine::GameObject* gameObject, const float width, const float height, bool isTrigger) :
	Component(gameObject),
	Collider(gameObject, width, height, isTrigger)
{
	
}

void game::PlayerCollider::Start()
{
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
		GameManager::GetInstance().LoseLive();
	}
}
