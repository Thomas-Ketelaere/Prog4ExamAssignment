#include "BaseColliderComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"

RamCoreEngine::BaseColliderComponent::BaseColliderComponent(GameObject* gameObject, const float width, const float height, bool isTrigger) :
	Component(gameObject),
	Collider(gameObject, width, height, isTrigger)
{

}

void RamCoreEngine::BaseColliderComponent::Render() const
{
	if (m_DebugRender)
	{
		glm::vec3 pos = GetTransform()->GetWorldPosition();
		SDL_Color color = { 0, 0, 255, 255 };
		Renderer::GetInstance().DrawRectangle(pos.x, pos.y, RamCoreEngine::Collider::GetColliderWidth(), GetColliderHeight(), color);
	}
}
