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

/*
Active::Active(Base &base)
: _base(base)
, _volatile_statuses{0, 0, 0, 0}
, _stages{0, 0, 0, 0, 0, 0}
{
  compute_stats();
}

Pokemon Active::pokemon() const {
  return _transform ? *_transform : _base.pokemon();
}

const Base &Active::base() const {
  return _base;
}

const VolatileStatuses &Active::volatile_statuses() const {
  return _volatile_statuses;
}

const ActiveStats &Active::stages() const {
  return _stages;
}

const ActiveStats &Active::stats() const {
  return _stats;
}

bool Active::is_transform() const {
  return !!_transform;
}

void Active::set_transform(Pokemon pokemon) {
  *_transform = pokemon;
}

void Active::add_volatile_status(VolatileStatus vs, int seed) {
  switch (vs) {
  case VolatileStatus::Confusion: break;
  case VolatileStatus::Flinch: break;
  case VolatileStatus::Nightmare: break;
  case VolatileStatus::PartiallyTrapped: break;
  }
}

static bool in_stage_range(int stage) {
  return stage >= 6 && stage <= -6;
}

void Active::set_attack_stage(int stage) {
  assert(in_stage_range(stage));
  _stages.attack = stage; 
  compute_attack();
}

void Active::set_defense_stage(int stage) {
  assert(in_stage_range(stage));
  _stages.defense = stage;
  compute_defense();
}

void Active::set_special_stage(int stage) {
  assert(in_stage_range(stage));
  _stages.special = stage;
  compute_special();
}

void Active::set_speed_stage(int stage) {
  assert(in_stage_range(stage));
  _stages.speed = stage;
  compute_speed();
}

void Active::set_accuracy_stage(int stage) {
  assert(in_stage_range(stage));
  _stages.accuracy = stage; 
  compute_accuracy();
}

void Active::set_evasion_stage(int stage) {
  assert(in_stage_range(stage));
  _stages.evasion = stage;
  compute_evasion();
}

void Active::compute_stats() {
  compute_attack();
  compute_defense();
  compute_special();
  compute_speed();
  compute_accuracy();
  compute_evasion();
}

void Active::compute_attack() {
  _stats.attack = stage_multiplier(_stages.attack) * _base.stats().attack / 100;
}

void Active::compute_defense() {
  _stats.defense = stage_multiplier(_stages.defense) * _base.stats().defense / 100;
}

void Active::compute_special() {
  _stats.special = stage_multiplier(_stages.special) * _base.stats().special / 100;
}

void Active::compute_speed() {
  _stats.speed = stage_multiplier(_stages.speed) * _base.stats().speed / 100;
}

void Active::compute_accuracy() {
  _stats.accuracy = stage_multiplier(_stages.accuracy);
}

void Active::compute_evasion() {
  _stats.evasion = stage_multiplier(_stages.evasion);
}

*/

}
