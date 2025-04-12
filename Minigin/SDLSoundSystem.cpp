#include "SDLSoundSystem.h"
#include <iostream>


dae::SDLSoundSystem::SDLSoundSystem()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
}

void dae::SDLSoundSystem::Play(const SoundId id, const float volume, const int loops)
{
	for (auto& pair : m_Samples)
	{
		if (pair.first.id == id)
		{
			if (!pair.first.isLoaded)
			{
				pair.second = Mix_LoadWAV(pair.first.m_FilePath);
				pair.first.isLoaded = true;
			}
			pair.second->volume = Uint8(volume);
			pair.first.m_Channel = Mix_PlayChannel(-1, pair.second, loops);
		}
	}
}

void dae::SDLSoundSystem::Stop(const SoundId id)
{
	for (auto& pair : m_Samples)
	{
		if (pair.first.id == id)
		{
			const int channel = pair.first.m_Channel;
			if (channel != -1)
			{
				int playing = Mix_Playing(channel);
				if (playing != 0) //is playing on that channel
				{
					Mix_HaltChannel(channel);
				}
			}
		}
	}
}

void dae::SDLSoundSystem::AddSound(const SoundId id, const char* filePath)
{
	Sound sound(id, filePath);
	Mix_Chunk* soundEffect = nullptr;
	m_Samples.emplace_back(std::make_pair(sound, soundEffect));
}
