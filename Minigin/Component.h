#pragma once

namespace dae
{
	class GameObject;
	class Transform;
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
		Transform* GetTransform() const { return m_pTransform; }

	private:
		//friend class GameObject;

		GameObject* m_pGameObject = nullptr; 
		Transform* m_pTransform = nullptr; //pointer to one transform from GameObject

		bool m_Destroy{};
	};
}


