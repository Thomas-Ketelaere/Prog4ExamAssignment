#include "MovementComponent.h"
#include "Transform.h"
#include "Time.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "GameObject.h"


dae::MovementComponent::MovementComponent(GameObject* gameObject):
	Component(gameObject)
{
}

void dae::MovementComponent::Start()
{
	CalculateRadiusAndAngle();
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

void dae::MovementComponent::SetRotation(float newRotationSpeed, float rotationPositionX, float rotationPositionY)
{
	m_RotationSpeed = newRotationSpeed;
	m_RotationPoint.x = rotationPositionX;
	m_RotationPoint.y = rotationPositionY;
	m_Rotate = true;
}

void dae::MovementComponent::SetRotationPoint(float rotationPositionX, float rotationPositionY)
{
	m_RotationPoint.x = rotationPositionX; 
	m_RotationPoint.y = rotationPositionY;
	m_Rotate = true;
}

void dae::MovementComponent::CalculateRadiusAndAngle()
{

	m_Radius = glm::distance(m_RotationPoint, GetTransform()->GetWorldPosition());
	m_Angle = atan2(GetTransform()->GetWorldPosition().y - m_RotationPoint.y, GetTransform()->GetWorldPosition().x - m_RotationPoint.x);
}

void dae::MovementComponent::UpdatePosition()
{
	const float deltaTime = Time::GetInstance().m_DeltaTime;
	//glm::uvec3 newPosition{ GetTransform()->GetPosition() }; conversion problems
	float xPos = GetGameObject()->GetWorldPosition().x;
	float yPos = GetGameObject()->GetWorldPosition().y;
	xPos += m_SpeedX * deltaTime;
	yPos += m_SpeedY * deltaTime;
	m_RotationPoint.x += m_SpeedX * deltaTime;
	m_RotationPoint.y += m_SpeedY * deltaTime;
	GetGameObject()->SetWorldPosition(xPos, yPos);

}

void dae::MovementComponent::UpdateRotation()
{
	m_Angle += m_RotationSpeed * Time::GetInstance().m_DeltaTime;

	if (m_Angle > 2.f * float(M_PI))
	{
		m_Angle -= 2.f * float(M_PI);
	}

	const glm::vec3 newPosition {m_RotationPoint.x + m_Radius * cos(m_Angle), m_RotationPoint.y + m_Radius * sin(m_Angle), 0};
	GetTransform()->SetWorldPosition(newPosition.x, newPosition.y, 0.f);
	GetGameObject()->SetWorldPosition(newPosition.x, newPosition.y);
}
