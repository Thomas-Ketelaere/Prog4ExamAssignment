#pragma once
//#include "Events.h"
#include "Hash.h"

using SoundId = unsigned int;

struct Sound
{
	const SoundId id;
	bool m_IsLoaded = false;
	bool m_IsMusic;
	bool m_ShouldStop{};
	int m_Loops = 0;
	const char* m_FilePath;
	int m_Volume = 0;
	int m_Channel = -1; //-1 is not playing
	explicit Sound(SoundId _id, const char* filePath, bool isMusic) : id{ _id }, m_FilePath{ filePath }, m_IsMusic{ isMusic } {}
};
