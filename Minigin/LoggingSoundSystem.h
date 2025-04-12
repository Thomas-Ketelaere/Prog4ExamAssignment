#pragma once
#include "SoundSystem.h"
#include <memory>
#include <iostream>

namespace dae
{
	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SoundSystem> _real_ss;
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss) : _real_ss(std::move(ss)) {}
		virtual ~LoggingSoundSystem() = default;

		void Play(const SoundId id, const float volume, const int loops = 0) override
		{
			_real_ss->Play(id, volume, loops);
			std::cout << "playing " << id << " at volume " << volume << "amount loops:" << loops << std::endl;
		}

		void Stop(const SoundId id) override
		{
			_real_ss->Stop(id);
			std::cout << "stopping " << id << std::endl;
		}

		void AddSound(const SoundId id, const char* filePath) override 
		{
			_real_ss->AddSound(id, filePath);
		}
	};
}


