#include "SpriteSheetComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Timer.h"

RamCoreEngine::SpriteSheetComponent::SpriteSheetComponent(GameObject* gameObject, const std::string& fullPath, int amountColumns, int amountRows, float interval, bool destroyAfterPlayed, bool useCustomPosition) :
	Component(gameObject),
	m_Columns{ amountColumns },
	m_Rows{amountRows},
	m_Interval{interval},
	m_Animate{true},
	m_DestroyAfterPlayed{destroyAfterPlayed},
	m_UseCustomPosition{ useCustomPosition }

{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fullPath);
	m_Width = m_Texture->GetSize().x / amountColumns;
	m_Height = m_Texture->GetSize().y / amountRows;
}

void RamCoreEngine::SpriteSheetComponent::Render() const
{
	if (m_UseCustomPosition)
	{
		const auto& worldPos = GetTransform()->GetWorldPosition();
		glm::vec2 pos{};
		pos.x = m_CustomPosition.x + worldPos.x;
		pos.y = m_CustomPosition.y + worldPos.y;

		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Width, m_Height, m_CurrentColumn * m_Width, m_CurrentRow * m_Height);
	}
	else
	{
		const auto& transform = GetTransform()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, transform.x, transform.y, m_Width, m_Height, m_CurrentColumn * m_Width, m_CurrentRow * m_Height);
	}
	
}

void RamCoreEngine::SpriteSheetComponent::Update()
{
	if (m_Animate) 
	{
		m_AccumulatedTime += Time::GetInstance().m_DeltaTime;
		if (m_AccumulatedTime >= m_Interval)
		{
			++m_CurrentColumn;
			if (m_CurrentColumn == m_Columns)
			{
				if (m_DestroyAfterPlayed)
				{
					Destroy();
					//GetGameObject()->Destroy();
				}
				m_CurrentColumn = 0;
			}
			m_AccumulatedTime -= m_Interval;
		}
		
	}
	
	else
	{
		m_AccumulatedTime = 0;
	}

}

void RamCoreEngine::SpriteSheetComponent::SetRow(int newRow)
{
	m_CurrentRow = newRow;
}

