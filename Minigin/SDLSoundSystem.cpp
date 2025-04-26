#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include <vector>
#include <iostream>

class dae::SDLSoundSystem::SoundSystemImpl
{
public:
	SoundSystemImpl()
	{
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	}
	~SoundSystemImpl()
	{
		Mix_FreeMusic(m_pMusic);
	}
	void Play(const SoundId id, const float volume, const int loops = 0)
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

	void Stop(const SoundId id)
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
						pair.first.m_Channel = -1;
					}
				}
			}
		}
	}

	void PlayMusic(const int volume, const int loops)
	{
		Mix_VolumeMusic(volume);
		Mix_PlayMusic(m_pMusic, loops);
	}

	void StopMusic()
	{
		Mix_HaltMusic();
	}

	void AddSound(const SoundId id, const char* filePath)
	{
		Sound sound(id, filePath);
		Mix_Chunk* soundEffect = nullptr;
		m_Samples.emplace_back(std::make_pair(sound, soundEffect));
	}

	void LoadMusic(const char* filePath)
	{
		m_pMusic = Mix_LoadMUS(filePath);
	}

	void UnloadMusic()
	{
		Mix_FreeMusic(m_pMusic);
	}

	void UnloadAllSound()
	{
		for (auto& pair : m_Samples)
		{
			Mix_FreeChunk(pair.second);
		}
		m_Samples.clear();
	}

private:
	std::vector<std::pair<Sound, Mix_Chunk*>> m_Samples;
	Mix_Music* m_pMusic = nullptr;
};

dae::SDLSoundSystem::SDLSoundSystem():
	m_pImpl{std::make_unique<SoundSystemImpl>()}
{
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
}

void dae::SDLSoundSystem::Play(const SoundId id, const float volume, const int loops)
{
	m_pImpl->Play(id, volume, loops);
}

void dae::SDLSoundSystem::Stop(const SoundId id)
{
	m_pImpl->Stop(id);
}

void dae::SDLSoundSystem::PlayMusic(const int volume, const int loops)
{
	m_pImpl->PlayMusic(volume, loops);
}

void dae::SDLSoundSystem::StopMusic()
{
	m_pImpl->StopMusic();
}

void dae::SDLSoundSystem::AddSound(const SoundId id, const char* filePath)
{
	m_pImpl->AddSound(id, filePath);
}

void dae::SDLSoundSystem::LoadMusic(const char* filePath)
{
	m_pImpl->LoadMusic(filePath);
}

void dae::SDLSoundSystem::UnloadMusic()
{
	m_pImpl->UnloadMusic();
}

void dae::SDLSoundSystem::UnloadAllSound()
{
	m_pImpl->UnloadAllSound();
}


