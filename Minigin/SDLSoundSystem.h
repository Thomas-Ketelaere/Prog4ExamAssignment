#pragma once
#include "SoundSystem.h"
#include <memory>

namespace RamCoreEngine
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		void Play(const SoundId id, const int volume, const int loops = 0) override;
		void Stop(const SoundId id) override;
		void PlayMusic(const char* filePath, const int volume, const int loops) override;
		void StopMusic() override;

		void Mute() override;

		void AddSound(const SoundId id, const char* filePath) override;
		void UnloadMusic() override;
		void UnloadAllSound() override;
		void LoadAllSound() override;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}


