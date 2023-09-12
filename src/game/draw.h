#pragma once

#include <X11/Xlib.h>
#include <iostream>
#include "./variables.h"

namespace Draw {
	Window window;
	Display *display;
	GC gc;
	bool isLost = true;

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

	  if(Draw::isLost) {
	  	const char* message = "Perdiste";
	  	XDrawString(Draw::display, Draw::window, Draw::gc, 50, 100, message, strlen(message));

	  	return;
	  }

	  Draw::clear();
	  for (int i = 0; i < VARIABLES::DIMENSION; i++) {
	    for (int j = 0; j < VARIABLES::DIMENSION; j++) {
	      if(VARIABLES::matrix[i][j] == 1 || VARIABLES::matrix[i][j] == 2) {
	  			if (VARIABLES::matrix[i][j] == 1) setColor(RGB(0, 255, 0));
	  			else setColor(RGB(0, 0, 255));
	        Draw::rectangle(i+i*40, j+j*40, VARIABLES::BLOCK_WIDTH, VARIABLES::BLOCK_HEIGHT);
	      }
	    }
	  }

	  XFlush(Draw::display);
	}

}