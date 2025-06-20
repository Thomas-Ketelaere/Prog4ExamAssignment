#include "MovementComponent.h"
#include "TransformComponent.h"
#include "Timer.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "GameObject.h"


game::MovementComponent::MovementComponent(RamCoreEngine::GameObject* gameObject):
	Component(gameObject)
{
}

void game::MovementComponent::Start()
{
	CalculateRadiusAndAngle();
}

void game::MovementComponent::Update()
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

void game::MovementComponent::SetSpeed(float newSpeedX, float newSpeedY)
{
	m_SpeedX = newSpeedX;
	m_SpeedY = newSpeedY;
	m_Move = true;
}

void game::MovementComponent::SetRotation(float newRotationSpeed, float rotationPositionX, float rotationPositionY)
{
	m_RotationSpeed = newRotationSpeed;
	m_RotationPoint.x = rotationPositionX;
	m_RotationPoint.y = rotationPositionY;
	CalculateRadiusAndAngle();
	m_Rotate = true;
}

void game::MovementComponent::SetRotationPoint(float rotationPositionX, float rotationPositionY)
{
	m_RotationPoint.x = rotationPositionX; 
	m_RotationPoint.y = rotationPositionY;
	CalculateRadiusAndAngle();
}

void game::MovementComponent::CalculateRadiusAndAngle()
{
	m_Radius = glm::distance(m_RotationPoint, GetTransform()->GetWorldPosition());
	m_Angle = atan2(GetTransform()->GetWorldPosition().y - m_RotationPoint.y, GetTransform()->GetWorldPosition().x - m_RotationPoint.x);
}

void game::MovementComponent::InputMovement(float horizontal, float vertical)
{
	const float deltaTime = RamCoreEngine::Time::GetInstance().m_DeltaTime;
	float xPos = GetGameObject()->GetWorldPosition().x;
	float yPos = GetGameObject()->GetWorldPosition().y;
	xPos += m_SpeedX * deltaTime * horizontal;
	yPos += m_SpeedY * deltaTime * vertical;
	m_RotationPoint.x += m_SpeedX * deltaTime;
	m_RotationPoint.y += m_SpeedY * deltaTime;
	GetGameObject()->SetLocalPosition(glm::vec3(xPos, yPos, 0.f));
}

void game::MovementComponent::UpdatePosition()
{
	const float deltaTime = RamCoreEngine::Time::GetInstance().m_DeltaTime;
	float xPos = GetGameObject()->GetWorldPosition().x;
	float yPos = GetGameObject()->GetWorldPosition().y;
	xPos += m_SpeedX * deltaTime;
	yPos += m_SpeedY * deltaTime;
	m_RotationPoint.x += m_SpeedX * deltaTime;
	m_RotationPoint.y += m_SpeedY * deltaTime;
	GetGameObject()->SetLocalPosition(glm::vec3(xPos, yPos, 0.f));

}

void game::MovementComponent::UpdateRotation()
{
	m_Angle += m_RotationSpeed * RamCoreEngine::Time::GetInstance().m_DeltaTime;

	if (m_Angle > 2.f * static_cast<float>(M_PI))
	{
		m_Angle -= 2.f * static_cast<float>(M_PI);
	}

	const glm::vec3 newPosition {m_RotationPoint.x + m_Radius * cos(m_Angle), m_RotationPoint.y + m_Radius * sin(m_Angle), 0};
	GetGameObject()->SetLocalPosition(glm::vec3(newPosition.x, newPosition.y, 0.f));
}
