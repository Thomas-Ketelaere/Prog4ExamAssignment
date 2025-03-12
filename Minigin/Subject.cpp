#include "Subject.h"
#include "Observer.h"


void dae::Subject::AddObserver(Observer* observerToAdd)
{
	m_Observers.push_back(observerToAdd);
}

void dae::Subject::RemoveObserver(Observer* observerToDestroy)
{
	std::erase_if(m_Observers, [&](Observer* observer)
		{
			return observerToDestroy = observer;
		});
}

void dae::Subject::NotifyObservers(Event event, GameObject* gameObject)
{
	for (auto observer : m_Observers)
	{
		observer->Notify(event, gameObject);
	}
}

