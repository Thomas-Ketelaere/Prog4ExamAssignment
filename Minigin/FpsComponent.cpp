#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"
#include <sstream>
#include <iomanip>

void dae::FpsComponent::Start()
{
	m_TextComponent = GetGameObject()->GetComponent<TextComponent>();
}

void dae::FpsComponent::Update()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << 1.f / Time::GetInstance().m_DeltaTime << "FPS";
	m_TextComponent->ChangeText(stream.str());
}
