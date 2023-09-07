#pragma once

#include <iostream>
#include <X11/Xlib.h>

namespace Events {
  XEvent event;
  Window window;
  Display* display;
  Atom wmDeleteMessage;

	void isClose() {
	  if (
	  	Events::event.xclient.message_type == XInternAtom(Events::display, "WM_PROTOCOLS", True) &&
	  	Events::event.xclient.data.l[0] == Events::wmDeleteMessage
	  ) {
			XDestroyWindow(Events::display, Events::window);
	  	XCloseDisplay(Events::display);
	  }
	}

	void isKeyboard() {
		std::cout << KeyPress << std::endl;
	}

	void start(Window window, Display* display, Atom wmDeleteMessage) {
		Events::window = window;
		Events::display = display;
		Events::wmDeleteMessage = wmDeleteMessage;

	  while (1) {
			XNextEvent(Events::display, &Events::event);
			std::cout << ClientMessage << std::endl;

			if (Events::event.type == Expose) {
			  // Handle expose event
			}else if (event.type == KeyPress) {
				Events::isKeyboard();
			}else if (Events::event.type == ClientMessage) {
	  		std::cout << "close" << std::endl;
				Events::isClose();
			}		

		}

	}

}

