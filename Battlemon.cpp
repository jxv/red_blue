#include <cmath>
#include <cassert>
#include "RedBlue.h"

namespace RedBlue {

static int StageMultiplier(ActiveStage stage) {
  switch (stage) {
  case ActiveStage::MinusSix: return 25;
  case ActiveStage::MinusFive: return 28;
  case ActiveStage::MinusFour: return 33;
  case ActiveStage::MinusThree: return 40;
  case ActiveStage::MinusTwo: return 50;
  case ActiveStage::MinusOne: return 66;
  case ActiveStage::Zero: return 100;
  case ActiveStage::PlusOne: return 150;
  case ActiveStage::PlusTwo: return 200;
  case ActiveStage::PlusThree: return 250;
  case ActiveStage::PlusFour: return 300;
  case ActiveStage::PlusFive: return 350;
  case ActiveStage::PlusSix: return 400;
  default: assert(false);
  }
}
  
Battlemon::Battlemon(const Pokemon& p)
: transform()
, volStatuses()
, stats()
, stages()
{ UpdateStats(p); }

const VolStatuses& Battlemon::GetVolStatuses() const { return volStatuses; }
const ActiveStats& Battlemon::GetStats() const { return stats; }
const ActiveStages& Battlemon::GetStages() const { return stages; }

Specie Battlemon::GetSpecie(const Pokemon &p) const {
  if (transform) return *transform;
  return p.GetSpecie();
}

void Battlemon::UpdateAttack(const Pokemon& p) { stats.attack = StageMultiplier(stages.attack) * p.GetStats().attack / 100; }
void Battlemon::UpdateDefense(const Pokemon& p) { stats.defense = StageMultiplier(stages.defense) * p.GetStats().defense / 100; }
void Battlemon::UpdateSpecial(const Pokemon& p) { stats.special = StageMultiplier(stages.special) * p.GetStats().special / 100; }
void Battlemon::UpdateSpeed(const Pokemon& p) { stats.speed = StageMultiplier(stages.speed) * p.GetStats().speed / 100; }
void Battlemon::UpdateAccuracy(const Pokemon& p) { stats.accuracy = StageMultiplier(stages.accuracy); }
void Battlemon::UpdateEvasion(const Pokemon& p) { stats.evasion = StageMultiplier(stages.evasion); }

void Battlemon::UpdateStats(const Pokemon& p) {
  UpdateAttack(p);
  UpdateDefense(p);
  UpdateSpecial(p);
  UpdateSpeed(p);
  UpdateAccuracy(p);
  UpdateEvasion(p);
}

}
