#pragma once

#include "./check.h"
#include "./draw.h"
#include "./variables.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <random>
#include <cstdlib>

namespace Player {
int y[4] = {0, 0, 1, 1};
int x[4] = {5, 6, 5, 6};
bool isRotated = true;

void clear() {
  for (int i = 0; i < 4; ++i) {
    VARIABLES::matrix[x[i]][y[i]] = 0;
  }
}

void assignValues(int *arr, std::initializer_list<int> v) {
  std::vector<int> values = v;
  values.resize(4);
  std::copy(values.begin(), values.end(), arr);
}

void OBlock() {
  isRotated = false;
  assignValues(y,{0,0,1,1});
  assignValues(x,{5,6,5,6});
}
void IBlock() {
  assignValues(y,{0,0,0,0});
  assignValues(x,{4,6,7,5});
}
void TBlock() {
  assignValues(y,{0,1,1,1});
  assignValues(x,{5,4,6,5});
}
void SBlock() {
  assignValues(y,{0,0,1,1});
  assignValues(x,{6,7,5,6});
}
void ZBlock() {
  assignValues(y,{0,0,1,1});
  assignValues(x,{5,6,7,6});
}
void JBlock() {
  assignValues(y,{0,1,1,1});
  assignValues(x,{4,4,6,5});
}
void LBlock() {
  assignValues(y,{0,1,1,1});
  assignValues(x,{6,6,4,5});
}

void moveIfCloseToTheEdges(int x[4], int y[4], int index, int newX, int newY) {
  int positiveX = (x[index]-newX == -1)?1:0;
  int negativeX = (x[index]-newX == 15)?(-1):0;
  int negativeY = (y[index]+newY == 15-1)?(-1):0;
  
  if(positiveX == 0 && negativeX == 0 && negativeY == 0) return;

  for (int i = 0; i < 4; ++i) {
    x[i]+= positiveX+negativeX;
    y[i]+= negativeY;
  }
}


void rotate() {
  if(!isRotated) return;

  int XCopy[4], YCopy[4];
  std::copy(x, x + 4, XCopy);
  std::copy(y, y + 4, YCopy);

  bool isCollisionWithBlock = false, isMoveUp = false;
  for (int i = 0; i < 4; ++i) {
    int diffX = XCopy[i] - XCopy[3];
    int diffY = YCopy[i] - YCopy[3];
    
    int newX = diffX+diffY, newY = (diffX+(-diffY));
    moveIfCloseToTheEdges(XCopy, YCopy, i, newX, newY);
    YCopy[i] += newY;
    XCopy[i] -= newX;

    if(VARIABLES::matrix[XCopy[i]][YCopy[i]] == 1 || XCopy[i] == -1 || XCopy[i] == 15 ) {
      isCollisionWithBlock = true;
    }
  }

  if(isCollisionWithBlock) {
    isMoveUp = true;
    for (int i = 0; i < 4; ++i) {
      if(VARIABLES::matrix[XCopy[i]][YCopy[i]-1] == 1) {
        isMoveUp = false;
        break;
      }
    }
  }

  if(isCollisionWithBlock && !isMoveUp) return;

  clear();
  std::copy(XCopy, XCopy + 4, x);
  std::copy(YCopy, YCopy + 4, y);

  for (int i = 0; i < 4; ++i) {
    if(isMoveUp) y[i]--;
    VARIABLES::matrix[x[i]][y[i]] = 2;
  }
  Draw::game();
}

void reset() {
  srand(time(NULL));

  int i = rand()%7;
  isRotated = true;
  
  if(i == 0) {OBlock();}
  else if(i == 1) {IBlock();}
  else if(i == 2) {TBlock();}
  else if(i == 3) {SBlock();}
  else if(i == 4) {ZBlock();}
  else if(i == 5) {JBlock();}
  else if(i == 6) {LBlock();}
}

bool validateCollicion(int down) {
  bool result = false;
  for (int i = 0; i < 4; ++i) {
    result = (VARIABLES::matrix[x[i]][y[i] + down] == 1 ||
              y[i] + down >= VARIABLES::DIMENSION);
    if (result)
      break;
  }
  return result;
}

void setBlocks() {
  for (int i = 0; i < 4; ++i) {
    VARIABLES::matrix[x[i]][y[i]] = 1;
    Check::line(VARIABLES::matrix, y[i]);
  }
}


bool setMove(int left, int right, int down) {
  if (!Check::isInsideBorder(x, y, left, right, down))
    return true;

  Player::clear();
  if (validateCollicion(down)) {
    setBlocks();
    reset();
    Draw::game();
    return false;
  }

  bool move = true;

  for (int i = 0; i < 4; ++i) {
    if(VARIABLES::matrix[x[i]-left+right][y[i]] == 1) {
      move = false;
      break;
    }
  }

  for (int i = 0; i < 4; ++i) {
    if(move) x[i] += -left + right;
    y[i] += down;
    VARIABLES::matrix[x[i]][y[i]] = 2;
  }

  Draw::game();
  return true;
}

void setMoveRight() { setMove(0, 1, 0); }
void setMoveLeft() { setMove(1, 0, 0); }
void setMoveDown() { setMove(0, 0, 1); }
void setMoveDownT() {
  for (int i = 0; i < VARIABLES::DIMENSION + 1; ++i) {
    if (!setMove(0, 0, 1)) {
      break;
    }

    usleep(20000);
  }
}

} // namespace Player
