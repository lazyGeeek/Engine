#pragma once
#ifndef ENGINE_LOGS_LOGGER_PANEL_HPP_
#define ENGINE_LOGS_LOGGER_PANEL_HPP_

#include "tools/eventing/event.hpp"
#include "logs/log_level.hpp"
#include "ui/panels/window_panel.hpp"

#include <deque>

namespace Engine::UI::Widgets::Buttons
{
    class Button;
}

namespace Engine::UI::Widgets::Layouts
{
    class Group;
}

namespace Engine::UI::Widgets::Selections
{
    class CheckBox;
}

namespace Engine::UI::Widgets::Texts
{
    class ColoredText;
    class TextFilter;
}

namespace Engine::Logs
{
    struct LogMessage
    {
        ELogLevel Level;
        std::shared_ptr<UI::Widgets::Texts::ColoredText> UIText;
    };

    class LoggerPanel : public UI::Panels::WindowPanel
    {
    public:
        LoggerPanel();
        ~LoggerPanel();

        LoggerPanel(const LoggerPanel& other)             = delete;
        LoggerPanel(LoggerPanel&& other)                  = delete;
        LoggerPanel& operator=(const LoggerPanel& other)  = delete;
        LoggerPanel& operator=(const LoggerPanel&& other) = delete;

    protected:
        void DrawImpl() override;

    private:
        bool isFiltered(const LogMessage& message);
        void toggleMessagesByLevel(ELogLevel level, bool value);
        void addLogMessage(ELogLevel level, const std::string& message);
        void clearButtonClicked();

        const uint8_t LOG_DEQUE_SIZE = 1000;
        std::deque<LogMessage> m_logDeque;

        std::shared_ptr<UI::Widgets::Buttons::Button> m_clearButton   = nullptr;
        std::shared_ptr<UI::Widgets::Buttons::Button> m_showAllButton = nullptr;

        std::shared_ptr<Engine::UI::Widgets::Selections::CheckBox> m_debugCheckBox   = nullptr;
        std::shared_ptr<Engine::UI::Widgets::Selections::CheckBox> m_infoCheckBox    = nullptr;
        std::shared_ptr<Engine::UI::Widgets::Selections::CheckBox> m_warningCheckBox = nullptr;
        std::shared_ptr<Engine::UI::Widgets::Selections::CheckBox> m_errorCheckBox   = nullptr;

        std::shared_ptr<UI::Widgets::Layouts::Group> m_logMessagesGroup = nullptr;
        std::shared_ptr<UI::Widgets::Texts::TextFilter> m_textFilter    = nullptr;
        std::string m_textFilterOld = "";

        Tools::Eventing::ListenerID m_logRecieveListener = 0;
    };
}

#endif // ENGINE_LOGS_LOGGER_PANEL_HPP_
