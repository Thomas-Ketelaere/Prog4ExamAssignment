#pragma once
#include "Events.h"
#include <vector>
namespace dae
{
	class Observer;
	class GameObject;
	class Subject
	{
	public:
		void AddObserver(Observer* observerToAdd);
		void RemoveObserver(Observer* observerToDestroy); 
		void NotifyObservers(Event event, GameObject* gameObject);

	private:
		std::vector<Observer*> m_Observers{};
	};


}


