#pragma once
#include <memory>
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		void Play(const SoundId, const float, const int) override {}
		void Stop(const SoundId) override {}
		void AddSound(const SoundId, const char*) override {}

		void PlayMusic(const int , const int) override {}
		void StopMusic() override {}
		void LoadMusic(const char* ) override {}


		void UnloadMusic() override {}
		void UnloadAllSound() override {}

	};

	class ServiceLocator final
	{
		static std::unique_ptr<SoundSystem> _ss_instance;
	public:
		static SoundSystem& GetSoundSystem() { return *_ss_instance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
		{
			_ss_instance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		};
	};
}


