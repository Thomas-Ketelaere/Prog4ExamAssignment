#include "MovementComponent.h"
#include "Transform.h"
#include "Time.h"
#define _USE_MATH_DEFINES
#include "math.h"


dae::MovementComponent::MovementComponent()
{
}

void dae::MovementComponent::Start()
{
	m_Radius = glm::distance(m_RotationPoint, GetTransform()->GetWorldPosition());
}

void dae::MovementComponent::Update()
{
	if (m_Move)
	{
		UpdatePosition();
	}

	if (m_Rotate)
	{
		UpdateRotation();
	}
}

void dae::MovementComponent::SetSpeed(float newSpeedX, float newSpeedY)
{
	m_SpeedX = newSpeedX;
	m_SpeedY = newSpeedY;

	m_Move = true;
}

void dae::MovementComponent::SetRotationSpeed(float newRotationSpeed, glm::vec3& newRotationPoint)
{
	m_RotationSpeed = newRotationSpeed;
	m_RotationPoint = newRotationPoint;
	m_Rotate = true;
}

void dae::MovementComponent::UpdatePosition()
{
	const float deltaTime = Time::GetInstance().m_DeltaTime;
	//glm::uvec3 newPosition{ GetTransform()->GetPosition() }; conversion problems
	float xPos = GetTransform()->GetWorldPosition().x;
	float yPos = GetTransform()->GetWorldPosition().y;
	xPos += m_SpeedX * deltaTime;
	yPos += m_SpeedY * deltaTime;
	GetTransform()->SetWorldPosition(xPos, yPos, 0);

}

void dae::MovementComponent::UpdateRotation()
{
	m_Angle += m_RotationSpeed * Time::GetInstance().m_DeltaTime;

	if (m_Angle > 2.f * float(M_PI))
	{
		m_Angle -= 2.f * float(M_PI);
	}

	const glm::vec3 newPosition {m_RotationPoint.x + m_Radius * cos(m_Angle), m_RotationPoint.y + m_Radius * sin(m_Angle), 0};
	GetTransform()->SetLocalPosition(newPosition.x, newPosition.y, 0.f);
}
