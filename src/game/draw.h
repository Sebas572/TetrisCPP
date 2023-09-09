#pragma once

#include <X11/Xlib.h>
#include <iostream>
#include "./variables.h"

namespace Draw {
	Window window;
	Display *display;
	GC gc;

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
	  setColor(RGB(53, 53, 53));
	  Draw::rectangle(0, 0, 615, 615);
	}

	void game() {
	  Draw::clear();

	  setColor(RGB(0, 255, 0));
	  for (int i = 0; i < VARIABLES::DIMENSION; i++) {
	    for (int j = 0; j < VARIABLES::DIMENSION; j++) {
	      if(VARIABLES::matrix[i][j] == 1) {
	        Draw::rectangle(i+i*40, j+j*40, VARIABLES::BLOCK_WIDTH, VARIABLES::BLOCK_HEIGHT);
	      }
	    }
	  }

	  XFlush(Draw::display);
	}

}