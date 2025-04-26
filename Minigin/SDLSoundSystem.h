#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		void Play(const SoundId id, const float volume, const int loops = 0) override;
		void Stop(const SoundId id) override;
		void PlayMusic(const int volume, const int loops) override;
		void StopMusic() override;

		void AddSound(const SoundId id, const char* filePath) override;
		void LoadMusic(const char* filePath) override;
		void UnloadMusic() override;
		void UnloadAllSound() override;

	private:
		class SoundSystemImpl;
		std::unique_ptr<SoundSystemImpl> m_pImpl;

		
	};
}


