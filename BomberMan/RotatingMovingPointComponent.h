#pragma once
#include "Component.h"

namespace game
{
	class MovementComponent;
	class RotatingMovingPointComponent final : public RamCoreEngine::Component
	{
	public:
		RotatingMovingPointComponent(RamCoreEngine::GameObject* gameObject);
		~RotatingMovingPointComponent() = default;
		RotatingMovingPointComponent(const RotatingMovingPointComponent& other) = delete;
		RotatingMovingPointComponent(RotatingMovingPointComponent&& other) = delete;
		RotatingMovingPointComponent& operator=(const RotatingMovingPointComponent& other) = delete;
		RotatingMovingPointComponent& operator=(RotatingMovingPointComponent&& other) = delete;

		virtual void Start() override;
		virtual void Update() override;

	private:
		MovementComponent* m_MovementComponent = nullptr;
		RamCoreEngine::GameObject* m_Parent{ nullptr };
	};
}

