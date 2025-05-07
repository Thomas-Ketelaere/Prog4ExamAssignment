#include "ServiceLocator.h"

std::unique_ptr<RamCoreEngine::SoundSystem> RamCoreEngine::ServiceLocator::_ss_instance = nullptr;

