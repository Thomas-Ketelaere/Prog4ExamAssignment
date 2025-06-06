#pragma once
#include "Collider.h"
#include "Component.h"

namespace RamCoreEngine
{
	// class to put on objects that dont have a trigger, but do need to collide with
	class BaseColliderComponent final : public Collider, public Component
	{
	public:
		BaseColliderComponent(GameObject* gameObject, const float width, const float height, bool isTrigger);
		~BaseColliderComponent() = default;
		BaseColliderComponent(const BaseColliderComponent& other) = delete;
		BaseColliderComponent(BaseColliderComponent&& other) = delete;
		BaseColliderComponent& operator=(const BaseColliderComponent& other) = delete;
		BaseColliderComponent& operator=(BaseColliderComponent&& other) = delete;

		void Render() const override;

		void OnTriggerOverlap(Collider*) override {}

		void SetDebugRendering(bool shouldRender) { m_DebugRender = shouldRender; }

	private:
		bool m_DebugRender{ true };
	};
}