#pragma once
#include "Component.h"

namespace game
{
	class GridComponent;
	class BombComponent final : public RamCoreEngine::Component
	{
	public:
		BombComponent(RamCoreEngine::GameObject* gameObject, GridComponent* gridComponent, int cellIndex, int range);
		~BombComponent() = default;
		BombComponent(const BombComponent& other) = delete;
		BombComponent(BombComponent&& other) = delete;
		BombComponent& operator=(const BombComponent& other) = delete;
		BombComponent& operator=(BombComponent&& other) = delete;

		void Explode();
	private:
		GridComponent* m_pGridComponent;

		int m_CellIndex;
		int m_Range;
	};
}


