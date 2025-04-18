#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class GridComponent;
	class SpawnBombCommand : public GameActorCommand
	{
	public:
		SpawnBombCommand(GameObject* actor);
		virtual void Execute() override;

	private:
		GridComponent* m_pGridComponent;
	};
}

