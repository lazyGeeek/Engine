#pragma once
#ifndef ENGINE_UI_WIDGETS_DRAGS_MULTI_DRAG_HPP_
#define ENGINE_UI_WIDGETS_DRAGS_MULTI_DRAG_HPP_

#include <array>

#include <imgui/imgui.h>

#include "tools/eventing/event.hpp"
#include "ui/widgets/base_widget.hpp"

namespace Engine::UI::Widgets::Drags
{
    template <typename T, size_t Size>
    class MultiDrag : public BaseWidget
    {
        static_assert(std::is_arithmetic<T>::value, "MultiDrag T should be arithmetic value");
        static_assert(Size > 2, "MultiDrag number of elements shoulb be greater then 1");

    public:
        MultiDrag(
            T min, T max,
            const std::array<T, Size>& values,
            float speed,
            const std::string& label)
            : m_min { min }, m_max { max }, m_values { values },
              m_speed { speed }, m_label { label }
        {
            setFormat<T>();
        }

        virtual ~MultiDrag()
        {
            ValueChangedEvent.RemoveAllListeners();
        }

        MultiDrag(const MultiDrag& other)             = delete;
        MultiDrag(MultiDrag&& other)                  = delete;
        MultiDrag& operator=(const MultiDrag& other)  = delete;
        MultiDrag& operator=(const MultiDrag&& other) = delete;

        virtual T GetMinValue()              const { return m_min; }
        virtual T GetMaxValue()              const { return m_max; }
        virtual float GetSpeed()             const { return m_speed; }
        virtual const std::string& GetText() const { return m_label; }

        virtual const std::array<T, Size>& GetValues() const { return m_values; }

        virtual void SetMinValue(T min)               { m_min = min; }
        virtual void SetMaxValue(T max)               { m_max = max; }
        virtual void SetSpeed(float speed)            { m_speed = speed; }
        virtual void SetText(const std::string& text) { m_label = text; }

        virtual void SetValues(const std::array<T, Size>& values) { m_values = values; }

        Tools::Eventing::Event<std::array<T, Size>&> ValueChangedEvent;

    protected:
        virtual void DrawImpl() override
        {
            if (m_max < m_min)
                m_max = m_min;

            for (size_t i = 0; i < Size; ++i)
            {
                if (m_values[i] < m_min)
                    m_values[i] = m_min;

                if (m_values[i] > m_max)
                    m_values[i] = m_max;
            }

            if (ImGui::DragScalarN((m_label + m_widgetId).c_str(), m_dataType, m_values.data(), Size, m_speed, &m_min, &m_max, m_format.c_str()))
                ValueChangedEvent.Invoke(m_values);
        }

        T m_min;
        T m_max;
        std::array<T, Size> m_values;

        float m_speed        = 1.0f;
        std::string m_label  = "";
        std::string m_format = "";

        ImGuiDataType m_dataType = ImGuiDataType_Float;

    private:
        template <typename T>
        void setFormat()
        {
            std::string name = typeid(T).name();

            if (name == "bool")
                throw std::runtime_error("MultiDrag doesn't support bool value");

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

            throw std::runtime_error("MultiDrag unsupported format");
        }
    };
}

#endif // ENGINE_UI_WIDGETS_DRAGS_MULTI_DRAG_HPP_
