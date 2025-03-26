#pragma once
#include "Component.h"
#include "Observer.h"
namespace dae
{
	class TextComponent;
	class LivesTextComponent final: public Component, public Observer
	{
	public:
		LivesTextComponent(GameObject* gameObject);

		virtual void Start() override;
		virtual void Notify(Event event, GameObject* gameObject) override;

	private:
		TextComponent* m_TextComponent = nullptr;
	};
}


