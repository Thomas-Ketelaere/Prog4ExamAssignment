#include "Achievements.h"
#include "GameObject.h"
#include "ScoreComponent.h"
#include <iostream>


void dae::Achievements::Notify(Event event, GameObject* gameObject)
{
	if (event.id == make_sdbm_hash("PlayerGainedScore"))
	{
		if (gameObject->GetComponent<ScoreComponent>()->GetCurrentScore() >= 500.f)
		{
			SetAchievement("ACH_WIN_ONE_GAME");
		}
	}
}

void dae::Achievements::SetAchievement(const char* ID)
{
	std::cout << "ACHIEVMENT RECEIVED: " << ID << std::endl;
}
