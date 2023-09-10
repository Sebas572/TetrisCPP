#pragma once

#include <X11/Xlib.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "../game/player.h"

namespace Events {
XEvent event;
Window window;
Display *display;
Atom wmDeleteMessage;
Bool isRun = true;

void isClose() {
  Bool isMessageType = Events::event.xclient.message_type ==
                       XInternAtom(Events::display, "WM_PROTOCOLS", True);
  Bool isWmDeleteMessage =
      Events::event.xclient.data.l[0] == Events::wmDeleteMessage;

  if (isMessageType && isWmDeleteMessage) {
    Events::isRun = false;
  }
}

void isKeyboard() {
	KeySym keySym = XLookupKeysym(&Events::event.xkey, 0);
	std::string key = XKeysymToString(keySym);

	if(key == "a") { Player::setMoveLeft(); }
	else if(key == "d") { Player::setMoveRight(); }
	else if(key == "s") { Player::setMoveDown(); }
  else if(key == "v") { Player::rotate(); }
	else if(key == "space") {Player::setMoveDownT(); }
}

void start(Window window, Display *display, Atom wmDeleteMessage, GC gc) {
  Events::window = window;
  Events::display = display;
  Events::wmDeleteMessage = wmDeleteMessage;

  while (Events::isRun) {
    XNextEvent(Events::display, &Events::event);

    if (Events::event.type == Expose) {
    	// Handle expose event
    }else if (Events::event.type == Expose && Events::event.xexpose.count == 0) {
      // Handle expose event
    }else if (event.type == KeyPress) {
      Events::isKeyboard();
    }else if (Events::event.type == ClientMessage) {
      std::cout << "close" << std::endl;
      Events::isClose();
    }

    sleep(1/60);
  }

}

} // namespace Events
