#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;
	class FpsComponent final : public Component
	{
	public:
		FpsComponent(GameObject* gameObject);

		virtual void Start() override;
		virtual void Update() override;

	private:
		TextComponent* m_TextComponent = nullptr;
	};
}


