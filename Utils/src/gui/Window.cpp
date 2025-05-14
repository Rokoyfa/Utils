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

        std::string Window::getTitle() const {
            return __title__;
        }

        std::vector<int> Window::getSize() const {
            return { __width__, __height__ };
        }

        void Window::addChild(Interface* child) {
            __children__.push_back(child);
        }

        void Window::handleEvent(r_utils::events::Event& event) {
        
        }

        void Window::draw() {
            for (Interface* child : __children__) {
                if (child) {
                    break;
                }
            }
        }

    }
}