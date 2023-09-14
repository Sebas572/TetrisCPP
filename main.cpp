#include <X11/Xlib.h>
#include <iostream>
#include <thread>
#include <X11/Xft/Xft.h>
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
      display, RootWindow(display, screen), 0, 0, 800, 615, 0,
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
  Draw::screen = screen;
  Draw::font_title = XftFontOpenName(display, screen, "Arial:bold:size=80");
  Draw::font = XftFontOpenName(display, screen, "Arial:size=20");
  Draw::draw = XftDrawCreate(Draw::display, Draw::window, DefaultVisual(Draw::display, Draw::screen), DefaultColormap(Draw::display, Draw::screen));

  XftColorAllocName(display, DefaultVisual(display, screen), DefaultColormap(display, screen), "white", &Draw::color);

  XInitThreads();
  std::thread hilo1(Events::start, window, display, wmDeleteMessage, gc);
  std::thread hilo2(Game::start);
  std::thread hilo3(Check::moveLineDown);

  hilo1.join();
  // hilo2.join();

  XftColorFree(display, DefaultVisual(display, screen), DefaultColormap(display, screen), &Draw::color);
  XftFontClose(display, Draw::font_title);
  XFreeGC(display, gc);
  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}

int main(int argc, char const *argv[]) {
  createWindow();
  return 0;
}
