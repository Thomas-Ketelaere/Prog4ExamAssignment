#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

class RamCoreEngine::SDLSoundSystem::SDLSoundSystemImpl
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
		if (m_Samples.size() > 0)
		{
			for (auto& pair : m_Samples)
			{
				Mix_FreeChunk(pair.second);
			}
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
				pair.first.m_RequestType = SoundRequest::PlaySound;
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
						pair.first.m_RequestType = SoundRequest::StopSound;
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
		Sound music(0, filePath, SoundRequest::PlayMusic); // dont check id in queue, so doesnt matter what it is
		music.m_Loops = loops;
		music.m_Volume = volume;
		m_MusicVolume = volume;
		Mix_Chunk* soundEffect = nullptr; //doesnt require a chunk, just loaded music in queue itself
		m_Queue.push(std::make_pair(music, soundEffect));
		m_CondVar.notify_one();
	}

	void StopMusic()
	{
		Sound music(0, nullptr, SoundRequest::StopMusic); // dont check id in queue, so doesnt matter what it is
		Mix_Chunk* soundEffect = nullptr; //doesnt require a chunk, just loaded music in queue itself
		m_Queue.push(std::make_pair(music, soundEffect));
		m_CondVar.notify_one();
	}

	void AddSound(const SoundId id, const char* filePath)
	{
		Sound sound(id, filePath, SoundRequest::PlaySound);
		Mix_Chunk* soundEffect = nullptr;
		m_Samples.emplace_back(std::make_pair(sound, soundEffect));
	}

	void UnloadMusic()
	{
		Sound music(0, nullptr, SoundRequest::UnloadMusic); // dont check id in queue, so doesnt matter what it is
		Mix_Chunk* soundEffect = nullptr; //doesnt require a chunk, just loaded music in queue itself
		m_Queue.push(std::make_pair(music, soundEffect));
		m_CondVar.notify_one();
	}

	void UnloadAllSound()
	{
		for (auto& pair : m_Samples)
		{
			
			pair.first.m_RequestType = SoundRequest::UnloadSound;
			m_Queue.push(pair);
			m_CondVar.notify_one();
		}
		m_Samples.clear();
	}

	void Mute()
	{
		Sound music(0, nullptr, SoundRequest::Mute); // dont check id in queue, so doesnt matter what it is
		Mix_Chunk* soundEffect = nullptr; //doesnt require a chunk, just loaded music in queue itself
		m_Queue.push(std::make_pair(music, soundEffect));
		m_CondVar.notify_one();
	}

	void Unmute()
	{
		Sound music(0, nullptr, SoundRequest::Unmute); // dont check id in queue, so doesnt matter what it is
		Mix_Chunk* soundEffect = nullptr; //doesnt require a chunk, just loaded music in queue itself
		m_Queue.push(std::make_pair(music, soundEffect));
		m_CondVar.notify_one();
	}

private:
	void SoundQueueThread(const std::stop_token& stopToken)
	{
		while (!stopToken.stop_requested())
		{
			std::unique_lock<std::mutex> lck(m_Mutex);
			m_CondVar.wait(lck, [this, &stopToken] { return !m_Queue.empty() || stopToken.stop_requested(); });

			if (stopToken.stop_requested()) break;

			auto& pair = m_Queue.front();
			m_Queue.pop();

			lck.unlock(); // only need to lock shared resources (so m_queue in this case)

			switch (pair.first.m_RequestType)
			{
			case SoundRequest::PlaySound:
				if (pair.second == nullptr)
				{
					pair.second = Mix_LoadWAV(pair.first.m_FilePath);
					for (auto& pairSample : m_Samples)
					{
						if (pairSample.first.id == pair.first.id)
						{
							pairSample.second = pair.second;
							break;
						}
					}
				}
				if (pair.second != nullptr)
				{
					pair.second->volume = Uint8(pair.first.m_Volume);
					pair.first.m_Channel = Mix_PlayChannel(-1, pair.second, pair.first.m_Loops);
				}
				break;

			case SoundRequest::PlayMusic:
				if (m_pMusic != nullptr)
				{
					Mix_FreeMusic(m_pMusic);
				}
				m_pMusic = Mix_LoadMUS(pair.first.m_FilePath);
				Mix_VolumeMusic(pair.first.m_Volume);
				Mix_PlayMusic(m_pMusic, pair.first.m_Loops);
				break;

			case SoundRequest::StopSound:
				Mix_HaltChannel(pair.first.m_Channel);
				pair.first.m_Channel = -1;
				break;

			case SoundRequest::StopMusic:
				Mix_HaltMusic();
				break;

			case SoundRequest::UnloadSound:
				if (pair.second != nullptr)
				{
					Mix_FreeChunk(pair.second);
				}
				break;

			case SoundRequest::UnloadMusic:
				if (m_pMusic != nullptr)
				{
					Mix_FreeMusic(m_pMusic);
					m_pMusic = nullptr;
				}
				break;
			case SoundRequest::Mute:
				Mix_VolumeMusic(0);
				Mix_Volume(-1, 0);
				break;
			case SoundRequest::Unmute:
				Mix_VolumeMusic(m_MusicVolume);
				Mix_Volume(-1, MIX_MAX_VOLUME);
				for (auto& pairSample : m_Samples)
				{
					if (pairSample.first.m_Channel != -1)
					{
						Mix_Volume(pairSample.first.m_Channel, pairSample.first.m_Volume);
					}
				}
				break;
			}
		}
	}

	std::vector<std::pair<Sound, Mix_Chunk*>> m_Samples;
	Mix_Music* m_pMusic = nullptr;
	int m_MusicVolume{};

	std::jthread m_SoundQueueThread;
	std::mutex m_Mutex;
	std::condition_variable m_CondVar;
	std::queue< std::pair<Sound, Mix_Chunk*>> m_Queue;
};

RamCoreEngine::SDLSoundSystem::SDLSoundSystem():
	m_pImpl{std::make_unique<SDLSoundSystemImpl>()}
{
}

RamCoreEngine::SDLSoundSystem::~SDLSoundSystem() = default;

void RamCoreEngine::SDLSoundSystem::Play(const SoundId id, const int volume, const int loops)
{
	m_pImpl->Play(id, volume, loops);
}

void RamCoreEngine::SDLSoundSystem::Stop(const SoundId id)
{
	m_pImpl->Stop(id);
}

void RamCoreEngine::SDLSoundSystem::PlayMusic(const char* filePath, const int volume, const int loops)
{
	m_pImpl->PlayMusic(filePath, volume, loops);
}

void RamCoreEngine::SDLSoundSystem::StopMusic()
{
	m_pImpl->StopMusic();
}

void RamCoreEngine::SDLSoundSystem::Mute()
{
	m_pImpl->Mute();
}

void RamCoreEngine::SDLSoundSystem::Unmute()
{
	m_pImpl->Unmute();
}

void RamCoreEngine::SDLSoundSystem::AddSound(const SoundId id, const char* filePath)
{
	m_pImpl->AddSound(id, filePath);
}


void RamCoreEngine::SDLSoundSystem::UnloadMusic()
{
	m_pImpl->UnloadMusic();
}

void RamCoreEngine::SDLSoundSystem::UnloadAllSound()
{
	m_pImpl->UnloadAllSound();
}


