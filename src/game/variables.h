#pragma once

#include <iostream>
#include <unistd.h>

namespace VARIABLES {
const int BLOCK_WIDTH = 40;
const int BLOCK_HEIGHT = 40;
const int DIMENSION = 15;
std::vector<std::vector<int>> matrix(VARIABLES::DIMENSION, std::vector<int>(VARIABLES::DIMENSION, 0));
}//namespace VARIABLES
