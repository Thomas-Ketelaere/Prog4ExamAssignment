#pragma once
#include "Component.h"
#include <string>
#include <glm.hpp>

namespace dae
{
	class Texture2D;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject* gameObject, const std::string& fullPath, bool useCustomPosition = false);

		virtual void Render() const override;
		void SetCustomPosition(const glm::vec2 customPosition) { m_CustomPosition = customPosition; }
		
	private:
		Texture2D* m_Texture;
		glm::vec2 m_CustomPosition;

		bool m_UseCustomPosition;
		
	};
}


