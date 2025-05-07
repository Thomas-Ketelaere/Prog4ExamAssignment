#pragma once
#include "SoundId.h"

namespace RamCoreEngine
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const SoundId id, const int volume, const int loops = 0) = 0;
		virtual void Stop(const SoundId id) = 0;
		virtual void PlayMusic(const char* filePath, const int volume, const int loops) = 0;
		virtual void StopMusic() = 0;

		virtual void AddSound(const SoundId id, const char* filePath) = 0;

		virtual void UnloadMusic() = 0;
		virtual void UnloadAllSound() = 0;

	};
}


