#pragma once
#include "Component.h"
#include <glm.hpp>
#include <vector>

namespace dae
{
	class GridComponent;
	class EnemyMovementComponent final : public Component
	{
	public:
		EnemyMovementComponent(GameObject* gameObject, const float speed);

		virtual void Start() override;
		virtual void Update() override;

		virtual void Render() const override;

		void SetDebugRendering(bool shouldDebugRender) { m_DebugRender = shouldDebugRender; }

	private:
		GridComponent* m_pGridComponent;
		std::vector<glm::vec2> m_Path;

		const float m_Speed;
		const float m_DistanceToReachPoint{ 2.f };

		int m_PathIndex{};

		bool m_DebugRender{};
	};

}


