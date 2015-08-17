#include <cmath>
#include <cassert>
#include "red_blue.h"

namespace red_blue {

Pokemon::Pokemon(CoreStats iv, Specie s, int lvl, MoveSet ms)
: specie(s)
, individual_values(iv)
, effort_values{0,0,0,0,0}
, level(lvl)
, experience(get_experience_by_level(specie, lvl))
, move_set(ms)
, non_vol_status(NonVolStatus::None) {
  update_stats();
  health_points = stats.health_points;
}

void Pokemon::evolve(Specie to) {
  assert(can_evolve_to(specie, level, to));
  specie = to;
}

void Pokemon::restore_health_points() { health_points = stats.health_points; }

void Pokemon::restore_health_points(int hp) {
  assert(hp > 0);
  assert(health_points < stats.health_points);
  health_points += hp;
  if (health_points > stats.health_points) health_points = stats.health_points;
}

void Pokemon::damage_health_points(int hp) {
  assert(hp > 0);
  assert(health_points > 0);
  health_points -= hp;
  if (health_points < 0) health_points = 0;
  if (health_points == 0) non_vol_status = NonVolStatus::None;
}

void Pokemon::add_experience(int exp) {
  const int old_exp = experience;
  const int max_exp = get_experience_by_level(specie, 100);
  assert(experience <= max_exp);
  if (experience == max_exp) return;
  experience += exp;
  if (experience > max_exp) experience = max_exp;
  sync_level();
}

bool are_valid_effort_values(const CoreStats &exp) {
  return
    (exp.health_points & 0xffff) == exp.health_points &&
    (exp.attack & 0xffff) == exp.attack &&
    (exp.defense & 0xffff) == exp.defense &&
    (exp.speed & 0xffff) == exp.speed &&
    (exp.special & 0xffff) == exp.special;
}

void Pokemon::add_effort_values(CoreStats ev) {
  assert(are_valid_effort_values(ev));
  assert(are_valid_effort_values(effort_values));
  const auto  old_ev = effort_values;
  // TODO
}

void Pokemon::burn() {
  assert(is_alive());
  assert(non_vol_status == NonVolStatus::None);
  non_vol_status = NonVolStatus::Burn;
}

void Pokemon::freeze() {
  assert(is_alive());
  assert(non_vol_status == NonVolStatus::None);
  non_vol_status = NonVolStatus::Freeze;
}

void Pokemon::paralyze() {
  assert(is_alive());
  assert(non_vol_status == NonVolStatus::None);
  non_vol_status = NonVolStatus::Paralysis;
}

void Pokemon::poison() {
  assert(is_alive());
  assert(non_vol_status == NonVolStatus::None || non_vol_status == NonVolStatus::Toxic);
  non_vol_status = NonVolStatus::Poison;
}

void Pokemon::sleep() {
  assert(is_alive());
  assert(non_vol_status == NonVolStatus::None);
  non_vol_status = NonVolStatus::Sleep;
}

void Pokemon::intoxicate() {
  assert(is_alive());
  assert(non_vol_status == NonVolStatus::None);
  non_vol_status = NonVolStatus::Toxic;
}

void Pokemon::restore_non_vol_status() { non_vol_status = NonVolStatus::None; }

Specie Pokemon::get_specie() const { return specie; }

int Pokemon::get_health_points() const { return health_points; }

int Pokemon::get_experience() const { return experience; }

NonVolStatus Pokemon::get_non_vol_status() const { return non_vol_status; }

int Pokemon::get_level() const { return level; }

const CoreStats& Pokemon::get_stats() const { return stats; }

void Pokemon::sync_level() {
  assert(level >= 1 && level <= 100);
  auto old_level = level;
  while (level < 100 && get_experience_by_level(specie, level + 1) < experience) ++level;
  if (old_level != level) update_stats();
}

void Pokemon::update_stats() {
  assert(level >= 1 && level <= 100);
  auto compute = [&](int iv, int ev, int base) -> int {
    return ((iv + base + (std::sqrt(ev) / 8) + 50) * level) / 50;
  };
  auto base = get_base_stats(specie);
  stats.health_points = compute(individual_values.health_points, effort_values.health_points, base.health_points) + 10;
  stats.attack = compute(individual_values.attack, effort_values.attack, base.attack) + 5;
  stats.defense = compute(individual_values.defense, effort_values.defense, base.defense) + 5;
  stats.special = compute(individual_values.special, effort_values.special, base.special) + 5;
  stats.speed = compute(individual_values.speed, effort_values.speed, base.speed) + 5;
}

bool Pokemon::is_alive() const {
  assert(health_points >= 0 && health_points <= stats.health_points);
  return health_points > 0;
}

std::ostream& operator<<(std::ostream& os, const Pokemon& p) {
  os << "NAME" << std::endl;
  os << "  specie: " << get_name(p.specie) << std::endl;
  os << "  hp: " << p.health_points << std::endl;
  os << "  exp: " << p.experience << std::endl;
  os << "  level: " << p.level << std::endl;
  os << "  non_vol_status: " << p.non_vol_status << std::endl;
  os << "  moves:" << std::endl;
  for (auto i = 0; i < p.move_set.get_size(); ++i) {
    auto move = p.move_set.get_move(i);
    auto pp = p.move_set.get_power_points(i);
    os << "  [" << i << "] " << move << "\tcur=" << pp.get_current() << "\tmax=" << pp.get_maximum() << "\tstage=" << pp.get_stage() << std::endl;
  }
  os << "  iv:   \thp=" << p.individual_values.health_points << "\tatk=" << p.individual_values.attack << "\tdef=" << p.individual_values.defense << "\tspc=" << p.individual_values.special << "\tspd=" << p.individual_values.speed << std::endl;
  os << "  ev:   \thp=" << p.effort_values.health_points << "\tatk=" << p.effort_values.attack << "\tdef=" << p.effort_values.defense << "\tspc=" << p.effort_values.special << "\tspd=" << p.effort_values.speed << std::endl;
  os << "  stats:\thp=" << p.stats.health_points << "\tatk=" << p.stats.attack << "\tdef=" << p.stats.defense << "\tspc=" << p.stats.special << "\tspd=" << p.stats.speed << std::endl;
  return os;
}

}
