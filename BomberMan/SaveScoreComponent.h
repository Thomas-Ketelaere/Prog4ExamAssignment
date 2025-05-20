#pragma once
#include "Component.h"
#include "string"

namespace game
{
	class SaveScoreComponent final : public RamCoreEngine::Component
	{
	public:
		SaveScoreComponent(RamCoreEngine::GameObject* gameObject, float lengthBar, float heightBar, float speed, const std::string& saveFileName);

		void Render() const override;

		void IncreaseBar();
		void ResetBar() { m_CurrentPercent = 0.f; }

	private:
		void SaveScore();

		float m_CurrentPercent{};
		const float m_Speed;
		const float m_LengthBar;
		const float m_HeightBar;
		const std::string m_SaveFileName;
		const size_t m_MaxPlayersInFile{ 5 };
	};
}


