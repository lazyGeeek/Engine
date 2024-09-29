#pragma once
#ifndef ENGINE_UI_WIDGETS_DRAGS_SINGLE_DRAG_HPP_
#define ENGINE_UI_WIDGETS_DRAGS_SINGLE_DRAG_HPP_

#include <imgui/imgui.h>

#include "tools/eventing/event.hpp"
#include "ui/widgets/base_widget.hpp"

namespace Engine::UI::Widgets::Drags
{
    template <typename T>
    class SingleDrag : public BaseWidget
    {
        static_assert(std::is_arithmetic<T>::value, "SingleDrag T should be arithmetic value");

    public:
        SingleDrag(
            T min, T max, T value,
            float speed,
            const std::string& label)
            : m_min { min }, m_max { max }, m_value { value },
              m_speed { speed }, m_label { label }
        {
            setFormat<T>();
        }

        virtual ~SingleDrag()
        {
            ValueChangedEvent.RemoveAllListeners();
        }

        SingleDrag(const SingleDrag& other)             = delete;
        SingleDrag(SingleDrag&& other)                  = delete;
        SingleDrag& operator=(const SingleDrag& other)  = delete;
        SingleDrag& operator=(const SingleDrag&& other) = delete;

        virtual T GetMinValue()              const { return m_min; }
        virtual T GetMaxValue()              const { return m_max; }
        virtual T GetValue()                 const { return m_value; }
        virtual float GetSpeed()             const { return m_speed; }
        virtual const std::string& GetText() const { return m_label; }

        virtual void SetMinValue(T min)               { m_min = min; }
        virtual void SetMaxValue(T max)               { m_max = max; }
        virtual void SetValue(T value)                { m_value = value; }
        virtual void SetSpeed(float speed)            { m_speed = speed; }
        virtual void SetText(const std::string& text) { m_label = text; }

        Tools::Eventing::Event<T> ValueChangedEvent;

    protected:
        virtual void DrawImpl() override
        {
            if (m_max < m_min)
                m_max = m_min;

            if (m_value < m_min)
                m_value = m_min;

            if (m_value > m_max)
                m_value = m_max;

            std::string name = typeid(m_value).name();
            if (name == "bool")
            {
                m_format = m_value ? "True" : "False";
                if (ImGui::DragScalar((m_label + m_widgetId).c_str(), m_dataType, &m_value, m_speed, &m_min, &m_max, m_format.c_str()))
                    ValueChangedEvent.Invoke(m_value);
            }
            else
            {
                if (ImGui::DragScalar((m_label + m_widgetId).c_str(), m_dataType, &m_value, m_speed, &m_min, &m_max, m_format.c_str()))
                    ValueChangedEvent.Invoke(m_value);
            }
        }

        T m_min;
        T m_max;
        T m_value;

        float m_speed        = 1.0f;
        std::string m_label  = "";
        std::string m_format = "";

        ImGuiDataType m_dataType = ImGuiDataType_Float;

    private:
        template <typename T>
        void setFormat()
        {
            std::string name = typeid(T).name();

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

            if (name == "bool")
            {
                m_dataType = ImGuiDataType_U8;
                m_min = false;
                m_max = true;
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

            throw std::runtime_error("SingleDrag unsupported format");
        }
    };
}

#endif // ENGINE_UI_WIDGETS_DRAGS_SINGLE_DRAG_HPP_
