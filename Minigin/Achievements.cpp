#include "Achievements.h"
#include <steam_api.h>
#include "GameObject.h"
#include "ScoreComponent.h"


void dae::Achievements::Notify(Event event, GameObject* gameObject)
{
	if (event == Event::PlayerGainedScore)
	{
		if (gameObject->GetComponent<ScoreComponent>()->GetCurrentScore() >= 500.f)
		{
			SetAchievement("ACH_WIN_ONE_GAME");
		}
	}
}

bool dae::Achievements::SetAchievement(const char* ID)
{
	SteamUserStats()->SetAchievement(ID);
	return SteamUserStats()->StoreStats();
}
