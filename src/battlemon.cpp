#include <cmath>
#include <cassert>
#include "red_blue.h"

namespace red_blue {

static int stage_multiplier(ActiveStage stage) {
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
, vol_statuses()
, stats()
, stages() {
  update_stats(p);
}

const VolStatuses& Battlemon::get_vol_statuses() const {
  return vol_statuses;
}

const ActiveStats& Battlemon::get_stats() const {
  return stats;
}

const ActiveStages& Battlemon::get_stages() const {
  return stages;
}

Specie Battlemon::get_specie(const Pokemon &p) const {
  return transform ? *transform : p.get_specie();
}

void Battlemon::update_attack(const Pokemon& p) {
  stats.attack = stage_multiplier(stages.attack) * p.get_stats().attack / 100;
}

void Battlemon::update_defense(const Pokemon& p) {
  stats.defense = stage_multiplier(stages.defense) * p.get_stats().defense / 100;
}

void Battlemon::update_special(const Pokemon& p) {
  stats.special = stage_multiplier(stages.special) * p.get_stats().special / 100;
}

void Battlemon::update_speed(const Pokemon& p) {
  stats.speed = stage_multiplier(stages.speed) * p.get_stats().speed / 100;
}

void Battlemon::update_accuracy(const Pokemon& p) {
  stats.accuracy = stage_multiplier(stages.accuracy);
}

void Battlemon::update_evasion(const Pokemon& p) {
  stats.evasion = stage_multiplier(stages.evasion);
}

void Battlemon::update_stats(const Pokemon& p) {
  update_attack(p);
  update_defense(p);
  update_special(p);
  update_speed(p);
  update_accuracy(p);
  update_evasion(p);
}

}
