#include "SDLSoundSystem.h"
#include <iostream>


void dae::SDLSoundSystem::Play(const sound_id id, const float volume)
{
	Mix_Chunk* sample = Mix_LoadWAV("sample.wav");
	//auto audioclip = audioclips[id];
	//if (!audioclip->is_loaded()) audioclip->load();
	//audioclip->set_volume(volume);
	//audioclip->play();
	Mix_PlayChannel(-1, sample, 0);
	std::cout << id << volume << std::endl;
}
