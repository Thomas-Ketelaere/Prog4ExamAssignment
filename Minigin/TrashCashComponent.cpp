#include "TrashCashComponent.h"
#include "imgui.h"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <chrono>
#include "imgui_plot.h"




dae::TrashCashComponent::TrashCashComponent(GameObject* gameObject) :
    Component(gameObject),
    m_Number{ 0 },
    m_AmountSteps{ 11 }, //1, 2, 4, 8, ..., 1024 (11 times)
    m_SampleAmount{ 50 },
    m_MaxStepSize{ 1024 }
{
    m_DurationArr = new float[m_AmountSteps];
    m_StepArr = new float[m_AmountSteps] {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
}

dae::TrashCashComponent::~TrashCashComponent()
{
    if (m_DurationArr != nullptr)
    {
        delete[] m_DurationArr;
    }

    if (m_StepArr != nullptr)
    {
        delete[] m_StepArr;
    }
}

void dae::TrashCashComponent::Start()
{
    TrashTheCash();
    //TrashTheCastGameObjectAlt();
}

void dae::TrashCashComponent::Update()
{

}

void dae::TrashCashComponent::Render() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Begin a new ImGui window
    ImGui::Begin("Exercise 2");
    
    // Line Graph
    //ImGui::PlotLines("Line Graph", m_DurationArr, m_AmountSteps, 0, nullptr, 0.0f, 1.0f, ImVec2(0, 100));

    ImGui::PlotConfig conf;
    conf.values.xs = m_StepArr; 
    conf.values.ys = m_DurationArr;
    conf.values.count = m_AmountSteps;
    conf.scale.min = 0.f;
    conf.scale.max = *std::max_element(m_DurationArr, m_DurationArr + m_AmountSteps);
    conf.tooltip.show = true;
    conf.tooltip.format = "x=%.0f, y=%.3f";
    conf.grid_x.show = true;
    conf.grid_y.show = true;
    conf.frame_size = ImVec2(400, 200);
    conf.line_thickness = 2.f;

    ImGui::Plot("Exercise 2 graph", conf);

    ImGui::InputInt("Value", const_cast<int*>(&m_Number), 0, 0);

    ImGui::SameLine();
    if (ImGui::Button("+"))
    {
        //m_Number++;
    }

    ImGui::SameLine();
    if (ImGui::Button("-"))
    {
       // m_Number--;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void dae::TrashCashComponent::TrashTheCash()
{
    //int stepCounter{};
    int arraySize = 99999999;
	int* arr = new int[arraySize] {};

    std::vector<float> durationVct{};

    for (int sampleCounter{}; sampleCounter < m_SampleAmount; ++sampleCounter)
    {
        for (int stepsize = 1; stepsize <= m_MaxStepSize; stepsize *= 2)
        {
            const auto currentTime = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < arraySize; i += stepsize)
            {
                arr[i] *= 2;
            }
            const auto endTime = std::chrono::high_resolution_clock::now();
            durationVct.emplace_back(std::chrono::duration<float>(endTime - currentTime).count());

            //m_DurationArr[stepCounter] = std::chrono::duration<float>(endTime - currentTime).count();
            //++stepCounter;
        }
    }

    for (int i = 0; i < m_AmountSteps; ++i)
    {
        float sum{};
        for (int j = 0; j < m_SampleAmount; ++j)
        {
            sum += durationVct[i + j * m_AmountSteps];
        }
        m_DurationArr[i] = sum / m_SampleAmount;
    }

	
	//for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	//{
	//	const auto currentTime = std::chrono::high_resolution_clock::now();
	//	for (int i = 0; i < arraySize; i += stepsize)
	//	{
	//		arr[i] *= 2;
	//	}
	//	const auto endTime = std::chrono::high_resolution_clock::now();
 //       m_DurationArr[stepCounter] = std::chrono::duration<float>(endTime - currentTime).count();
 //       m_StepArr[stepCounter] = float(stepsize);
 //       ++stepCounter;
	//}

	delete[] arr;
}

void dae::TrashCashComponent::TrashTheCashGameObject()
{
    int stepCounter{};
    int arraySize = 99999999;
    gameobject* arr = new gameobject[arraySize]{};

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < arraySize; i += stepsize)
        {
            arr[i].id *= 2;
        }
        const auto endTime = std::chrono::high_resolution_clock::now();
        m_DurationArr[stepCounter] = std::chrono::duration<float>(endTime - currentTime).count();
        m_StepArr[stepCounter] = float(stepsize);
        ++stepCounter;
    }

    delete[] arr;
}

void dae::TrashCashComponent::TrashTheCastGameObjectAlt()
{
    int stepCounter{};
    int arraySize = 99999999;
    gameobjectTransformPtr* arr = new gameobjectTransformPtr[arraySize]{};

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < arraySize; i += stepsize)
        {
            arr[i].id *= 2;
        }
        const auto endTime = std::chrono::high_resolution_clock::now();
        m_DurationArr[stepCounter] = std::chrono::duration<float>(endTime - currentTime).count();
        m_StepArr[stepCounter] = float(stepsize);
        ++stepCounter;
    }

    delete[] arr;
}
