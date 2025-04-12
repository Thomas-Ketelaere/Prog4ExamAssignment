#pragma once
#include "SoundSystem.h"
#include "SDL_mixer.h"
#include <vector>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		void Play(const SoundId id, const float volume, const int loops = 0) override;
		void Stop(const SoundId id) override;
		void AddSound(const SoundId id, const char* filePath) override;

	private:
		std::vector<std::pair<Sound, Mix_Chunk*>> m_Samples;
	};
}


