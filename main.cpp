#include <X11/Xlib.h>
#include <iostream>
#include <thread>
#include "src/events/events.h"
#include "src/game/start.h"
#include "src/game/draw.h"

int createWindow() {
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Error: Unable to open display.\n");
    return 1;
  }

  int screen = DefaultScreen(display);
  Window window = XCreateSimpleWindow(
      display, RootWindow(display, screen), 0, 0, 615, 615, 0,
      BlackPixel(display, screen), WhitePixel(display, screen));

  XSelectInput(display, window,
               ExposureMask | KeyPressMask | StructureNotifyMask);
  XMapWindow(display, window);

  Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, window, &wmDeleteMessage, 1);
  
  GC gc = XCreateGC(display, window, 0, NULL);

  Draw::window = window;
  Draw::display = display;
  Draw::gc = gc;
  
  XInitThreads();
  std::thread hilo1(Events::start, window, display, wmDeleteMessage, gc);
  std::thread hilo2(Game::start);

  hilo1.join();
  // hilo2.join();

  XFreeGC(display, gc);
  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}

int main(int argc, char const *argv[]) {
  createWindow();
  return 0;
}
