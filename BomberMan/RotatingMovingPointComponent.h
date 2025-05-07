#pragma once
#include "Component.h"

namespace game
{
	class MovementComponent;
	class RotatingMovingPointComponent final : public RamCoreEngine::Component
	{
	public:
		RotatingMovingPointComponent(RamCoreEngine::GameObject* gameObject);

		virtual void Start() override;
		virtual void Update() override;

	private:
		MovementComponent* m_MovementComponent = nullptr;
		RamCoreEngine::GameObject* m_Parent{ nullptr };
	};
}

