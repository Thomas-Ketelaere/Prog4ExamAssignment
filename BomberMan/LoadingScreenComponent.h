#pragma once
#include "Component.h"

namespace game
{
	class LoadingScreenComponent final : public RamCoreEngine::Component
	{
	public:
		LoadingScreenComponent(RamCoreEngine::GameObject* gameObject, float timeToLoadLevel);

		void Update() override;

	private:
		float m_AccumulatedTime{};
		const float m_TimeToLoadLevel{};
	};
}

