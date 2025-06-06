#pragma once
#include "Component.h"
#include "Observer.h"

namespace RamCoreEngine
{
	class TextComponent;
}

namespace game
{
	class NameTextComponent final : public RamCoreEngine::Component, public RamCoreEngine::Observer
	{
	public:
		NameTextComponent(RamCoreEngine::GameObject* gameObject);
		~NameTextComponent() = default;
		NameTextComponent(const NameTextComponent& other) = delete;
		NameTextComponent(NameTextComponent&& other) = delete;
		NameTextComponent& operator=(const NameTextComponent& other) = delete;
		NameTextComponent& operator=(NameTextComponent&& other) = delete;

		virtual void Start() override;
		virtual void Notify(Event event, RamCoreEngine::GameObject* gameObject) override;

	private:
		RamCoreEngine::TextComponent* m_TextComponent = nullptr;
	};
}
