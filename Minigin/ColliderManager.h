#pragma once
#include "Singleton.h"
#include "Collider.h"
#include <vector>


namespace RamCoreEngine
{
	class ColliderManager final : public Singleton<ColliderManager>
	{
	public:
		void AddCollider(Collider* collider);
		void ClearColliders();

		void UpdateColliders();

		void RemoveCollider(Collider* collider);

	private:

		std::vector<Collider*> m_pColliderCompVct{};
	};
}


