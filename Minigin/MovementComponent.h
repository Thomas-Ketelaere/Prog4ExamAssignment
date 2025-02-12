#pragma once
#include "Component.h"

namespace dae
{
	class MovementComponent final : public Component
	{
	public:
		MovementComponent(float speedX, float speedY);

		virtual void Update() override;

		void SetSpeed(float newSpeedX, float newSpeedY);

	private:
		float m_SpeedX;
		float m_SpeedY;

	};
}

