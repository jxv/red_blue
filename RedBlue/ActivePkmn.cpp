#include <cmath>
#include <cassert>
#include "RedBlue.hpp"

namespace RedBlue {

static int stage_multiplier(int stage) {
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
  
ActivePkmn::ActivePkmn(CorePkmn& cp)
: corepkmn(cp) 
, transform()
, volstatuses()
, stats()
, stages() {
  update_stats();
}

const CorePkmn& ActivePkmn::get_corepkmn() const { return corepkmn; }

Specie::Tag ActivePkmn::get_specie() const {
  if (transform) return *transform;
  return corepkmn.get_specie();
}

const VolStatuses& ActivePkmn::get_volstatuses() const { return volstatuses; }
const ActiveStats& ActivePkmn::get_stats() const { return stats; }
const ActiveStats& ActivePkmn::get_stages() const { return stages; }

void ActivePkmn::update_stats() {
  update_attack();
  update_defense();
  update_special();
  update_speed();
  update_accuracy();
}

void ActivePkmn::update_attack() { stats.attack = stage_multiplier(stages.attack) * corepkmn.get_stats().attack / 100; }
void ActivePkmn::update_defense() { stats.defense = stage_multiplier(stages.defense) * corepkmn.get_stats().defense / 100; }
void ActivePkmn::update_special() { stats.special = stage_multiplier(stages.special) * corepkmn.get_stats().special / 100; }
void ActivePkmn::update_speed() { stats.speed = stage_multiplier(stages.speed) * corepkmn.get_stats().speed / 100; }
void ActivePkmn::update_accuracy() { stats.accuracy = stage_multiplier(stages.accuracy); }
void ActivePkmn::update_evasion() { stats.evasion = stage_multiplier(stages.evasion); }

}
