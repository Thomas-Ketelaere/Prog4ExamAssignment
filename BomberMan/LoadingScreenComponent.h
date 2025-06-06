#pragma once
#include "Component.h"

namespace game
{
	class LoadingScreenComponent final : public RamCoreEngine::Component
	{
	public:
		LoadingScreenComponent(RamCoreEngine::GameObject* gameObject, float timeToLoadLevel);
		~LoadingScreenComponent() = default;
		LoadingScreenComponent(const LoadingScreenComponent& other) = delete;
		LoadingScreenComponent(LoadingScreenComponent&& other) = delete;
		LoadingScreenComponent& operator=(const LoadingScreenComponent& other) = delete;
		LoadingScreenComponent& operator=(LoadingScreenComponent&& other) = delete;

		void Update() override;

	private:
		float m_AccumulatedTime{};
		const float m_TimeToLoadLevel{};
	};
}

