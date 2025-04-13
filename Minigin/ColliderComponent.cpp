#include "ColliderComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"

dae::ColliderComponent::ColliderComponent(GameObject* gameObject, const float width, const float height):
	Component(gameObject),
	m_Width{width},
	m_Height{height}
{
}

void dae::ColliderComponent::Render() const
{
	if (m_DebugRender)
	{
		glm::vec3 pos = GetTransform()->GetWorldPosition();
		SDL_Color color = { 0, 0, 255, 255 };
		Renderer::GetInstance().DrawRectangle(pos.x, pos.y, m_Width, m_Height, color);
	}
}

bool dae::ColliderComponent::IsColliding(const glm::vec2& objectPos, const float width, const float height)
{

	glm::vec2 colliderPos = glm::vec2(GetTransform()->GetWorldPosition());

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
