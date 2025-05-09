#pragma once
#include <memory>
#include "TransformComponent.h"
#include <vector>

namespace RamCoreEngine
{
	class Texture2D;
	class Component;
	// todo: this should become final.
	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Start();
		void Update();
		void LateUpdate();
		void Render() const;

		bool IsMarkedDestroy() { return m_Destroy; }

		void AddComponent(std::unique_ptr<Component> newComponent);
		void SetWorldPosition(float x, float y);

		void SetParent(GameObject* parentUPtr, bool keepWorldPosition);
		void SetLocalPosition(const glm::vec3& position);
		void SetPositionDirty();
		void UpdateWorldPosition();
		bool IsChild(GameObject* child);

		void SetTag(unsigned int tag) { m_Tag = tag; }
		unsigned int GetTag() const { return m_Tag; }

		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition();

		const std::vector<GameObject*>& GetChildren() { return m_Children; }
		GameObject* GetParent() const { return m_Parent; }
		TransformComponent* GetTransform();
		
		void Destroy() { m_Destroy = true; }

		template <typename T>
		T* GetComponent() const;

	private:
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);

		TransformComponent* m_Transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::vector<std::unique_ptr<Component>> m_ComponentsVector;
		std::vector<GameObject*> m_Children;
		GameObject* m_Parent{ nullptr };
		bool m_Destroy;
		bool m_PositionIsDirty{};

		unsigned int m_Tag{};
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
