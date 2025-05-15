#ifdef __APPLE__
#include <Cocoa/Cocoa.h>
#include "gui/Window.h"
#include "exception/gui/WindowException.h"

namespace r_utils
{
	namespace gui
	{
		@interface RUtilsWindowDelegate : NSObject <NSWindowDelegate>
		{
			// We could implement delegate methods here later,
			// e.g. for closing the window.
		}
		@end

			@implementation RUtilsWindowDelegate
			// No specific delegate methods at the moment
			@end

			Window::Window(std::string id, const std::string& title, int width, int height, bool expandable)
			: __id__(id), __title__(title), __width__(width), __height__(height), __isExpandable__(expandable), __isVisible__(false), __nsWindow__(nullptr)
		{
			NSRect windowRect = NSMakeRect(0, 0, width, height);

			NSUInteger styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable;
			if (expandable) {
				styleMask |= NSWindowStyleMaskResizable;
			}

			__nsWindow__ = [[NSWindow alloc]initWithContentRect:windowRect
				styleMask : styleMask
				backing : NSBackingStoreBuffered
				defer : NO];

			if (!__nsWindow__) {
				throw exception::WindowException("Error creating the NSWindow!");
			}

			NSString* titleNSString = [[NSString alloc]initWithUTF8String:title.c_str()];
			[__nsWindow__ setTitle : titleNSString] ;
			[titleNSString release] ;

			RUtilsWindowDelegate* delegate = [[RUtilsWindowDelegate alloc]init];
			[__nsWindow__ setDelegate : delegate] ;
			[delegate release] ;
		}

		Window::~Window()
		{
			if (__nsWindow__) {
				[__nsWindow__ release] ;
				__nsWindow__ = nullptr;
			}
		}

		void Window::show()
		{
			if (__nsWindow__) {
				[__nsWindow__ makeKeyAndOrderFront : nil] ;
				__isVisible__ = true;
			}
		}

		void Window::hide()
		{
			if (__nsWindow__) {
				[__nsWindow__ orderOut : nil] ;
				__isVisible__ = false;
			}
		}

		void Window::close() const
		{
			if (__nsWindow__) {
				[__nsWindow__ close] ;
			}
		}

	private:
		void* __nsWindow__;
	}
}
#endif