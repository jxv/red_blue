#include <cmath>
#include <cassert>
#include "RedBlue.hpp"

namespace RedBlue {

CorePkmn::CorePkmn(CoreStats iv_, Specie::Tag specie_, int level_, MoveSet moveset_)
: specie(specie_)
, iv(iv_)
, ev{0,0,0,0,0}
, level(level_)
, exp(calc_specie_exp(specie_, level_))
, moves(moveset_.moves)
, move_count(moveset_.move_count)
, pps(moveset_.pps)
, nonvolstatus(NonVolStatus::none) {
  update_stats();
  hp = stats.hp;
}

void CorePkmn::evolve(Specie::Tag to_specie) {
  assert(can_specie_evolve_to(specie, level, to_specie));
  specie = to_specie;
}

void CorePkmn::restore_hp() { hp = stats.hp; }

void CorePkmn::restore_hp(int hp_) {
  assert(hp_ > 0);
  assert(hp < stats.hp);
  hp += hp_;
  if (hp > stats.hp) hp = stats.hp;
}

void CorePkmn::damage_hp(int hp_) {
  assert(hp_ > 0);
  assert(hp > 0);
  hp -= hp_;
  if (hp < 0) hp = 0;
  if (hp == 0) nonvolstatus = NonVolStatus::none;
}

void CorePkmn::add_exp(int exp_) {
  const int old_exp = exp;
  const int max_exp = calc_specie_exp(specie, 100);
  assert(exp <= max_exp);
  if (exp == max_exp) return;
  exp += exp_;
  if (exp > max_exp) exp = max_exp;
  update_level();
}

bool validate_ev(const CoreStats &e) {
  return
    (e.hp & 0xffff) == e.hp &&
    (e.attack & 0xffff) == e.attack &&
    (e.defense & 0xffff) == e.defense &&
    (e.speed & 0xffff) == e.speed &&
    (e.special & 0xffff) == e.special;
}

void CorePkmn::add_ev(CoreStats ev_) {
  assert(validate_ev(ev_));
  assert(validate_ev(ev));
  const auto  old_ev = ev;
  // ev = ev + ev;
  // TODO
}

void CorePkmn::burn() {
  assert(is_alive());
  assert(nonvolstatus == NonVolStatus::none);
  nonvolstatus = NonVolStatus::burn;
}

void CorePkmn::freeze() {
  assert(is_alive());
  assert(nonvolstatus == NonVolStatus::none);
  nonvolstatus = NonVolStatus::freeze;
}

void CorePkmn::paralyze() {
  assert(is_alive());
  assert(nonvolstatus == NonVolStatus::none);
  nonvolstatus = NonVolStatus::paralysis;
}

void CorePkmn::poison() {
  assert(is_alive());
  assert(nonvolstatus == NonVolStatus::none || nonvolstatus == NonVolStatus::toxic);
  nonvolstatus = NonVolStatus::poison;
}

void CorePkmn::sleep() {
  assert(is_alive());
  assert(nonvolstatus == NonVolStatus::none);
  nonvolstatus = NonVolStatus::sleep;
}

void CorePkmn::intoxicate() {
  assert(is_alive());
  assert(nonvolstatus == NonVolStatus::none);
  nonvolstatus = NonVolStatus::toxic;
}

void CorePkmn::restore_nonvolstatus() { nonvolstatus = NonVolStatus::none; }

void CorePkmn::swap_move(int idx0, int idx1) {
  assert(idx0 >= 0 && idx0 < move_count);
  assert(idx1 >= 0 && idx1 < move_count);
  std::swap(moves[idx0], moves[idx1]);
}

void CorePkmn::learn_move(Move::Tag m, int idx) {
  assert(idx >= 0 && idx < move_count);
  assert(/* can_learn_move(specie, m) */ true);
  assert(/* !has_move(m) */ true);
  moves[idx] = m;
  /// TODO: Reset PP 
  pps[idx] = { .cur = 15, .max = 15, .stage = 0 };
}

void CorePkmn::use_pp(int idx) {
  assert(idx >= 0 && idx < move_count);
  assert(pps[idx].cur > 0);
  --pps[idx].cur;
}

void CorePkmn::restore_pp() {
  for (auto& pp : pps) {
    pp.cur = pp.max;
  }
}

void CorePkmn::restore_pp(int idx) {
  assert(idx >= 0 && idx < move_count);
  auto& pp = pps[idx];
  pp.cur = pp.max;
}

void CorePkmn::restore_pp(int idx, int addition) {
  assert(idx >= 0 && idx < move_count);
  auto& pp = pps[idx];
  pp.cur += addition;
  pp.cur %= pp.max + 1;
}

void CorePkmn::increment_pp_stage(int idx) {
  assert(idx >= 0 && idx < move_count);
  auto& pp = pps[idx];
  assert(pp.stage >= 0 && pp.stage < 6);
  ++pp.stage;
}

Specie::Tag CorePkmn::get_specie() const { return specie; }

int CorePkmn::get_hp() const { return hp; }

int CorePkmn::get_exp() const { return exp; }

NonVolStatus::Tag CorePkmn::get_nonvolstatus() const { return nonvolstatus; }

int CorePkmn::get_move_count() const { return move_count; }

Move::Tag CorePkmn::get_move(int idx) const {
  assert(idx >= 0 && idx < move_count);
  return moves[idx];
}

const PP& CorePkmn::get_pp(int idx) const {

  assert(idx >= 0 && idx < move_count);
  return pps[idx];
}

int CorePkmn::get_level() const { return level; }

CoreStats CorePkmn::get_stats() const { return stats; }

void CorePkmn::update_level() {
  assert(level >= 1 && level <= 100);
  while (level < 100 && calc_specie_exp(specie, level + 1) < exp) ++level;
}

void CorePkmn::update_stats() {
  assert(level >= 1 && level <= 100);
  auto compute = [&](int iv, int ev, int base) -> int {
    return ((iv + base + (std::sqrt(ev) / 8) + 50) * level) / 50;
  };
  auto base = get_specie_base_stats(specie);
  stats.hp = compute(iv.hp, ev.hp, base.hp) + 10;
  stats.attack = compute(iv.attack, ev.attack, base.attack) + 5;
  stats.defense = compute(iv.defense, ev.defense, base.defense) + 5;
  stats.special = compute(iv.special, ev.special, base.special) + 5;
  stats.speed = compute(iv.speed, ev.speed, base.speed) + 5;
}

bool CorePkmn::is_alive() const {
  assert(hp >= 0 && hp <= stats.hp);
  return hp > 0;
}

std::ostream& operator<<(std::ostream& os, const CorePkmn& cp) {
  os << "NAME" << std::endl;
  os << "  specie: " << get_specie_name(cp.specie) << std::endl;
  os << "  hp: " << cp.hp << std::endl;
  os << "  exp: " << cp.exp << std::endl;
  os << "  level: " << cp.level << std::endl;
  os << "  nonvolstatus: " << cp.nonvolstatus << std::endl;
  os << "  moves:" << std::endl;
  for (auto i = 0; i < cp.move_count; ++i) {
    os << "  [" << i << "] " << cp.moves[i] << "\tcur=" << cp.pps[i].cur << "\tmax=" << cp.pps[i].max << "\tstage=" << cp.pps[i].stage << std::endl;
  }
  os << "  iv:   \thp=" << cp.iv.hp << "\tatk=" << cp.iv.attack << "\tdef=" << cp.iv.defense << "\tspc=" << cp.iv.special << "\tspd=" << cp.iv.speed << std::endl;
  os << "  ev:   \thp=" << cp.ev.hp << "\tatk=" << cp.ev.attack << "\tdef=" << cp.ev.defense << "\tspc=" << cp.ev.special << "\tspd=" << cp.ev.speed << std::endl;
  os << "  stats:\thp=" << cp.stats.hp << "\tatk=" << cp.stats.attack << "\tdef=" << cp.stats.defense << "\tspc=" << cp.stats.special << "\tspd=" << cp.stats.speed << std::endl;
  return os;
}

}
