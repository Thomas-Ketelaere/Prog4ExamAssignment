#pragma once
#include "Component.h"
#include "Observer.h"
#include <glm.hpp>

namespace game
{
	class GridComponent;
	class SpawnBombComponent final : public RamCoreEngine::Component, public RamCoreEngine::Observer
	{
	public:
		SpawnBombComponent(RamCoreEngine::GameObject* gameObject);
		~SpawnBombComponent();

		void Start() override;
		void Notify(Event event, RamCoreEngine::GameObject* gameObject) override;

		void SpawnBomb(const glm::vec2 position);
		void RemoteExplodeBomb();

	private:
		GridComponent* m_pGridComponent{};
		int m_Range;
		int m_MaxAmountBombs;
		int m_CurrentAmountBombs{};
		bool m_RemoteExplode;

	};
}
