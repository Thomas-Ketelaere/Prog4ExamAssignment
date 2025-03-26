#include "Component.h"
#include <string>
#include <glm.hpp>

namespace dae
{
	class Texture2D;
	class SpriteSheetComponent final : public Component
	{
	public:
		SpriteSheetComponent(GameObject* gameObject, const std::string& fullPath, int amountColumns, int amountRows, float interval);

		virtual void Render() const override;
		virtual void Update() override;

		void SetDirectionSprite(glm::vec2 direction);

	private:
		Texture2D* m_Texture;

		float m_AccumulatedTime{};
		float m_Interval;

		int m_Columns;
		int m_Rows;
		int m_CurrentColumn{};
		int m_CurrentRow{};
		int m_Width;
		int m_Height;

		bool m_Move{};
	};
}


