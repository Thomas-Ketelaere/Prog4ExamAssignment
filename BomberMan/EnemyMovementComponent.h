#pragma once
#include "Component.h"
#include <glm.hpp>
#include <vector>

namespace dae
{
	class GridComponent;
	class SpriteSheetComponent;
	class EnemyMovementComponent final : public Component
	{
	public:
		EnemyMovementComponent(GameObject* gameObject, const float speed);

		virtual void Start() override;
		virtual void Update() override;

		virtual void Render() const override;

		void StartDying();

		void SetDebugRendering(bool shouldDebugRender) { m_DebugRender = shouldDebugRender; }

	private:
		void SetSpriteDirection();

		SpriteSheetComponent* m_pSpriteSheetComponent = nullptr;
		GridComponent* m_pGridComponent = nullptr;
		std::vector<glm::vec2> m_Path;

		const float m_Speed;
		const float m_DistanceToReachPoint{ 2.f };

		unsigned int m_PathIndex{};

		bool m_DebugRender{};
		bool m_IsDying{};
	};

}


