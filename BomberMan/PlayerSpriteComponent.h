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
		PlayerSpriteComponent(RamCoreEngine::GameObject* gameObject, float timeToDie);
		~PlayerSpriteComponent() = default;
		PlayerSpriteComponent(const PlayerSpriteComponent& other) = delete;
		PlayerSpriteComponent(PlayerSpriteComponent&& other) = delete;
		PlayerSpriteComponent& operator=(const PlayerSpriteComponent& other) = delete;
		PlayerSpriteComponent& operator=(PlayerSpriteComponent&& other) = delete;

		virtual void Start() override;
		virtual void Update() override;

		int GetWidthSprite() const;
		int GetHeightSprite() const;

		void SetDirectionSprite(glm::vec2 direction);

		void StartDying();
		bool IsDying() const { return m_IsDying; }
	private:
		RamCoreEngine::SpriteSheetComponent* m_pSpriteSheetComponent = nullptr;
		float m_AccumulatedTime{};
		const float m_TimeToDie;
		const float m_TimeToAdvanceLevel{3.f};
		bool m_Move{};
		bool m_IsDying{};
		bool m_Died{};

	};
}


