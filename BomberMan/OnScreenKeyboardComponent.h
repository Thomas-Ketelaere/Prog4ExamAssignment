#pragma once
#include "Component.h"
#include <vector>
#include <Subject.h>
#include <glm.hpp>
#include <memory>

namespace RamCoreEngine
{
	class TextComponent;
}

namespace game
{
	class OnScreenKeyboardComponent final : public RamCoreEngine::Component
	{
	public:
		OnScreenKeyboardComponent(RamCoreEngine::GameObject* gameObject, int columns, int rows, int offsetX, int offsetY, uint8_t smallFontSize, uint8_t bigFontSize);
		~OnScreenKeyboardComponent() = default;
		OnScreenKeyboardComponent(const OnScreenKeyboardComponent& other) = delete;
		OnScreenKeyboardComponent(OnScreenKeyboardComponent&& other) = delete;
		OnScreenKeyboardComponent& operator=(const OnScreenKeyboardComponent& other) = delete;
		OnScreenKeyboardComponent& operator=(OnScreenKeyboardComponent&& other) = delete;

		void Start() override;
		void ButtonPressed(bool shouldRemove);
		void ChangeSelected(glm::vec2 direction);

		RamCoreEngine::Subject* GetNameChangedEventSubject() const { return m_pNameChangedEvent.get(); }

	private:
		std::unique_ptr<RamCoreEngine::Subject> m_pNameChangedEvent;
		std::vector<char> m_Alphabet;
		std::vector<RamCoreEngine::TextComponent*> m_pLetters;
		uint8_t m_SmallFontSize;
		uint8_t m_BigFontSize;
		int m_Index;
		int m_Columns;
		int m_Rows;
		int m_OffsetX;
		int m_OffsetY;
	};
}
