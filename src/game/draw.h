#pragma once

#include "./variables.h"
#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>
#include <iostream>
#include <iterator>

namespace Draw {
int screen;
Window window;
Display *display;
GC gc;
XftColor color;
XftFont* font_title, *font;
XftDraw* draw;
bool isLost = false;

unsigned long RGB(int r, int g, int b) { return b + (g << 8) + (r << 16); }

void setColor(long RGB) {
  XSetForeground(Draw::display, Draw::gc, RGB);
  XSetBackground(Draw::display, Draw::gc, RGB);
}

void rectangle(int x, int y, int width, int height) {
  XFillRectangle(Draw::display, Draw::window, Draw::gc, x, y, width, height);
}

void clear() {
  XClearWindow(Draw::display, Draw::window);

  setColor(RGB(30, 30, 30));
  Draw::rectangle(0, 0, 800, 615);
  setColor(RGB(250, 85, 92));
  Draw::rectangle(615, 0, 5, 615);

  setColor(RGB(0, 0, 0));
  for (int i = 0; i < 15; ++i) {
    Draw::rectangle(i + i * 40, 0, 1, 615);
    Draw::rectangle(0, i + i * 40, 615, 1);
  }
}

void game() {
  if (VARIABLES::IS_LOSE) {
    XClearWindow(Draw::display, Draw::window);
    setColor(RGB(0, 0, 0));
    Draw::rectangle(0, 0, 800, 615);
    
    XftDrawStringUtf8(draw, &Draw::color, Draw::font_title, 150, 220, (XftChar8*)"You lost!", 9);
    return;
  }

  Draw::clear();

  const char *message = ("Score: " + std::to_string(VARIABLES::SCORE)).c_str();
	XftDrawStringUtf8(draw, &Draw::color, Draw::font, 625, 40, (XftChar8*)message, strlen(message));

  for (int i = 0; i < VARIABLES::DIMENSION; i++) {
    for (int j = 0; j < VARIABLES::DIMENSION; j++) {
      if (VARIABLES::matrix[i][j] == 1 || VARIABLES::matrix[i][j] == 2 ||
          VARIABLES::matrix[i][j] == 3) {
        if (VARIABLES::matrix[i][j] == 1)
          setColor(RGB(0, 255, 0));
        else if (VARIABLES::matrix[i][j] == 2)
          setColor(RGB(0, 0, 255));
        else
          setColor(RGB(255, 0, 0));
        	Draw::rectangle(i + i * 40, j + j * 40, VARIABLES::BLOCK_WIDTH, VARIABLES::BLOCK_HEIGHT);
      }
    }
  }

  XFlush(Draw::display);
}

} // namespace Draw
