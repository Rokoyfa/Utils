#include "gui/Window.h"

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

        void Window::setIconPath(std::string& iconPath)
        {
            __iconPath__ = iconPath;
        }

        std::string Window::getTitle() const {
            return __title__;
        }

        std::string Window::getIcon() const
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

        void Window::draw() {
            for (Interface* child : __children__) {
                if (child) {
                    break;
                }
            }
        }


        void Window::addEventListener(const std::string& eventType, EventCallback callback) {
            __listeners__[eventType].push_back(callback);
        }

        void Window::handleEvent(r_utils::events::Event& event) {
            /*
            auto it = __listeners__.find(event.getType());
            if (it != __listeners__.end()) {
                for (const auto& callback : it->second) {
                    callback(event);
                }
            }*/
        }
    } // gui
} // r_utils