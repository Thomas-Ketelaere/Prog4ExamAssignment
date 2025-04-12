#pragma once
//#include "Events.h"
#include "Hash.h"

using SoundId = unsigned int;

struct Sound
{
	const SoundId id;
	bool isLoaded = false;
	const char* m_FilePath;
	int m_Channel = -1; //-1 is not playing
	explicit Sound(SoundId _id, const char* filePath) : id{ _id }, m_FilePath{ filePath } {}
};
