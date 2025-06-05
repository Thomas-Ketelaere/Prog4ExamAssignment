#pragma once
#include "Component.h"
#include "Collider.h"

namespace game
{
	class LivesComponent;
	class PlayerCollider final : public RamCoreEngine::Collider, public RamCoreEngine::Component
	{
	public:
		PlayerCollider(RamCoreEngine::GameObject* gameObject, const float width, const float height, bool isTrigger);

		
		void Render() const override;

		void OnTriggerOverlap(Collider* other) override;
		void SetDebugRendering(bool shouldRender) { m_DebugRender = shouldRender; }

	private: 
		bool m_DebugRender{true};
	};
}


