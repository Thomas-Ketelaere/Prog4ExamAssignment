#pragma once
#include <string>
#include <functional>
#include "GameObject.h"

namespace RamCoreEngine
{
	class Scene final
	{
	public:
		explicit Scene(unsigned int name);

		void LoadScene() { m_LoadingFunction(); }
		void ReloadScene();
		void SetLoadingFunction(const std::function<void()>& load) { m_LoadingFunction = load; }

		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Start();
		void Update();
		void LateUpdate();
		void Render() const;

		unsigned int GetName() { return m_Name; } 
		bool IsMarkedDestroy() { return m_Destroy; }
		bool IsMarkedReload() { return m_ShouldReload; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Destroy() { m_Destroy = true; }
		void MarkForReload() { m_ShouldReload = true; }

		std::vector<GameObject*> GetAllObjectsWithTag(unsigned int tag);
		GameObject* GetFirstObjectWithTag(unsigned int tag);

	private: 
		unsigned int m_Name;
		std::vector < std::unique_ptr<GameObject>> m_Objects{};
		std::function<void()> m_LoadingFunction;

		bool m_Destroy;
		bool m_ShouldReload;

		static unsigned int m_idCounter; 
	};

}
