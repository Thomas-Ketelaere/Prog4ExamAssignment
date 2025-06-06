#pragma once
#include "Component.h"
#include "Observer.h"

namespace RamCoreEngine
{
	class TextComponent;
}

namespace game
{
	
	class LivesTextComponent final: public RamCoreEngine::Component, public RamCoreEngine::Observer
	{
	public:
		LivesTextComponent(RamCoreEngine::GameObject* gameObject);
		~LivesTextComponent() = default;
		LivesTextComponent(const LivesTextComponent& other) = delete;
		LivesTextComponent(LivesTextComponent&& other) = delete;
		LivesTextComponent& operator=(const LivesTextComponent& other) = delete;
		LivesTextComponent& operator=(LivesTextComponent&& other) = delete;

		virtual void Start() override;
		virtual void Notify(Event event, RamCoreEngine::GameObject* gameObject) override;

	private:
		RamCoreEngine::TextComponent* m_TextComponent = nullptr;
	};
}


