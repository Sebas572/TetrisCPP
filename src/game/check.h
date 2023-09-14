#pragma once

#include "./variables.h"
#include <algorithm>
#include <iostream>
#include <vector>

namespace Check {

bool isLose() {
  bool result = false;
  for (int i = 0; i <= 14; ++i) {
    if (VARIABLES::matrix[i][0] == 1) {
      result = true;
      break;
    }
  }

  return result;
}

void moveLineDown() {
  while (true) {
    for (int y = 14; y >= 0; --y) {
      if (VARIABLES::matrix[0][y] != 3)
        continue;
      for (int i = 14; i >= 0; --i) {
        for (int j = y; j >= 0; --j) {
          VARIABLES::matrix[i][j] = VARIABLES::matrix[i][j - 1];
        }
        VARIABLES::SCORE += 1;
      }
    }
    sleep(2);
  }
}

bool line(int y) {
  bool allEqualToOne = true;

  VARIABLES::IS_LOSE = Check::isLose();

  for (int i = 0; i < VARIABLES::matrix.size(); ++i) {
    if (VARIABLES::matrix[i][y] != 1) {
      allEqualToOne = false;
      break;
    }
  }

  if (!allEqualToOne)
    return false;

  for (int i = 14; i >= 0; --i) {
    VARIABLES::matrix[i][y] = 3;
  }

  return true;
}

bool isInsideBorder(int x[], int y[], int left, int right, int down) {
  bool result = true;

  for (int i = 0; i < 4; ++i) {
    if (x[i] - left + right < 0 ||
        x[i] - left + right >= VARIABLES::DIMENSION ||
        y[i] + down >= VARIABLES::DIMENSION + 1) {
      result = false;
      break;
    }
  }

  return result;
}
} // namespace Check
