#pragma once
#include "Component.h"
#include <glm.hpp>
#include <vector>
#include <memory>
#include <string>

namespace dae
{
	class GridComponent;
	class SpriteSheetComponent;
	class Subject;
	class EnemyMovementComponent final : public Component
	{
	public:
		EnemyMovementComponent(GameObject* gameObject, const float speed, const std::string& name);

		virtual void Start() override;
		virtual void Update() override;
		virtual void Render() const override;

		void StartDying();
		void SetDebugRendering(bool shouldDebugRender) { m_DebugRender = shouldDebugRender; }

		Subject* GetEnemyDiedSubject() const { return m_pEnemyDiedEvent.get(); }

	private:
		void SetSpriteDirection();
		std::unique_ptr<Subject> m_pEnemyDiedEvent;
		SpriteSheetComponent* m_pSpriteSheetComponent = nullptr;
		GridComponent* m_pGridComponent = nullptr;
		std::vector<glm::vec2> m_Path;
		const std::string m_Name{};

		const float m_Speed;
		const float m_DistanceToReachPoint{ 2.f };

		unsigned int m_PathIndex{};

		bool m_DebugRender{};
		bool m_IsDying{};
	};

}


