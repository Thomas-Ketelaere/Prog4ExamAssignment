#include "Component.h"
#include <string>
#include <glm.hpp>

namespace dae
{
	class Texture2D;
	class SpriteSheetComponent final : public Component
	{
	public:
		SpriteSheetComponent(GameObject* gameObject, const std::string& fullPath, int amountColumns, int amountRows, float interval, bool destroyAfterPlayed, bool useCustomPosition = false);

		virtual void Render() const override;
		virtual void Update() override;

		void SetCustomPosition(glm::vec2 customPosition) { m_CustomPosition = customPosition; }
		void UseCustomPosition(bool useCustomPosition) { m_UseCustomPosition = useCustomPosition; }
		void SetRow(int newRow) { m_CurrentRow = newRow; }
		void SetColumn(int newColumn) { m_CurrentColumn = newColumn; }
		void ShouldAnimate(bool animate) { m_Animate = animate; }

		int GetWidthSprite() const { return m_Width; }
		int GetHeightSprite() const { return m_Height; }

	private:
		Texture2D* m_Texture;

		glm::vec2 m_CustomPosition{};

		float m_AccumulatedTime{};
		float m_Interval;

		int m_Columns;
		int m_Rows;
		int m_CurrentColumn{};
		int m_CurrentRow{};
		int m_Width;
		int m_Height;

		bool m_Animate;
		bool m_UseCustomPosition;
		const bool m_DestroyAfterPlayed;
	};
}


