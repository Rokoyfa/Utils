#ifdef __linux__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstring>
#include "gui/Window.h"
#include "exception/gui/WindowException.h"

namespace r_utils
{
	namespace gui
	{
		Window::Window(std::string id, const std::string& title, r_utils::events::EventDispatcher& dispatcher, int width, int height, bool expandable)
			: __id__(id), __title__(title), __dispatcher__(dispatcher), __width__(width), __height__(height), __isExpandable__(expandable), __isVisible__(true), __xid__(0)
		{
			Display* display = XOpenDisplay(nullptr);
			if (!display) {
				throw r_utilsexception::WindowException("Couldn't connect to X-Server!");
			}

			int screen = DefaultScreen(display);
			Window root = RootWindow(display, screen);

			__xid__ = XCreateSimpleWindow(display, root, 0, 0, width, height, 0, 0, WhitePixel(display, screen));
			if (!__xid__) {
				XCloseDisplay(display);
				throw r_utils::exception::WindowException("Error creating the X11-Window!");
			}

			XStoreName(display, __xid__, title.c_str());

			if(XStoreName(__display__, __xid__, title.c_str()) == 0) {
				throw r_utils::logger::warn("Error when setting the window title under X11.");
			}

			__display__ = display;
		}

		Window::~Window()
		{
			if (__display__ && __xid__) {
				XDestroyWindow(__display__, __xid_);
				XCloseDisplay(__display__);
				__display__ = nullptr;
				__xid__ = 0;
			}
			else if (__display__) {
				XCloseDisplay(__display__);
				__display__ = nullptr;
			}
		}

		void Window::show()
		{
			if (__display__ && __xid__) {
				XMapWindow(display_, __xid__);
				__isVisible__ = true;
			}
		}

		void Window::hide()
		{
			if (__display__ && __xid__) {
				XUnmapWindow(display_, __xid__);
				__isVisible__ = false;
			}
		}

		void Window::close()
		{
			if (__display__ && __xid__) {
				XDestroyWindow(__display__, __xid__);
				__xid__ = 0;
			}
		}
	private:
		Display* __display__ = nullptr;
	} // gui
} // r_utils
#endif