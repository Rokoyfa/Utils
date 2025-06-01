#include "gui/Window.h"
#include "logger/LoggerMakro.h"

namespace r_utils {
    namespace gui {
        void Window::setTitle(const std::string& title) {
            __title__ = title;
        }

        void Window::setSize(int width, int height) {
            __width__ = width;
            __height__ = height;
        }

        void Window::setVisible(bool visible) {
            __isVisible__ = visible;
        }

        void Window::setIconPath(const std::string& iconPath)
        {
            __iconPath__ = iconPath;
        }

        std::string Window::getTitle() const {
            return __title__;
        }

        std::string Window::getIconPath() const
        {
            return __iconPath__;
        }

        std::vector<int> Window::getSize() const {
            return { __width__, __height__ };
        }

        std::string Window::getID() const
        {
            return __id__;
        }

        void Window::addChild(Interface* child) {
            __children__.push_back(child);
        }

        void Window::onEvent(r_utils::events::Event& event)
        {
            switch (event.getType())
            {
            case r_utils::events::EventType::WINDOW_RESIZE:
            {
                r_utils::gui::events::WindowResizeEvent& resizeEvent = static_cast<r_utils::gui::events::WindowResizeEvent&>(event);
                event.setHandled(true);
                break;
            }
            default:
                break;
            }
        }

        void Window::draw() {
            for (Interface* child : __children__) {
                if (child) {
                    break;
                }
            }
        }
    } // gui
} // r_utils