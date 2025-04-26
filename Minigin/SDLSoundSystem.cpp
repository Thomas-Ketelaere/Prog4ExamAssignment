#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

class dae::SDLSoundSystem::SDLSoundSystemImpl
{
public:
	SDLSoundSystemImpl()
	{
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		m_SoundQueueThread = std::jthread([this](const std::stop_token& stopToken)
			{
				SoundQueueThread(stopToken);
			});
	}
	~SDLSoundSystemImpl()
	{
		m_CondVar.notify_one();
		m_SoundQueueThread.request_stop();
		Mix_FreeMusic(m_pMusic);
		for (auto& pair : m_Samples)
		{
			Mix_FreeChunk(pair.second);
		}
	}

	void Play(const SoundId id, const int volume, const int loops = 0)
	{
		for (auto& pair : m_Samples)
		{
			if (pair.first.id == id)
			{
				pair.first.m_Loops = loops;
				pair.first.m_Volume = volume;
				m_Queue.push(pair);
				m_CondVar.notify_one();
				return;
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
						pair.first.m_ShouldStop = true;
						m_Queue.push(pair);
						m_CondVar.notify_one();
					}
				}
				return;
			}
		}
	}

	void PlayMusic(const char* filePath, const int volume, const int loops)
	{
		Sound music(0, filePath, true); // dont check id in queue, so doesnt matter what it is
		music.m_Loops = loops;
		music.m_Volume = volume;
		Mix_Chunk* soundEffect = nullptr; //doesnt require a chunk, just loaded music in queue itself
		m_Queue.push(std::make_pair(music, soundEffect));
		m_CondVar.notify_one();
	}

	void StopMusic()
	{
		Sound music(0, nullptr, true); // dont check id in queue, so doesnt matter what it is
		music.m_ShouldStop = true;
		Mix_Chunk* soundEffect = nullptr; //doesnt require a chunk, just loaded music in queue itself
		m_Queue.push(std::make_pair(music, soundEffect));
		m_CondVar.notify_one();
	}

	void AddSound(const SoundId id, const char* filePath)
	{
		Sound sound(id, filePath, false);
		Mix_Chunk* soundEffect = nullptr;
		m_Samples.emplace_back(std::make_pair(sound, soundEffect));
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
	void SoundQueueThread(const std::stop_token& stopToken)
	{
		while (!stopToken.stop_requested())
		{
			std::unique_lock<std::mutex> lck(m_Mutex);
			m_CondVar.wait(lck, [this, &stopToken] { return !m_Queue.empty() || stopToken.stop_requested(); });

			if (stopToken.stop_requested()) break;

			auto pair = m_Queue.front();
			m_Queue.pop();

			if (pair.first.m_ShouldStop)
			{
				if (pair.first.m_IsMusic)
				{
					Mix_HaltMusic();
				}
				else
				{
					Mix_HaltChannel(pair.first.m_Channel);
					pair.first.m_Channel = -1;
				}
			}

			else
			{
				if (pair.first.m_IsMusic)
				{
					m_pMusic = Mix_LoadMUS(pair.first.m_FilePath);
					Mix_VolumeMusic(pair.first.m_Volume);
					Mix_PlayMusic(m_pMusic, pair.first.m_Loops);
				}
				else
				{
					if (!pair.first.m_IsLoaded)
					{
						pair.second = Mix_LoadWAV(pair.first.m_FilePath);
						pair.first.m_IsLoaded = true;
					}
					pair.second->volume = Uint8(pair.first.m_Volume);
					pair.first.m_Channel = Mix_PlayChannel(-1, pair.second, pair.first.m_Loops);
				}
			}
		}
	}

	std::vector<std::pair<Sound, Mix_Chunk*>> m_Samples;
	Mix_Music* m_pMusic = nullptr;

	std::jthread m_SoundQueueThread;
	std::mutex m_Mutex;
	std::condition_variable m_CondVar;
	std::queue< std::pair<Sound, Mix_Chunk*>> m_Queue;
};

dae::SDLSoundSystem::SDLSoundSystem():
	m_pImpl{std::make_unique<SDLSoundSystemImpl>()}
{
}

dae::SDLSoundSystem::~SDLSoundSystem() = default;

void dae::SDLSoundSystem::Play(const SoundId id, const int volume, const int loops)
{
	m_pImpl->Play(id, volume, loops);
}

void dae::SDLSoundSystem::Stop(const SoundId id)
{
	m_pImpl->Stop(id);
}

void dae::SDLSoundSystem::PlayMusic(const char* filePath, const int volume, const int loops)
{
	m_pImpl->PlayMusic(filePath, volume, loops);
}

void dae::SDLSoundSystem::StopMusic()
{
	m_pImpl->StopMusic();
}

void dae::SDLSoundSystem::AddSound(const SoundId id, const char* filePath)
{
	m_pImpl->AddSound(id, filePath);
}


void dae::SDLSoundSystem::UnloadMusic()
{
	m_pImpl->UnloadMusic();
}

void dae::SDLSoundSystem::UnloadAllSound()
{
	m_pImpl->UnloadAllSound();
}


