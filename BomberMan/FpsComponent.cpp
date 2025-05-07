#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Timer.h"
#include <sstream>
#include <iomanip>

game::FpsComponent::FpsComponent(RamCoreEngine::GameObject* gameObject):
	Component(gameObject)
{
}

void game::FpsComponent::Start()
{
	m_TextComponent = GetGameObject()->GetComponent<RamCoreEngine::TextComponent>();
}

void game::FpsComponent::Update()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << 1.f / RamCoreEngine::Time::GetInstance().m_DeltaTime << "FPS";
	m_TextComponent->ChangeText(stream.str());
}
