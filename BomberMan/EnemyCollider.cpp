#include "EnemyCollider.h"
#include "Hash.h"
#include "EnemyMovementComponent.h"
#include "GameObject.h"

game::EnemyCollider::EnemyCollider(RamCoreEngine::GameObject* gameObject, const float width, const float height, bool isTrigger):
	Component(gameObject),
	Collider(gameObject, width, height, isTrigger)
{
}

void game::EnemyCollider::OnTriggerOverlap(Collider* other)
{
	if (other->GetTag() == make_sdbm_hash("Explosion"))
	{
		GetGameObject()->GetComponent<EnemyMovementComponent>()->StartDying();
	}
}
