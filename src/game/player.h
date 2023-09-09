#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include "./check.h"
#include "./draw.h"
#include "./variables.h"

namespace Player {
	std::vector<int> piece(std::vector<int>(4, 0));
	int y, x = 7;

	void setMove(int left, int right, int down) {
		std::cout << "Es: " << x << "," << y << std::endl;
	  if(VARIABLES::matrix[x-left+right][y+down] == 1 || y+down >= VARIABLES::DIMENSION) {
	    VARIABLES::matrix[x][y] = 1;
	    Check::Line(VARIABLES::matrix, y);
	    x = 7;
	    y = 0;
	    return;
	  }

	  VARIABLES::matrix[x][y] = 0;
	  x += -left+right;
	  y += down;
	  VARIABLES::matrix[x][y] = 1;
	}

	void setMoveRight() { 
	  if(x+1<=VARIABLES::DIMENSION-1) {
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
	  if(y+1<=VARIABLES::DIMENSION){
	    setMove(0, 0, 1);
	    Draw::game();
	  }
	}
	void setMoveDownT() { 
	  for (int i = 0; i < VARIABLES::DIMENSION+1; ++i) {
	    if(i == y) continue;
	    if(VARIABLES::matrix[x][i] == 1) break;
	    setMove(0, 0, 1);
	    Draw::game();

	    usleep(20000);
	  }
	}

}//namespace Player