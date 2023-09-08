#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

namespace Check {
	bool Line(std::vector<std::vector<int>> &matrix, int y) {
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
}// namespace Check