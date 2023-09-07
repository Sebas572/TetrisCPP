#include <iostream>
#include <X11/Xlib.h>
#include "src/events/keyboard.h"

int createWindow() {
  Display* display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Error: Unable to open display.\n");
    return 1;
  }

  int screen = DefaultScreen(display);
  Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, 640, 480, 0, BlackPixel(display, screen), WhitePixel(display, screen));

  XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);
  XMapWindow(display, window);

  Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, window, &wmDeleteMessage, 1);

  Events::start(window, display, wmDeleteMessage);

  // XEvent event;
  // while (1) {
	// 	XNextEvent(display, &event);
	// 	if (event.type == Expose) {
	// 	  // Handle expose event
	// 	}
		
	// 	if (event.type == ClientMessage) {
	// 	  if (
	// 	  	event.xclient.message_type == XInternAtom(display, "WM_PROTOCOLS", True) &&
	// 	  	event.xclient.data.l[0] == wmDeleteMessage
	// 	  ) {
	//       break;
	// 	  }
	// 	}
	// }

  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}

int main(int argc, char const *argv[]) {
	createWindow();
	return 0;
}