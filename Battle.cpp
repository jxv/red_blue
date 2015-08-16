#include "RedBlue.h"

namespace RedBlue {

Battle::Battle()
: hot(Player::A)
, cold(Player::B)
{}

bool Battle::Step() {
}

const BattleAction& Battle::GetBattleAction() const {
  return battleAction;
}

}
