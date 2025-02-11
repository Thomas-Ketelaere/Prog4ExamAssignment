#pragma once
namespace dae
{
	class GameObject;
	class Transform;
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Start() {}
		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void Render() const {}
		
		GameObject* GetGameObject() const { return m_pGameObject; }
		Transform* GetTransform() const { return m_pTransform; }

	private:
		friend class GameObject;

		GameObject* m_pGameObject = nullptr; 
		Transform* m_pTransform = nullptr; // every component will have a transform, so we just add it in here, instead of adding it to every individual one

	};
}


