#pragma once
#include "Component.h"
#include "vector"

namespace dae
{
	class TrashCashComponent : public Component
	{
	public:
		TrashCashComponent(GameObject* gameObject);
		~TrashCashComponent();

		virtual void Start() override;
		virtual void Update() override;
		virtual void Render() const override;

	private:
		void TrashTheCash();
		void TrashTheCashGameObject();
		void TrashTheCastGameObjectAlt();

		float* m_DurationArr;
		float* m_StepArr;
		//std::vector<float> m_DurationVct;
		const int m_AmountSteps;

		int m_Number;
	};
}

struct transform
{
	float matrix[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
};

class gameobject
{
	transform local;
public:
	int id;
};

class gameobjectTransformPtr
{
	transform* local;
public:
	int id;
};


