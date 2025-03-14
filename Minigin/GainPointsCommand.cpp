#include "GainPointsCommand.h"
#include "GameObject.h"
#include "ScoreComponent.h"

dae::GainPointsCommand::GainPointsCommand(GameObject* actor):
	GameActorCommand(actor)
{
	m_pScoreComponent = actor->GetComponent<ScoreComponent>();
}

void dae::GainPointsCommand::Execute()
{
	m_pScoreComponent->GainScore(m_GainScore);
}
