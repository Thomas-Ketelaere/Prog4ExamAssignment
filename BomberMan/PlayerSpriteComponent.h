#pragma once
#include "Component.h"
#include <glm.hpp>

namespace RamCoreEngine
{
	class SpriteSheetComponent;
}

namespace game
{
	
	class PlayerSpriteComponent final : public RamCoreEngine::Component
	{
	public:
		PlayerSpriteComponent(RamCoreEngine::GameObject* gameObject);

		virtual void Start() override;
		virtual void Render() const override;
		virtual void Update() override;

		int GetWidthSprite() const;
		int GetHeightSprite() const;

		void SetDirectionSprite(glm::vec2 direction);

		void StartDying();
	private:
		RamCoreEngine::SpriteSheetComponent* m_pSpriteSheetComponent = nullptr;
		bool m_Move{};
		bool m_IsDying{};
	};
}


