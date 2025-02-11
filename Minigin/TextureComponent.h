#pragma once
#include "Component.h"
#include <string>


namespace dae
{
	class Texture2D;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(const std::string& fullPath);

		virtual void Render() const override;
		
	private:
		Texture2D* m_Texture;
	};
}


