#pragma once
#include "Component.h"

namespace RamCoreEngine
{
	class TextComponent;
}

namespace game
{
	
	class FpsComponent final : public RamCoreEngine::Component
	{
	public:
		FpsComponent(RamCoreEngine::GameObject* gameObject);
		~FpsComponent() = default;
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;

		virtual void Start() override;
		virtual void Update() override;

	private:
		RamCoreEngine::TextComponent* m_TextComponent = nullptr;
	};
}


