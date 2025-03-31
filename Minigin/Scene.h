#pragma once
#include <string>
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);

		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Start();
		void Update();
		void LateUpdate();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_Objects{};

		static unsigned int m_idCounter; 
	};

}
