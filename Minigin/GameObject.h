#pragma once
#include <memory>
#include "Transform.h"
#include <vector>

namespace dae
{
	class Texture2D;
	class Component;
	// todo: this should become final.
	class GameObject
	{
	public:
		void Start();
		virtual void Update();
		virtual void Render() const;

		void AddComponent(std::unique_ptr<Component> newComponent);
		template <typename T>
		T* GetComponent() const;

		void SetPosition(float x, float y);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform* m_Transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::vector<std::shared_ptr<Component>> m_ComponentsVector;
	};

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		for (auto& component : m_ComponentsVector)
		{
			T* tempComponnent = dynamic_cast<T*>(component.get()); //does the same as "is valid" in unreal
			if (tempComponnent != nullptr)
			{
				return tempComponnent;
			}
		}
		return nullptr;
	}
}
