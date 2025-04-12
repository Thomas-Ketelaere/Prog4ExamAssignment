#pragma once
#include "SoundId.h"

namespace dae
{
	
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const SoundId id, const float volume, const int loops = 0) = 0;
		virtual void Stop(const SoundId id) = 0;

		virtual void AddSound(const SoundId id, const char* filePath) = 0;

	};
}


