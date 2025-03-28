#pragma once
#include "Component.h"
#include <glm.hpp>

namespace dae
{
	class SpriteSheetComponent;
	class PlayerSpriteComponent final : public Component
	{
	public:
		PlayerSpriteComponent(GameObject* gameObject);

		virtual void Start() override;
		virtual void Update() override;

		int GetWidthSprite() const;
		int GetHeightSprite() const;

		void SetDirectionSprite(glm::vec2 direction);

	private:
		SpriteSheetComponent* m_pSpriteSheetComponent;
		bool m_Move{};
	};
}


