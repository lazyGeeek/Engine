// #include "logs/logger_panel.hpp"
// #include "logs/logger.hpp"

// #include "ui/widgets/buttons/button.hpp"
// #include "ui/widgets/selections/check_box.hpp"
// #include "ui/widgets/texts/colored_text.hpp"
// #include "ui/widgets/layouts/group.hpp"
// #include "ui/widgets/texts/text.hpp"
// #include "ui/widgets/texts/text_filter.hpp"

// #include <imgui/imgui.h>

// using UIButton         = Engine::UI::Widgets::Buttons::Button;
// using UICheckBox       = Engine::UI::Widgets::Selections::CheckBox;
// using UICheckBoxPtr    = std::shared_ptr<UICheckBox>;
// using UIColor          = Engine::UI::Types::Color;
// using UIColoredText    = Engine::UI::Widgets::Texts::ColoredText;
// using UIColoredTextPtr = std::shared_ptr<UIColoredText>;
// using UIGroup          = Engine::UI::Widgets::Layouts::Group;
// using UITextFilter     = Engine::UI::Widgets::Texts::TextFilter;


// namespace Engine::Logs
// {
//     LoggerPanel::LoggerPanel()
//         : UI::Panels::WindowPanel("Logger")
//     {
//         m_logDeque.clear();

//         m_clearButton = CreateWidget<UIButton>("Clear");
//         m_clearButton->SetSize(glm::vec2(65.0f, 25.0f));
//         m_clearButton->SetSameLine(true);
//         m_clearButton->ClickedEvent += std::bind(&LoggerPanel::clearButtonClicked, this);

//         m_textFilter = CreateWidget<UITextFilter>();
//         m_textFilterOld = m_textFilter->GetFilterText();

//         m_debugCheckBox = CreateWidget<UICheckBox>("Debug", true);
//         m_debugCheckBox->SetSameLine(true);
//         m_debugCheckBox->ValueChangedEvent += [this](bool value)
//         {
//             toggleMessagesByLevel(ELogLevel::Debug, value);
//         };

//         m_infoCheckBox = CreateWidget<UICheckBox>("Info", true);
//         m_infoCheckBox->SetSameLine(true);
//         m_infoCheckBox->ValueChangedEvent += [this](bool value)
//         {
//             toggleMessagesByLevel(ELogLevel::Info, value);
//         };

//         m_warningCheckBox = CreateWidget<UICheckBox>("Warning", true);
//         m_warningCheckBox->SetSameLine(true);
//         m_warningCheckBox->ValueChangedEvent += [this](bool value)
//         {
//             toggleMessagesByLevel(ELogLevel::Warning, value);
//         };

//         m_errorCheckBox = CreateWidget<UICheckBox>("Error", true);
//         m_errorCheckBox->SetSameLine(true);
//         m_errorCheckBox->ValueChangedEvent += [this](bool value)
//         {
//             toggleMessagesByLevel(ELogLevel::Error, value);
//         };

//         m_showAllButton = CreateWidget<UIButton>("Show All");
//         m_showAllButton->SetSize(glm::vec2(65.0f, 25.0f));
//         m_showAllButton->ClickedEvent += [this]()
//         {
//             m_debugCheckBox->SetValue(true);
//             m_infoCheckBox->SetValue(true);
//             m_warningCheckBox->SetValue(true);
//             m_errorCheckBox->SetValue(true);
//         };

//         m_logMessagesGroup = CreateWidget<UIGroup>();

//         m_logRecieveListener = Logger::LogMessageReceived +=
//             std::bind(&LoggerPanel::addLogMessage, this, std::placeholders::_1, std::placeholders::_2);
//     }

//     LoggerPanel::~LoggerPanel()
//     {
//         Logger::LogMessageReceived -= m_logRecieveListener;

//         m_clearButton->ClickedEvent.RemoveAllListeners();
//         m_showAllButton->ClickedEvent.RemoveAllListeners();
//         m_debugCheckBox->ValueChangedEvent.RemoveAllListeners();
//         m_infoCheckBox->ValueChangedEvent.RemoveAllListeners();
//         m_warningCheckBox->ValueChangedEvent.RemoveAllListeners();
//         m_errorCheckBox->ValueChangedEvent.RemoveAllListeners();

//         clearButtonClicked();
//     }

//     void LoggerPanel::DrawImpl()
//     {
//         std::string newFilter = m_textFilter->GetFilterText();

//         if (newFilter != m_textFilterOld)
//         {
//             for (LogMessage& log : m_logDeque)
//             {
//                 UIColoredTextPtr& uiText = log.UIText;
//                 if (isFiltered(log) || !m_textFilter->PassFilter(uiText->GetContent()))
//                     uiText->SetEnabled(false);
//                 else
//                     uiText->SetEnabled(true);
//             }

//             m_textFilterOld = newFilter;
//         }

//         UI::Panels::WindowPanel::DrawImpl();
//     }

//     void LoggerPanel::toggleMessagesByLevel(ELogLevel level, bool value)
//     {
//         for (LogMessage& message : m_logDeque)
//         {
//             if (message.Level == level && m_textFilter->PassFilter(message.UIText->GetContent()))
//                 message.UIText->SetEnabled(value);
//         }
//     }

//     bool LoggerPanel::isFiltered(const LogMessage& message)
//     {
//         switch (message.Level)
//         {
//             case ELogLevel::Debug:
//                 return !m_debugCheckBox->GetValue();

//             case ELogLevel::Info:
//                 return !m_infoCheckBox->GetValue();

//             case ELogLevel::Warning:
//                 return !m_warningCheckBox->GetValue();

//             case ELogLevel::Error:
//                 return !m_errorCheckBox->GetValue();
//         }

//         return false;
//     }

//     void LoggerPanel::addLogMessage(ELogLevel level, const std::string& message)
//     {
//         LogMessage newMessage;
//         newMessage.Level = level;

//         UIColor color = UIColor::White;

//         switch (level)
//         {
//             case ELogLevel::Info:
//             {
//                 color = UIColor::Cyan;
//                 break;
//             }
//             case ELogLevel::Warning:
//             {
//                 color = UIColor::Yellow;
//                 break;
//             }
//             case ELogLevel::Error:
//             {
//                 color = UIColor::Red;
//                 break;
//             }
//             case ELogLevel::Debug:
//             default:
//             {
//                 color = UIColor::White;
//                 break;
//             }
//         }

//         newMessage.UIText = m_logMessagesGroup->CreateWidget<UIColoredText>(message, color);

//         if (m_logDeque.size() + 1 > LOG_DEQUE_SIZE)
//         {
//             m_logMessagesGroup->RemoveWidget(m_logDeque.at(0).UIText);
//             m_logDeque.pop_front();
//         }

//         m_logDeque.emplace_back(newMessage);

//         m_logMessagesGroup->ScrollToBottom();
//     }

//     void LoggerPanel::clearButtonClicked()
//     {
//         m_logDeque.clear();
//         m_logMessagesGroup->RemoveAllWidgets();
//     }
// }
