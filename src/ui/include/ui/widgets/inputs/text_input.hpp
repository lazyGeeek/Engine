#pragma once
#ifndef ENGINE_UI_WIDGETS_INPUTS_TEXT_INPUT_HPP_
#define ENGINE_UI_WIDGETS_INPUTS_TEXT_INPUT_HPP_

#include "tools/eventing/event.hpp"
#include "ui/widgets/base_widget.hpp"

namespace Engine::UI::Widgets::Inputs
{
    class TextInput : public BaseWidget
    {
    public:
        TextInput(const std::string& label, const std::string& content,
            const std::string& hint = "", bool selectAllOnClick = false);
        virtual ~TextInput() override;

        TextInput(const TextInput& other)             = delete;
        TextInput(TextInput&& other)                  = delete;
        TextInput& operator=(const TextInput& other)  = delete;
        TextInput& operator=(const TextInput&& other) = delete;

        virtual bool IsSelectAllOnClick() const { return m_selectAllOnClick; }

        virtual const std::string& GetContent() const { return m_content; }
        virtual const std::string& GetHint()    const { return m_hint; }

        virtual void SetSelectAllOnClick(bool value) { m_selectAllOnClick = value; }

        virtual void SetContent(const std::string& content) { m_content = content; }
        virtual void SetHint(const std::string& hint)       { m_hint = hint; }

        Tools::Eventing::Event<std::string> ContentChangedEvent;
        Tools::Eventing::Event<std::string> EnterPressedEvent;

    protected:
        virtual void DrawImpl() override;

        std::string m_content = "";
        std::string m_hint    = "";

        bool m_selectAllOnClick = false;

    private:
        const int CONTENT_BUFFER_SIZE = 256;
    };
}

#endif // ENGINE_UI_WIDGETS_INPUTS_TEXT_INPUT_HPP_
