#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "Minigin.h"

void load()
{
	
}

int main(int, char* [])
{
	RamCoreEngine::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}