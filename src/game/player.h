#pragma once

#include "./check.h"
#include "./draw.h"
#include "./variables.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <random>
#include <bits/stdc++.h>

namespace Player {
int y[4] = {0, 0, 1, 1};
int x[4] = {5, 6, 5, 6};

void clear() {
  for (int i = 0; i < 4; ++i) {
    VARIABLES::matrix[x[i]][y[i]] = 0;
  }
}

void assignValues(int *arr, std::initializer_list<int> v) {
  std::vector<int> values = v;
  for(int i = 0; i < 4; ++i) {
    arr[i] = values[i];
  }
}

void OBlock() {
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

void moveIfCloseToTheEdges(int x, int y, int newX, int newY) {
  int positiveX = (x-newX == -1)?1:0;
  int negativeX = (x-newX == 15)?(-1):0;
  int negativeY = (y+newY == 15)?(-1):0;
  
  if(positiveX == 0 && negativeX == 0 && negativeY == 0) return;

  for (int i = 0; i < 4; ++i) {
    Player::x[i]+= positiveX+negativeX;
    Player::y[i]+= negativeY;
  }
}

void rotate() {
  clear();
  int center = 3;


  for (int i = 0; i < 4; ++i) {
    int diffX = x[i] - x[center];
    int diffY = y[i] - y[center];
    
    int newX = diffX+diffY, newY = (diffX+(-diffY));
    moveIfCloseToTheEdges(x[i], y[i], newX, newY);
    y[i] += newY;
    x[i] -= newX;
  }
  for (int i = 0; i < 4; ++i) {
    VARIABLES::matrix[x[i]][y[i]] = 2;
  }
  Draw::game();
}

void reset() {
  int i = rand()%(7-0);
  if(i == 0) {OBlock();}
  else if(i == 1) {IBlock();}
  else if(i == 2) {TBlock();}
  else if(i == 3) {SBlock();}
  else if(i == 4) {ZBlock();}
  else if(i == 5) {JBlock();}
  else if(i == 6) {LBlock();}
}

bool validateCollicion(int left, int right, int down) {
  bool result = false;
  for (int i = 0; i < 4; ++i) {
    result = (VARIABLES::matrix[x[i] - left + right][y[i] + down] == 1 ||
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
  if (validateCollicion(left, right, down)) {
    setBlocks();
    reset();
    Draw::game();
    return false;
  }

  for (int i = 0; i < 4; ++i) {
    x[i] += -left + right;
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
