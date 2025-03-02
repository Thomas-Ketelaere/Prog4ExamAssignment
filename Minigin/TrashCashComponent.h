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

	private:
		void ExerciseTwo();
		void ExerciseThree();
		void TrashTheCash();
		void TrashTheCashGameObject();
		void TrashTheCashGameObjectAlt();

		static constexpr int m_AmountSteps{ 11 }; //1, 2, 4, 8, ..., 1024 (11 times)

		float m_StepArr[m_AmountSteps]{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
		float m_DurationArr[m_AmountSteps]{};
		float m_DurationGameObjectArr[m_AmountSteps]{};
		float m_DurationGameObjectAltArr[m_AmountSteps]{};
		
		const int m_MaxStepSize;
		int m_SampleAmount;

		bool m_CalcGraphOne;
		bool m_ShowGraphOne;

		bool m_CalcGraphGameObject;
		bool m_CalcGraphGameObjectAlt;
		bool m_ShowGraphGameObject;
		bool m_ShowGraphGameObjectAlt;
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
	transform local{};
public:
	int id{};
};

class gameobjectTransformPtr
{
	transform* local{};
public:
	int id{};
};


