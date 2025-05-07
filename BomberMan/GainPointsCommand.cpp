#include "GainPointsCommand.h"
#include "GameObject.h"
#include "ScoreComponent.h"

game::GainPointsCommand::GainPointsCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pScoreComponent = actor->GetComponent<ScoreComponent>();
}

void game::GainPointsCommand::Execute()
{
	m_pScoreComponent->GainScore(m_GainScore);
}
