#include "Component.h"
#include "Observer.h"

namespace RamCoreEngine
{
	class TextComponent;
}

namespace game
{
	
	class ScoreTextComponent final : public RamCoreEngine::Component, public RamCoreEngine::Observer
	{
	public:
		ScoreTextComponent(RamCoreEngine::GameObject* gameObject);

		virtual void Start() override;
		virtual void Notify(Event event, RamCoreEngine::GameObject* gameObject) override;

	private:
		RamCoreEngine::TextComponent* m_TextComponent = nullptr;
	};
}


