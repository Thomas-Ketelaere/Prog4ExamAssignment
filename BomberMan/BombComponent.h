#pragma once
#include "Component.h"

namespace game
{
	class GridComponent;
	class BombComponent final : public RamCoreEngine::Component
	{
	public:
		BombComponent(RamCoreEngine::GameObject* gameObject, GridComponent* gridComponent, int cellIndex, float timeToExplode, int range);

		virtual void Update() override;

		void Explode();
	private:
		GridComponent* m_pGridComponent;

		const float m_TimeToExplode;
		float m_AccumulatedTime;
		int m_CellIndex;
		int m_Range;
	};
}


