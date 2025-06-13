#pragma once
//#include "Events.h"
#include "Hash.h"

using SoundId = unsigned int;

enum class SoundRequest
{
	PlaySound, PlayMusic, StopSound, StopMusic, UnloadSound, UnloadMusic, Mute, Unmute, LoadSound
};

struct Sound
{
	const SoundId id;
	SoundRequest m_RequestType;
	int m_Loops = 0;
	const char* m_FilePath;
	int m_Volume = 0;
	int m_Channel = -1; //-1 is not playing
	explicit Sound(SoundId _id, const char* filePath, SoundRequest soundRequest) : id{ _id }, m_FilePath{ filePath }, m_RequestType{ soundRequest } {}
};
