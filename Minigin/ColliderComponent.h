#pragma once
#include <glm.hpp>
#include "Component.h"

namespace dae
{
	class ColliderComponent final : public Component
	{
	public:
		ColliderComponent(GameObject* gameObject, const float width, const float height);

		virtual void Render() const override;

		bool IsColliding(const glm::vec2& objectPos, const float width, const float height);
		bool IsColliding(ColliderComponent* other);

		float GetColliderWidth() { return m_Width; }
		float GetColliderHeight() { return m_Height; }

		void SetDebugRendering(bool shouldRender) { m_DebugRender = shouldRender; }
	private:
		const float m_Width;
		const float m_Height;

		bool m_DebugRender{};
	};
}

