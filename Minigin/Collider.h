#pragma once
#include <glm.hpp>


namespace dae
{
	class GameObject;
	class TransformComponent;
	class Collider
	{
	public:
		Collider(GameObject* gameObject, const float width, const float height, bool isTrigger);

		virtual void OnTriggerOverlap(Collider* other) = 0;

		bool IsColliding(const glm::vec2& objectPos, const float width, const float height);
		bool IsColliding(Collider* other);

		float GetColliderWidth() const { return m_Width; }
		float GetColliderHeight() const { return m_Height; }
		const TransformComponent* GetColliderTransform() { return m_pTransformComponent; }
		unsigned int GetTag();

		bool IsTrigger() { return m_Trigger; }

	private:
		TransformComponent* m_pTransformComponent;

		const float m_Width;
		const float m_Height;

		bool m_Trigger;
	};
}

