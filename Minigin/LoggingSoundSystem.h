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

		void Play(const SoundId id, const float volume) override
		{
			_real_ss->Play(id, volume);
			std::cout << "playing " << id << " at volume " << volume << std::endl;
		}

		void AddSound(const SoundId id, const char* filePath) override 
		{
			_real_ss->AddSound(id, filePath);
		}
	};
}


