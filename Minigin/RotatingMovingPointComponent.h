#pragma once
#include "Component.h"

namespace dae
{
	class MovementComponent;
	class RotatingMovingPointComponent final : public Component
	{
	public:
		RotatingMovingPointComponent(GameObject* gameObject);

		virtual void Start() override;
		virtual void Update() override;

	private:
		MovementComponent* m_MovementComponent = nullptr;
		GameObject* m_Parent{ nullptr };
	};
}

