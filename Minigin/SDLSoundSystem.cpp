#include "SDLSoundSystem.h"
#include <iostream>


dae::SDLSoundSystem::SDLSoundSystem()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
}

void dae::SDLSoundSystem::Play(const SoundId id, const float volume)
{
	for (auto pair : m_Samples)
	{
		if (pair.first.id == id)
		{
			if (!pair.first.isLoaded)
			{
				pair.second = Mix_LoadWAV(pair.first.m_FilePath);
				pair.first.isLoaded = true;
			}
			pair.second->volume = Uint8(volume);
			Mix_PlayChannel(-1, pair.second, 0);
		}
	}
}

void dae::SDLSoundSystem::AddSound(const SoundId id, const char* filePath)
{
	Sound sound(id, filePath);
	Mix_Chunk* soundEffect = nullptr;
	m_Samples.emplace_back(std::make_pair(sound, soundEffect));
}
