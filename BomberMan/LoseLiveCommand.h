#pragma once
#include "GameActorCommand.h"
namespace game
{
	class LivesComponent;
	class LoseLiveCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		LoseLiveCommand(RamCoreEngine::GameObject* actor);
		~LoseLiveCommand() = default;
		LoseLiveCommand(const LoseLiveCommand& other) = delete;
		LoseLiveCommand(LoseLiveCommand&& other) = delete;
		LoseLiveCommand& operator=(const LoseLiveCommand& other) = delete;
		LoseLiveCommand& operator=(LoseLiveCommand&& other) = delete;

		virtual void Execute() override;

	private:
		LivesComponent* m_pLivesComponent;
	};

}


