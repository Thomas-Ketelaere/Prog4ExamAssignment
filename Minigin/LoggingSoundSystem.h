#pragma once
#include "SoundSystem.h"
#include <memory>
#include <iostream>

namespace RamCoreEngine
{
	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SoundSystem> _real_ss;
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss) : _real_ss(std::move(ss)) {}
		virtual ~LoggingSoundSystem() = default;

		void Play(const SoundId id, const int volume, const int loops = 0) override
		{
			_real_ss->Play(id, volume, loops);
			std::cout << "playing " << id << " at volume " << volume << " amount loops: " << loops << std::endl;
		}

		void Stop(const SoundId id) override
		{
			_real_ss->Stop(id);
			std::cout << "stopping " << id << std::endl;
		}

		void AddSound(const SoundId id, const char* filePath) override 
		{
			_real_ss->AddSound(id, filePath);
			std::cout << "added sound " << id << std::endl;
		}

		void PlayMusic(const char* filePath, const int volume, const int loops) override
		{
			_real_ss->PlayMusic(filePath, volume, loops);
			std::cout << "playing music at volume " << volume  << " amount loops:" << loops << std::endl;
		}

		void StopMusic() override
		{
			_real_ss->StopMusic();
			std::cout << "stopped music" << std::endl;
		}

		void UnloadMusic() override
		{
			_real_ss->UnloadMusic();
			std::cout << "Unloaded music" << std::endl;
		}

		void UnloadAllSound() override
		{
			_real_ss->UnloadAllSound();
			std::cout << "Unloaded all sound" << std::endl;
		}

		void Mute() override
		{
			_real_ss->Mute();
			std::cout << "(Un)muted all sound" << std::endl;
		}

		void LoadAllSound() override
		{
			_real_ss->LoadAllSound();
			std::cout << "loaded all sound" << std::endl;
		}
	};
}


