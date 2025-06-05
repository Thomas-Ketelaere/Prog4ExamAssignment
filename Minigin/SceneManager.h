#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"

namespace RamCoreEngine
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(unsigned int name, bool setAsCurrentScene);
		Scene* GetCurrentScene() const { return m_pCurrentScene; }

		void Start();
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render();

		void LoadScene(unsigned int sceneToLoadName);
		void ReloadScene();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_Scenes;

		bool m_ShouldLoadScene{};
		unsigned int m_LoadSceneName{};

		Scene* m_pCurrentScene = nullptr;
	};
}
