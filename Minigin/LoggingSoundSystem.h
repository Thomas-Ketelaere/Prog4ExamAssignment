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

		void Play(const sound_id id, const float volume) override
		{
			_real_ss->Play(id, volume);
			std::cout << "playing " << id << " at volume " << volume << std::endl;
		}
	};
}


