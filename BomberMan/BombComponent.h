#pragma once
#include "Component.h"

namespace game
{
	class GridComponent;
	class BombComponent final : public RamCoreEngine::Component
	{
	public:
		BombComponent(RamCoreEngine::GameObject* gameObject, GridComponent* gridComponent, int cellIndex, float timeToExplode);

		virtual void Update() override;
	private:
		GridComponent* m_pGridComponent;

		const float m_TimeToExplode;
		float m_AccumulatedTime;
		int m_CellIndex;
	};
}


