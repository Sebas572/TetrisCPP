#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include "./check.h"
#include "./draw.h"
#include "./variables.h"


namespace Player {
	int y[4] = {0, 0, 1, 1};
	int x[4] = {5, 6, 5, 6};

	void reset() {
		y[0] = 0;
		y[1] = 0;
		y[2] = 1;
		y[3] = 1;
		x[0] = 5;
		x[1] = 6;
		x[2] = 5;
		x[3] = 6;
	}

	bool validateCollicion(int left, int right, int down) {
		bool result = false;
	  for (int i = 0; i < 4; ++i) {
			result = (VARIABLES::matrix[x[i]-left+right][y[i]+down] == 1 || y[i]+down >= VARIABLES::DIMENSION);
			if(result) break;
		}
		return result;
	}

	void setBlocks() {
	  for (int i = 0; i < 4; ++i) {
			VARIABLES::matrix[x[i]][y[i]] = 1;
	    Check::line(VARIABLES::matrix, y[i]);
		}
	}

	void clear() {
	  for (int i = 0; i < 4; ++i) {
			VARIABLES::matrix[x[i]][y[i]] = 0;
		}
	}

	void setMove(int left, int right, int down) {
		if(!Check::isInsideBorder(x, y, left, right, down)) return;

		Player::clear();
	  if(validateCollicion(left, right, down)) {
	  	setBlocks();
	  	reset();
	  	return;
		}

	  for (int i = 0; i < 4; ++i) {
	  	x[i] += -left+right;
	  	y[i] += down;
	  	VARIABLES::matrix[x[i]][y[i]] = 2;
		}

		system("clear");
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				std::cout << VARIABLES::matrix[j][i] << ", ";
			}
			std::cout << std::endl;
		}

	  Draw::game();
	}

	void setMoveRight() {
		setMove(0, 1, 0);
	}
	void setMoveLeft() {
		setMove(1, 0, 0);
	}
	void setMoveDown() {
		setMove(0, 0, 1);
	}
	void setMoveDownT() { 
	  for (int i = 0; i < VARIABLES::DIMENSION+1; ++i) {
	    // if(i == y) continue;
	    // if(VARIABLES::matrix[x][i] == 1) break;
	    setMove(0, 0, 1);

	    usleep(20000);
	  }
	}

}//namespace Player