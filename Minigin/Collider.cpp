#include "Collider.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "ColliderManager.h"
#include "GameObject.h"

dae::Collider::Collider(GameObject* gameObject, const float width, const float height, bool isTrigger):
	m_Width{width},
	m_Height{height},
	m_Trigger{isTrigger}
{
	ColliderManager::GetInstance().AddCollider(this);
	m_pTransformComponent = gameObject->GetTransform(); //all gameobjects have a transform
}

bool dae::Collider::IsColliding(const glm::vec2& objectPos, const float width, const float height)
{
	glm::vec2 colliderPos = glm::vec2(m_pTransformComponent->GetWorldPosition());

	float colliderLeft = colliderPos.x - m_Width / 2;
	float colliderRight = colliderPos.x + m_Width / 2;
	float colliderTop = colliderPos.y - m_Height / 2;
	float colliderBottom = colliderPos.y + m_Height / 2;

	float objectLeft = objectPos.x - width / 2;
	float objectRight = objectPos.x + width / 2;
	float objectTop = objectPos.y - height / 2;
	float objectBottom = objectPos.y + height / 2;

	bool isOverlapping = !(colliderRight < objectLeft || colliderLeft > objectRight || colliderBottom < objectTop || colliderTop > objectBottom);

	return isOverlapping;
}

bool dae::Collider::IsColliding(Collider* other)
{
	const glm::vec2 otherPos = other->GetColliderTransform()->GetWorldPosition();
	const float otherWidth = other->GetColliderWidth();
	const float otherHeight = other->GetColliderHeight();
	return IsColliding(otherPos, otherWidth, otherHeight);
}

unsigned int dae::Collider::GetTag()
{
	return GetColliderTransform()->GetGameObject()->GetTag();
}
