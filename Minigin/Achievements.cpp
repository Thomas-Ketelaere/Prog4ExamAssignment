#include "Achievements.h"
#include <steam_api.h>


bool dae::Achievements::SetAchievement(const char* ID)
{
	SteamUserStats()->SetAchievement(ID);
	return SteamUserStats()->StoreStats();
}
