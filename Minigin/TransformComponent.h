#pragma once
#include <glm.hpp>
#include "Component.h"

namespace RamCoreEngine
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* gameObject);

		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
		void SetWorldPosition(float x, float y, float z);
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void SetLocalPosition(float x, float y, float z);
	private:
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};

	};
}
