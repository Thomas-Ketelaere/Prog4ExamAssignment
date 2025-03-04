#pragma once
#include "Component.h"
#include <glm.hpp>

namespace dae
{
	class MovementComponent final : public Component
	{
	public:
		MovementComponent(GameObject* gameObject);

		virtual void Start() override;
		virtual void Update() override;


		void SetSpeed(float newSpeedX, float newSpeedY);
		void SetRotation(float newRotationSpeed, float rotationPositionX, float rotationPositionY);
		void SetRotationPoint(float rotationPositionX, float rotationPositionY);
		void CalculateRadiusAndAngle();

		void ActivateMove(bool activate) { m_Move = activate; }
		void ActivateRotate(bool activate) { m_Rotate = activate; };

		void InputMovement(float horizontal, float vertical);

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

