#pragma once
#include "Component.h"

namespace game
{
	class GridComponent;
	class BombComponent final : public RamCoreEngine::Component
	{
	public:
		BombComponent(RamCoreEngine::GameObject* gameObject, GridComponent* gridComponent, int cellIndex, int range);

		void Explode();
	private:
		GridComponent* m_pGridComponent;

		int m_CellIndex;
		int m_Range;
	};
}


