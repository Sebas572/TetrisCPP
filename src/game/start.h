#pragma once

#include <iostream>
#include "./player.h"
#include "./draw.h"
#include "./variables.h"

namespace Game {

void start() {
  Player::reset();
  while(1) {
    Player::setMoveDown();
    Draw::game();
    sleep(1);
  }
}

} // namespace Draw
