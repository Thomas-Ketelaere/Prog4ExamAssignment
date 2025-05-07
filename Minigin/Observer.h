#pragma once
#include "Events.h"
namespace RamCoreEngine
{
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(Event event, GameObject* gameObject) = 0;
	};
}


