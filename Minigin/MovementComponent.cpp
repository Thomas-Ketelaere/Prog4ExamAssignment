#include "MovementComponent.h"
#include "Transform.h"
#include "Time.h"

dae::MovementComponent::MovementComponent(float speedX, float speedY) :
	m_SpeedX{ speedX }, 
	m_SpeedY{ speedY }
{
}

void dae::MovementComponent::Update()
{
	const float deltaTime = Time::GetInstance().m_DeltaTime;
	//glm::uvec3 newPosition{ GetTransform()->GetPosition() }; conversion problems
	float xPos = GetTransform()->GetPosition().x;
	float yPos = GetTransform()->GetPosition().y;
	xPos += m_SpeedX * deltaTime;
	yPos += m_SpeedY * deltaTime;
	GetTransform()->SetPosition(xPos, yPos, 0);

}

void dae::MovementComponent::SetSpeed(float newSpeedX, float newSpeedY)
{
	m_SpeedX = newSpeedX;
	m_SpeedY = newSpeedY;
}
