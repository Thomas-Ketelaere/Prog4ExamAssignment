#pragma once
#include "Component.h"
#include "Collider.h"
#include <vector>
#include <memory>

namespace dae
{
	class LivesComponent;
	class PlayerCollider final : public Collider, public Component
	{
	public:
		PlayerCollider(GameObject* gameObject, const float width, const float height, bool isTrigger);

		void Start() override;
		void Render() const override;


		void OnTriggerOverlap(Collider* other) override;
		void SetDebugRendering(bool shouldRender) { m_DebugRender = shouldRender; }

	private: 
		LivesComponent* m_pLivesComponent;

		bool m_DebugRender{true};
	};
}


