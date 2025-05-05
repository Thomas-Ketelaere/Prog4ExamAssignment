#include "ColliderManager.h"

void dae::ColliderManager::AddCollider(Collider* collider)
{
	m_pColliderCompVct.emplace_back(collider);
}

void dae::ColliderManager::ClearColliders()
{
	m_pColliderCompVct.clear();
}

void dae::ColliderManager::UpdateColliders()
{
	//for (const auto& firstCollider : m_pColliderCompVct)
	//{
	//	for (const auto& secondCollider : m_pColliderCompVct)
	//	{
	//		if (firstCollider == secondCollider)
	//		{
	//			continue;
	//		}
	//		if (firstCollider->IsColliding(secondCollider))
	//		{
	//			if (firstCollider->IsTrigger())
	//			{
	//				firstCollider->OnTriggerOverlap(secondCollider);
	//			}

	//			if (secondCollider->IsTrigger())
	//			{
	//				secondCollider->OnTriggerOverlap(firstCollider);
	//			}
	//		}
	//	}
	//}

	//cannot do 2 range based for loops bcs will go over every collider twice otherwise
	for (unsigned int i{}; i < m_pColliderCompVct.size(); ++i)
	{
		for (unsigned int j = i + 1; j < m_pColliderCompVct.size(); ++j)
		{
			auto* firstCollider = m_pColliderCompVct[i];
			auto* secondCollider = m_pColliderCompVct[j];

			if (firstCollider->IsColliding(secondCollider))
			{
				if (firstCollider->IsTrigger())
				{
					firstCollider->OnTriggerOverlap(secondCollider);
				}

				if (secondCollider->IsTrigger())
				{
					secondCollider->OnTriggerOverlap(firstCollider);
				}
			}
		}
	}
}
