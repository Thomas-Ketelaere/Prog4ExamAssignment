#pragma once
#include "Component.h"

namespace dae
{
	class GridComponent;
	class BombComponent final : public Component
	{
	public:
		BombComponent(GameObject* gameObject, GridComponent* gridComponent, int cellIndex, float timeToExplode);

		virtual void Update() override;
	private:
		GridComponent* m_pGridComponent;

		const float m_TimeToExplode;
		float m_AccumulatedTime;
		int m_CellIndex;
	};
}


