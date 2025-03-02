#include "TrashCashComponent.h"
#include "imgui.h"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <chrono>
#include "imgui_plot.h"



dae::TrashCashComponent::TrashCashComponent(GameObject* gameObject) :
    Component(gameObject),
    m_SampleAmount{ 10 },
    m_MaxStepSize{ 1024 },
    m_CalcGraphOne{},
    m_ShowGraphOne{},
    m_CalcGraphGameObject{},
    m_CalcGraphGameObjectAlt{},
    m_ShowGraphGameObject{},
    m_ShowGraphGameObjectAlt{}
{
}

dae::TrashCashComponent::~TrashCashComponent()
{
}

void dae::TrashCashComponent::Start()
{
}

void dae::TrashCashComponent::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // ExerciseTwo
    ExerciseTwo();

    //Exercise 3
    ExerciseThree();
}

void dae::TrashCashComponent::ExerciseTwo()
{
    ImGui::Begin("Exercise 2");

    // Line Graph
    //ImGui::PlotLines("Line Graph", m_DurationArr, m_AmountSteps, 0, nullptr, 0.0f, 1.0f, ImVec2(0, 100));

    ImGui::InputInt("# Samples", &m_SampleAmount, 0, 0);

    if (ImGui::Button("+"))
    {
        ++m_SampleAmount;
    }

    ImGui::SameLine();
    if (ImGui::Button("-"))
    {
        --m_SampleAmount;
    }

    if (m_CalcGraphOne)
    {

        TrashTheCash();
        m_CalcGraphOne = false;
        m_ShowGraphOne = true;
    }
    else
    {
        if (ImGui::Button("Trash The Cash"))
        {
            m_CalcGraphOne = true;
            ImGui::Text("Calculating");
        }
    }

    if (m_ShowGraphOne)
    {
        ImGui::PlotConfig conf;
        conf.values.xs = m_StepArr;
        conf.values.ys = m_DurationArr;
        conf.values.count = m_AmountSteps;
        conf.scale.min = 0.f;
        conf.scale.max = *std::max_element(m_DurationArr, m_DurationArr + m_AmountSteps);
        conf.tooltip.show = true;
        conf.tooltip.format = "x=%.0f, y=%.3f";
        conf.frame_size = ImVec2(150, 100);
        conf.line_thickness = 2.f;
        conf.values.color = IM_COL32(255, 255, 0, 255);

        ImGui::Plot("Exercise 2 graph", conf);
    }
    ImGui::End();
}

void dae::TrashCashComponent::ExerciseThree()
{
    ImGui::Begin("Exercise 3");

    ImGui::InputInt("# Samples", &m_SampleAmount, 0, 0);

    if (ImGui::Button("+"))
    {
        ++m_SampleAmount;
    }

    ImGui::SameLine();
    if (ImGui::Button("-"))
    {
        --m_SampleAmount;
    }

    if (m_CalcGraphGameObject)
    {
        TrashTheCashGameObject();
        m_CalcGraphGameObject = false;
        m_ShowGraphGameObject = true;
    }
    else
    {
        if (ImGui::Button("Trash The Cash: Game Object"))
        {
            m_CalcGraphGameObject = true;
            ImGui::Text("Calculating");
        }
    }

    if (m_ShowGraphGameObject)
    {
        ImGui::PlotConfig conf;
        conf.values.xs = m_StepArr;
        conf.values.ys = m_DurationGameObjectArr;
        conf.values.count = m_AmountSteps;
        conf.scale.min = 0.f;
        conf.scale.max = *std::max_element(m_DurationGameObjectArr, m_DurationGameObjectArr + m_AmountSteps);
        conf.tooltip.show = true;
        conf.tooltip.format = "x=%.0f, y=%.3f";
        conf.frame_size = ImVec2(150, 100);
        conf.line_thickness = 2.f;
        conf.values.color = IM_COL32(0, 255, 255, 255);

        ImGui::Plot("Exercise 3 graph", conf);
    }

    if (m_CalcGraphGameObjectAlt)
    {
        TrashTheCashGameObjectAlt();
        m_CalcGraphGameObjectAlt = false;
        m_ShowGraphGameObjectAlt = true;
    }
    else
    {
        if (ImGui::Button("Trash The Cash: Game Object Alternative"))
        {
            m_CalcGraphGameObjectAlt = true;
            ImGui::Text("Calculating");
        }
    }

    if (m_ShowGraphGameObjectAlt)
    {
        ImGui::PlotConfig conf;
        conf.values.xs = m_StepArr;
        conf.values.ys = m_DurationGameObjectAltArr;
        conf.values.count = m_AmountSteps;
        conf.scale.min = 0.f;
        conf.scale.max = *std::max_element(m_DurationGameObjectAltArr, m_DurationGameObjectAltArr + m_AmountSteps);
        conf.tooltip.show = true;
        conf.tooltip.format = "x=%.0f, y=%.3f";
        conf.frame_size = ImVec2(150, 100);
        conf.line_thickness = 2.f;
        conf.values.color = IM_COL32(255, 0, 0, 255);


        ImGui::Plot("Exercise 3 alt graph", conf);
    }

    //combined graph
    if (m_ShowGraphGameObject && m_ShowGraphGameObjectAlt)
    {
        ImGui::Text("Combined: ");
        auto maxScale{ std::max_element(std::max_element(m_DurationGameObjectArr, m_DurationGameObjectArr + m_AmountSteps), std::max_element(m_DurationGameObjectAltArr, m_DurationGameObjectAltArr + m_AmountSteps)) };

        const float* combinedArr[2]{ m_DurationGameObjectArr, m_DurationGameObjectAltArr };
        unsigned int colors[2] = { IM_COL32(0, 255, 255, 255), IM_COL32(255, 0, 0, 255) };
        ImGui::PlotConfig conf;
        conf.values.xs = m_StepArr;
        conf.values.ys_list = combinedArr;
        conf.values.ys_count = 2;
        conf.values.count = m_AmountSteps;
        conf.scale.min = 0.f;
        conf.scale.max = *maxScale;
        conf.tooltip.show = true;
        conf.tooltip.format = "x=%.0f, y=%.3f";
        conf.frame_size = ImVec2(150, 100);
        conf.line_thickness = 2.f;
        conf.values.colors = colors;

        ImGui::Plot("Exercise combined graph", conf);
    }

    ImGui::End();
}

void dae::TrashCashComponent::TrashTheCash()
{
    //int stepCounter{};
    int arraySize = int(pow(2, 26));
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

        }
    }

    for (int stepCounter = 0; stepCounter < m_AmountSteps; ++stepCounter)
    {
        float sum{};
        for (int sampleCounter = 0; sampleCounter < m_SampleAmount; ++sampleCounter)
        {
            sum += durationVct[stepCounter + sampleCounter * m_AmountSteps];
        }
        m_DurationArr[stepCounter] = sum / m_SampleAmount;
    }

	delete[] arr;
}

void dae::TrashCashComponent::TrashTheCashGameObject()
{
    int arraySize = int(pow(2, 23));
    gameobject* arr = new gameobject[arraySize]{};

    std::vector<float> durationVct{};
    for (int sampleCounter{}; sampleCounter < m_SampleAmount; ++sampleCounter)
    {
        for (int stepsize = 1; stepsize <= m_MaxStepSize; stepsize *= 2)
        {
            const auto currentTime = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < arraySize; i += stepsize)
            {
                arr[i].id *= 2;
            }
            const auto endTime = std::chrono::high_resolution_clock::now();
            durationVct.emplace_back(std::chrono::duration<float>(endTime - currentTime).count());
        }
    }
    

    for (int stepCounter = 0; stepCounter < m_AmountSteps; ++stepCounter)
    {
        float sum{};
        for (int sampleCounter = 0; sampleCounter < m_SampleAmount; ++sampleCounter)
        {
            sum += durationVct[stepCounter + sampleCounter * m_AmountSteps];
        }
        m_DurationGameObjectArr[stepCounter] = sum / m_SampleAmount;
    }

    delete[] arr;
}

void dae::TrashCashComponent::TrashTheCashGameObjectAlt()
{
    int arraySize = int(pow(2, 23));
    gameobjectTransformPtr* arr = new gameobjectTransformPtr[arraySize]{};

    std::vector<float> durationVct{};

    for (int sampleCounter{}; sampleCounter < m_SampleAmount; ++sampleCounter)
    {
        for (int stepsize = 1; stepsize <= m_MaxStepSize; stepsize *= 2)
        {
            const auto currentTime = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < arraySize; i += stepsize)
            {
                arr[i].id *= 2;
            }
            const auto endTime = std::chrono::high_resolution_clock::now();
            durationVct.emplace_back(std::chrono::duration<float>(endTime - currentTime).count());
        }
    }

    for (int stepCounter = 0; stepCounter < m_AmountSteps; ++stepCounter)
    {
        float sum{};
        for (int sampleCounter = 0; sampleCounter < m_SampleAmount; ++sampleCounter)
        {
            sum += durationVct[stepCounter + sampleCounter * m_AmountSteps];
        }
        m_DurationGameObjectAltArr[stepCounter] = sum / m_SampleAmount;
    }

    delete[] arr;
}
