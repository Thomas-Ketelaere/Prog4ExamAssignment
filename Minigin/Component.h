#pragma once

namespace dae
{
	class GameObject;
	class TransformComponent;
	class Component
	{
	public:
		Component(GameObject* gameObject);
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void FixedUpdate() {}
		virtual void Render() const {}

		bool IsMarkedDestroy() { return m_Destroy; }

		virtual void Destroy()
		{
			m_Destroy = true;
		}
	

		GameObject* GetGameObject() const { return m_pGameObject; }
		TransformComponent* GetTransform() const { return m_pTransform; }

	private:

		GameObject* m_pGameObject = nullptr; 
		TransformComponent* m_pTransform = nullptr; //pointer to one transform from GameObject

		bool m_Destroy{};
	};
}


