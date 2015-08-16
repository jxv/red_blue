#include "red_blue.h"

namespace red_blue {

Battle::Battle()
: hot(Player::A)
, cold(Player::B)
{}

bool Battle::Step() {
}

const BattleAction& Battle::get_battle_action() const {
  return battle_action;
}

}
