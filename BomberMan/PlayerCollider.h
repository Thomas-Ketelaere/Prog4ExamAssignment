#pragma once
#include "Component.h"
#include "Collider.h"
#include <vector>
#include <memory>

namespace game
{
	class LivesComponent;
	class PlayerCollider final : public RamCoreEngine::Collider, public RamCoreEngine::Component
	{
	public:
		PlayerCollider(RamCoreEngine::GameObject* gameObject, const float width, const float height, bool isTrigger);

		void Start() override;
		void Render() const override;

		void OnTriggerOverlap(Collider* other) override;
		void SetDebugRendering(bool shouldRender) { m_DebugRender = shouldRender; }

	private: 
		bool m_DebugRender{true};
	};
}


