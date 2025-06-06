#pragma once
#include "Component.h"

namespace RamCoreEngine
{
	class TextComponent;
}

namespace game
{
	class TimerLevelComponent final : public RamCoreEngine::Component
	{
	public:
		TimerLevelComponent(RamCoreEngine::GameObject* gameObject, float timeForLevel, int amountEnemiesAfterTime);
		~TimerLevelComponent() = default;
		TimerLevelComponent(const TimerLevelComponent& other) = delete;
		TimerLevelComponent(TimerLevelComponent&& other) = delete;
		TimerLevelComponent& operator=(const TimerLevelComponent& other) = delete;
		TimerLevelComponent& operator=(TimerLevelComponent&& other) = delete;

		void Start() override;
		void Update() override;

	private:
		RamCoreEngine::TextComponent* m_TimeTextComponent{};
		float m_TimeForLevel;
		int m_TimeText{};
		const int m_AmountEnemiesAfterTime;
	};
}


