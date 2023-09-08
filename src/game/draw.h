#pragma once

#include <X11/Xlib.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "./check.h"

namespace Draw {
Window window;
Display *display;
GC gc;

const int BLOCK_WIDTH = 40;
const int BLOCK_HEIGHT = 40;
const int DIMENSION = 15;

int y, x = 7;

std::vector<std::vector<int>> matrix(DIMENSION, std::vector<int>(DIMENSION, 0));

unsigned long RGB(int r, int g, int b) { return b + (g << 8) + (r << 16); }

void setColor(long RGB) {
  XSetForeground(Draw::display, Draw::gc, RGB);
  XSetBackground(Draw::display, Draw::gc, RGB);
}

void rectangle(int x, int y, int width, int height) {
  XFillRectangle(Draw::display, Draw::window, Draw::gc, x, y, width, height);
}

void viewFall() {
  setColor(RGB(248, 248, 248));
  XFillRectangle(Draw::display, Draw::window, Draw::gc, x+x*BLOCK_WIDTH, y+(y+1)*BLOCK_WIDTH, BLOCK_WIDTH, BLOCK_WIDTH*DIMENSION);
}

void clear() {
  XClearWindow(Draw::display, Draw::window);
  setColor(RGB(53, 53, 53));
  Draw::rectangle(0, 0, 615, 615);
}

void game() {
  matrix[x][y] = 1;
  
  Draw::clear();
  Draw::viewFall();

  setColor(RGB(0, 255, 0));
  for (int i = 0; i < DIMENSION; i++) {
    for (int j = 0; j < DIMENSION; j++) {
      if(matrix[i][j] == 1) {
        Draw::rectangle(i+i*40, j+j*40, BLOCK_WIDTH, BLOCK_HEIGHT);
      }
    }
  }
  XFlush(Draw::display);

  std::cout << "Es: " << x << ", "<< y << std::endl;
}

void setMove(int left, int right, int down) {
  if(matrix[x-left+right][y+down] == 1 || y+down >= DIMENSION) {
    matrix[x][y] = 1;
    Check::Line(matrix, y);
    x = 7;
    y = 0;
    return;
  }

  matrix[x][y] = 0;
  x += -left+right;
  y += down;
}

void setMoveRight() { 
  if(x+1<=DIMENSION-1) {
    setMove(0, 1, 0);
    Draw::game();
  }
}
void setMoveLeft() { 
  if(x-1>=0){
    setMove(1, 0, 0);
    Draw::game();
  }
}
void setMoveDown() { 
  if(y+1<=DIMENSION){
    setMove(0, 0, 1);
    Draw::game();
  }
}
void setMoveDownT() { 
  for (int i = 0; i < DIMENSION+1; ++i) {
    if(i == y) continue;
    if(matrix[x][i] == 1) break;
    setMove(0, 0, 1);
    Draw::game();

    usleep(20000);
  }
}

void start() {
  while(1) {
    setMoveDown();
    Draw::game();
    sleep(1);
  }
}

} // namespace Draw
