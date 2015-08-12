#include <cmath>
#include <cassert>
#include "RedBlue.hpp"

namespace RedBlue {

static int StageMultiplier(int stage) {
  switch (stage) {
  case -6: return 25;
  case -5: return 28;
  case -4: return 33;
  case -3: return 40;
  case -2: return 50;
  case -1: return 66;
  case 0: return 100;
  case 1: return 150;
  case 2: return 200;
  case 3: return 250;
  case 4: return 300;
  case 5: return 350;
  case 6: return 400;
  default: assert(false);
  }
}

void ActivePkmn::CalcAttack() {
  mStats.attack = StageMultiplier(mStages.attack) * mCorePkmn.GetStats().attack / 100;
}

void ActivePkmn::CalcDefense() {
  mStats.defense = StageMultiplier(mStages.defense) * mCorePkmn.GetStats().defense / 100;
}

void ActivePkmn::CalcSpecial() {
  mStats.special = StageMultiplier(mStages.special) * mCorePkmn.GetStats().special / 100;
}

void ActivePkmn::CalcSpeed() {
  mStats.speed = StageMultiplier(mStages.speed) * mCorePkmn.GetStats().speed / 100;
}

void ActivePkmn::CalcAccuracy() {
  mStats.accuracy = StageMultiplier(mStages.accuracy);
}

void ActivePkmn::CalcEvasion() {
  mStats.evasion = StageMultiplier(mStages.evasion);
}

}
