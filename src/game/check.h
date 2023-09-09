#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "./variables.h"

namespace Check {
	bool line(std::vector<std::vector<int>> &matrix, int y) {
		bool allEqualToOne = true;

		for (int i = 0; i < matrix.size(); ++i) {
			if(matrix[i][y] != 1) {
				allEqualToOne = false;
				break;
			}
		}

		if (!allEqualToOne) return false;

		for (int i = 14; i >= 0; --i) {
			for (int j = y; j >= 0; --j) {
				std::cout << i << ", " << j << std::endl;
				matrix[i][j] = matrix[i][j-1];
			}
		}

		return true;
	}

	bool isInsideBorder(int x[], int y[], int left, int right, int down) {
		bool result = true;

		for (int i = 0; i < 4; ++i) {
			if(
				x[i]-left+right <= 0 ||
				x[i]-left+right >= VARIABLES::DIMENSION-1 ||
				y[i]+down >= VARIABLES::DIMENSION+1
			) {
				result = false;
				break;
			}
		}

		return result;
	}
}// namespace Check