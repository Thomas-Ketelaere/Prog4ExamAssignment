#pragma once
#include "Component.h"
#include <glm.hpp>

namespace game
{
	class MovementComponent final : public RamCoreEngine::Component
	{
	public:
		MovementComponent(RamCoreEngine::GameObject* gameObject);
		~MovementComponent() = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

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

