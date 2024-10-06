#pragma once
#ifndef ENGINE_UI_WIDGETS_INPUTS_SINGLE_NUMBER_INPUT_HPP_
#define ENGINE_UI_WIDGETS_INPUTS_SINGLE_NUMBER_INPUT_HPP_

#include <imgui/imgui.h>

#include "tools/eventing/event.hpp"
#include "ui/widgets/base_widget.hpp"

namespace Engine::UI::Widgets::Inputs
{
    template<typename T>
    class SingleNumberInput : public BaseWidget
    {
        static_assert(std::is_arithmetic<T>::value, "SingleNumberInput T should be arithmetic value");

    public:
        SingleNumberInput(const std::string& label,
            T value,
            T step,
            T fastStep,
            bool selectAllOnClick = false)
            : BaseWidget(label),
              m_value { value },
              m_step { step },
              m_fastStep { fastStep },
              m_selectAllOnClick { selectAllOnClick }
        {
            setFormat<T>();
        }

        virtual ~SingleNumberInput() override
        {
            ContentChangedEvent.RemoveAllListeners();
            EnterPressedEvent.RemoveAllListeners();
        }

        SingleNumberInput(const SingleNumberInput& other)             = delete;
        SingleNumberInput(SingleNumberInput&& other)                  = delete;
        SingleNumberInput& operator=(const SingleNumberInput& other)  = delete;
        SingleNumberInput& operator=(const SingleNumberInput&& other) = delete;

        virtual bool IsSelectAllOnClick() const { return m_selectAllOnClick; }

        virtual T GetValue()    const { return m_value; }
        virtual T GetStep()     const { return m_step; }
        virtual T GetFastStep() const { return m_fastStep; }

        virtual void SetSelectAllOnClick(bool value) { m_selectAllOnClick = value; }

        virtual void SetValue(T value)       { m_value = value; }
        virtual void SetStep(T step)         { m_step = step; }
        virtual void SetFastStep(T fastStep) { m_fastStep = fastStep; }

        Tools::Eventing::Event<T> ContentChangedEvent;
        Tools::Eventing::Event<T> EnterPressedEvent;

    protected:
        virtual void DrawImpl() override
        {
            T previousValue = m_value;

            ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
            if (m_selectAllOnClick)
                flags |= ImGuiInputTextFlags_AutoSelectAll;

            bool enterPressed = ImGui::InputScalar((m_label + m_widgetId).c_str(), m_dataType,
                &m_value, m_step != 0.0f ? &m_step : nullptr,
                m_fastStep != 0.0f ? &m_fastStep : nullptr, m_format.c_str(), flags);

            if (previousValue != m_value)
                ContentChangedEvent.Invoke(m_value);

            if (enterPressed)
                EnterPressedEvent.Invoke(m_value);
        }

        T m_value;
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
                throw std::runtime_error("SingleNumberInput doesn't support bool value");

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

            throw std::runtime_error("SingleNumberInput unsupported format");
        }
    };
}

#endif // ENGINE_UI_WIDGETS_INPUTS_SINGLE_NUMBER_INPUT_HPP_
