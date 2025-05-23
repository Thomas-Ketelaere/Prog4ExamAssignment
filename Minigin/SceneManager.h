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
		Scene& CreateScene(const std::string& name, bool setAsCurrentScene);
		Scene* GetCurrentScene() const { return m_pCurrentScene; }

		void Start();
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render();

		void LoadScene(const std::string& sceneToLoadName);
		void ReloadScene();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_Scenes;

		bool m_ShouldLoadScene{};
		std::string m_LoadSceneName{}; //TODO: make with hash

		Scene* m_pCurrentScene = nullptr;
	};
}
