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
		void Play(const SoundId id, const float volume) override;
		void AddSound(const SoundId id, const char* filePath) override;

	private:
		//std::vector<Mix_Chunk*> m_Samples;
		std::vector<std::pair<Sound, Mix_Chunk*>> m_Samples;
	};
}


