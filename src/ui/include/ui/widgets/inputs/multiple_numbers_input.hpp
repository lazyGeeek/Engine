#pragma once
#ifndef ENGINE_UI_WIDGETS_INPUTS_MULTIPLE_NUMBERS_INPUT_HPP_
#define ENGINE_UI_WIDGETS_INPUTS_MULTIPLE_NUMBERS_INPUT_HPP_

#include <array>

#include <imgui/imgui.h>

#include "tools/eventing/event.hpp"
#include "ui/widgets/base_widget.hpp"

namespace Engine::UI::Widgets::Inputs
{
    template<typename T, size_t Size>
    class MultipleNumbersInput : public BaseWidget
    {
        static_assert(std::is_arithmetic<T>::value, "MultipleNumbersInput T should be arithmetic value");
        static_assert(Size > 2, "MultipleNumbersInput number of elements shoulb be greater then 1");

    public:
        MultipleNumbersInput(const std::string& label,
            const std::array<T, Size>& values,
            T step,
            T fastStep,
            bool selectAllOnClick = false)
            : BaseWidget(label),
              m_values { values },
              m_step { step },
              m_fastStep { fastStep },
              m_selectAllOnClick { selectAllOnClick }
        {
            setFormat<T>();
        }

        virtual ~MultipleNumbersInput() override
        {
            ContentChangedEvent.RemoveAllListeners();
            EnterPressedEvent.RemoveAllListeners();
        }

        MultipleNumbersInput(const MultipleNumbersInput& other)             = delete;
        MultipleNumbersInput(MultipleNumbersInput&& other)                  = delete;
        MultipleNumbersInput& operator=(const MultipleNumbersInput& other)  = delete;
        MultipleNumbersInput& operator=(const MultipleNumbersInput&& other) = delete;

        virtual bool IsSelectAllOnClick() const { return m_selectAllOnClick; }

        virtual const std::array<T, Size>& GetValues() const { return m_values; }

        virtual T GetStep()     const { return m_step; }
        virtual T GetFastStep() const { return m_fastStep; }

        virtual void SetSelectAllOnClick(bool value) { m_selectAllOnClick = value; }

        virtual void SetValue(const std::array<T, Size>& value) { m_values = value; }

        virtual void SetStep(T step)         { m_step = step; }
        virtual void SetFastStep(T fastStep) { m_fastStep = fastStep; }

        Tools::Eventing::Event<std::array<T, Size>&> ContentChangedEvent;
        Tools::Eventing::Event<std::array<T, Size>&> EnterPressedEvent;

    protected:
        virtual void DrawImpl() override
        {
            std::array<T, Size> previousValues = m_values;

            ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
            if (m_selectAllOnClick)
                flags |= ImGuiInputTextFlags_AutoSelectAll;

            bool enterPressed = ImGui::InputScalarN((m_label + m_widgetId).c_str(), m_dataType,
                m_values.data(), Size, m_step != 0.0f ? &m_step : nullptr,
                m_fastStep != 0.0f ? &m_fastStep : nullptr, m_format.c_str(), flags);

            for (int i = 0; i < Size; ++i)
            {
                if (previousValues[i] != m_values[i])
                {
                    ContentChangedEvent.Invoke(m_values);
                    break;
                }
            }

            if (enterPressed)
                EnterPressedEvent.Invoke(m_values);
        }

        std::array<T, Size> m_values;

        T m_step;
        T m_fastStep;

        std::string m_format = "%.3f";

        ImGuiDataType m_dataType = ImGuiDataType_Float;

        bool m_selectAllOnClick = false;

    private:
        template <typename T>
        void setFormat()
        {
            std::string name = typeid(T).name();

            if (name == "bool")
                throw std::runtime_error("MultipleNumbersInput doesn't support bool value");

            if (name == "float")
            {
                m_dataType = ImGuiDataType_Float;
                m_format = "%.3f";
                return;
            }

            if (name == "double")
            {
                m_dataType = ImGuiDataType_Double;
                m_format = "%.5f";
                return;
            }

            if (sizeof(T) * 8 == 8)
            {
                if (std::is_unsigned<T>::value)
                {
                    m_dataType = ImGuiDataType_U8;
                    m_format = "%u";
                    return;
                }

                m_dataType = ImGuiDataType_S8;
                m_format = "%d";
                return;
            }

            if (sizeof(T) * 8 == 16)
            {
                if (std::is_unsigned<T>::value)
                {
                    m_dataType = ImGuiDataType_U16;
                    m_format = "%u";
                    return;
                }

                m_dataType = ImGuiDataType_S16;
                m_format = "%d";
                return;
            }

            if (sizeof(T) * 8 == 32)
            {
                if (std::is_unsigned<T>::value)
                {
                    m_dataType = ImGuiDataType_U32;
                    m_format = "%u";
                    return;
                }

                m_dataType = ImGuiDataType_S32;
                m_format = "%d";
                return;
            }

            if (sizeof(T) * 8 == 64)
            {
                if (std::is_unsigned<T>::value)
                {
                    m_dataType = ImGuiDataType_U64;
                    m_format = "%llu";
                    return;
                }

                m_dataType = ImGuiDataType_S64;
                m_format = "%lld";
                return;
            }

            throw std::runtime_error("MultipleNumbersInput unsupported format");
        }
    };
}

#endif // ENGINE_UI_WIDGETS_INPUTS_MULTIPLE_NUMBERS_INPUT_HPP_
