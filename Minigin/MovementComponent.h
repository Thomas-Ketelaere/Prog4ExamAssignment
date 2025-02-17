#pragma once
#include "Component.h"
#include <glm.hpp>

namespace dae
{
	class MovementComponent final : public Component
	{
	public:
		MovementComponent();

		virtual void Start() override;
		virtual void Update() override;


		void SetSpeed(float newSpeedX, float newSpeedY);
		void SetRotationSpeed(float newRotationSpeed, glm::vec3& newRotationPoint);

	private:
		void UpdatePosition();
		void UpdateRotation();

		float m_SpeedX{};
		float m_SpeedY{};

		glm::vec3 m_RotationPoint{};
		float m_RotationSpeed{};
		float m_Radius{};
		float m_Angle{};

		bool m_Move{};
		bool m_Rotate{};


	};
}

