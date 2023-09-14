#pragma once

#include <iostream>
#include <vector>
#include <unistd.h>

namespace VARIABLES {

struct IAanimationFullLine {
  bool execute;
  std::vector<int> y;
};

const int BLOCK_WIDTH = 40;
const int BLOCK_HEIGHT = 40;
const int DIMENSION = 15;

int SCORE = 0;
bool IS_LOSE = false;
IAanimationFullLine ANIMATION_FULL_LINE = {false, std::vector<int>()};
std::vector<std::vector<int>> matrix(VARIABLES::DIMENSION,
                                     std::vector<int>(VARIABLES::DIMENSION, 0));
} // namespace VARIABLES
