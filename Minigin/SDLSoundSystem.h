#pragma once
#include "SoundSystem.h"
#include "SDL_mixer.h"
#include <vector>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		void Play(const sound_id id, const float volume) override;

	private:
		std::vector<Mix_Chunk*> m_Samples;
	};
}


