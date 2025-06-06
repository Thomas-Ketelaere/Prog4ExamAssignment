#pragma once
#include <memory>
#include "Component.h"
#include "Observer.h"

namespace RamCoreEngine
{
	class Subject;
}

namespace game
{
	class ScoreComponent : public RamCoreEngine::Component, public RamCoreEngine::Observer
	{
	public:
		ScoreComponent(RamCoreEngine::GameObject* gameObject);
		~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void GainScore(int amount);

		virtual void Notify(Event event, RamCoreEngine::GameObject* gameObject) override;

		RamCoreEngine::Subject* GetActorScoreSubject() const { return m_pActorScoreEvent.get(); }
		int GetCurrentScore() { return m_CurrentScore; }
	private:
		int m_CurrentScore{};
		std::unique_ptr<RamCoreEngine::Subject> m_pActorScoreEvent;
	};
}


