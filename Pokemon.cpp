#include <cmath>
#include <cassert>
#include "RedBlue.h"

namespace RedBlue {

Pokemon::Pokemon(CoreStats iv, Specie s, int lvl, MoveSet ms)
: specie(s)
, individualValues(iv)
, effortValues{0,0,0,0,0}
, level(lvl)
, experience(CalculateSpecieExperience(specie, lvl))
, moves(ms.moves)
, moveCount(ms.moveCount)
, powerPointSet(ms.powerPointSet)
, nonVolStatus(NonVolStatus::None)
{
  UpdateStats();
  healthPoints = stats.healthPoints;
}

void Pokemon::Evolve(Specie to) {
  assert(CanSpecieEvolveTo(specie, level, to));
  specie = to;
}

void Pokemon::RestoreHealthPoints() { healthPoints = stats.healthPoints; }

void Pokemon::RestoreHealthPoints(int hp) {
  assert(hp > 0);
  assert(healthPoints < stats.healthPoints);
  healthPoints += hp;
  if (healthPoints > stats.healthPoints) healthPoints = stats.healthPoints;
}

void Pokemon::DamageHealthPoints(int hp) {
  assert(hp > 0);
  assert(healthPoints > 0);
  healthPoints -= hp;
  if (healthPoints < 0) healthPoints = 0;
  if (healthPoints == 0) nonVolStatus = NonVolStatus::None;
}

void Pokemon::AddExperience(int exp) {
  const int oldExp = experience;
  const int maxExp = CalculateSpecieExperience(specie, 100);
  assert(experience <= maxExp);
  if (experience == maxExp) return;
  experience += exp;
  if (experience > maxExp) experience = maxExp;
  UpdateLevel();
}

bool ValidateEffortValues(const CoreStats &exp) {
  return
    (exp.healthPoints & 0xffff) == exp.healthPoints &&
    (exp.attack & 0xffff) == exp.attack &&
    (exp.defense & 0xffff) == exp.defense &&
    (exp.speed & 0xffff) == exp.speed &&
    (exp.special & 0xffff) == exp.special;
}

void Pokemon::AddEffortValues(CoreStats ev) {
  assert(ValidateEffortValues(ev));
  assert(ValidateEffortValues(effortValues));
  const auto  oldEv = effortValues;
  // TODO
}

void Pokemon::Burn() {
  assert(IsAlive());
  assert(nonVolStatus == NonVolStatus::None);
  nonVolStatus = NonVolStatus::Burn;
}

void Pokemon::Freeze() {
  assert(IsAlive());
  assert(nonVolStatus == NonVolStatus::None);
  nonVolStatus = NonVolStatus::Freeze;
}

void Pokemon::Paralyze() {
  assert(IsAlive());
  assert(nonVolStatus == NonVolStatus::None);
  nonVolStatus = NonVolStatus::Paralysis;
}

void Pokemon::Poison() {
  assert(IsAlive());
  assert(nonVolStatus == NonVolStatus::None || nonVolStatus == NonVolStatus::Toxic);
  nonVolStatus = NonVolStatus::Poison;
}

void Pokemon::Sleep() {
  assert(IsAlive());
  assert(nonVolStatus == NonVolStatus::None);
  nonVolStatus = NonVolStatus::Sleep;
}

void Pokemon::Intoxicate() {
  assert(IsAlive());
  assert(nonVolStatus == NonVolStatus::None);
  nonVolStatus = NonVolStatus::Toxic;
}

void Pokemon::RestoreNonVolStatus() { nonVolStatus = NonVolStatus::None; }

void Pokemon::SwapMove(int idx0, int idx1) {
  assert(idx0 >= 0 && idx0 < moveCount);
  assert(idx1 >= 0 && idx1 < moveCount);
  std::swap(moves[idx0], moves[idx1]);
}

void Pokemon::LearnMove(Move m, int idx) {
  assert(idx >= 0 && idx < moveCount);
  assert(/* can_learn_move(specie, m) */ true);
  assert(/* !has_move(m) */ true);
  moves[idx] = m;
  /// TODO: Reset PP 
  powerPointSet[idx] = PowerPoints(m);
}

void Pokemon::UsePowerPoint(int idx) {
  assert(idx >= 0 && idx < moveCount);
  powerPointSet[idx].Use();
}

void Pokemon::RestorePowerPoints() {
  for (auto& pp : powerPointSet) {
    pp.RestoreFull();
  }
}

void Pokemon::RestorePowerPoints(int idx) {
  assert(idx >= 0 && idx < moveCount);
  powerPointSet[idx].RestoreFull();
}

void Pokemon::RestorePowerPoints(int idx, int addition) {
  assert(idx >= 0 && idx < moveCount);
  powerPointSet[idx].Restore(addition);
}

void Pokemon::IncrementPowerPointsStage(int idx) {
  assert(idx >= 0 && idx < moveCount);
  powerPointSet[idx].IncrementStage();
}

Specie Pokemon::GetSpecie() const { return specie; }

int Pokemon::GetHealthPoints() const { return healthPoints; }

int Pokemon::GetExperience() const { return experience; }

NonVolStatus Pokemon::GetNonVolStatus() const { return nonVolStatus; }

int Pokemon::GetMoveCount() const { return moveCount; }

Move Pokemon::GetMove(int idx) const {
  assert(idx >= 0 && idx < moveCount);
  return moves[idx];
}

const PowerPoints& Pokemon::GetPowerPoints(int idx) const {

  assert(idx >= 0 && idx < moveCount);
  return powerPointSet[idx];
}

int Pokemon::GetLevel() const { return level; }

CoreStats Pokemon::GetStats() const { return stats; }

void Pokemon::UpdateLevel() {
  assert(level >= 1 && level <= 100);
  while (level < 100 && CalculateSpecieExperience(specie, level + 1) < experience) ++level;
}

void Pokemon::UpdateStats() {
  assert(level >= 1 && level <= 100);
  auto compute = [&](int iv, int ev, int base) -> int {
    return ((iv + base + (std::sqrt(ev) / 8) + 50) * level) / 50;
  };
  auto base = GetSpecieBaseStats(specie);
  stats.healthPoints = compute(individualValues.healthPoints, effortValues.healthPoints, base.healthPoints) + 10;
  stats.attack = compute(individualValues.attack, effortValues.attack, base.attack) + 5;
  stats.defense = compute(individualValues.defense, effortValues.defense, base.defense) + 5;
  stats.special = compute(individualValues.special, effortValues.special, base.special) + 5;
  stats.speed = compute(individualValues.speed, effortValues.speed, base.speed) + 5;
}

bool Pokemon::IsAlive() const {
  assert(healthPoints >= 0 && healthPoints <= stats.healthPoints);
  return healthPoints > 0;
}

std::ostream& operator<<(std::ostream& os, const Pokemon& p) {
  os << "NAME" << std::endl;
  os << "  specie: " << GetSpecieName(p.specie) << std::endl;
  os << "  hp: " << p.healthPoints << std::endl;
  os << "  exp: " << p.experience << std::endl;
  os << "  level: " << p.level << std::endl;
  os << "  nonVolStatus: " << p.nonVolStatus << std::endl;
  os << "  moves:" << std::endl;
  for (auto i = 0; i < p.moveCount; ++i) {
    os << "  [" << i << "] " << p.moves[i] << "\tcur=" << p.powerPointSet[i].GetCurrent() << "\tmax=" << p.powerPointSet[i].GetMaximum() << "\tstage=" << p.powerPointSet[i].GetStage() << std::endl;
  }
  os << "  iv:   \thp=" << p.individualValues.healthPoints << "\tatk=" << p.individualValues.attack << "\tdef=" << p.individualValues.defense << "\tspc=" << p.individualValues.special << "\tspd=" << p.individualValues.speed << std::endl;
  os << "  ev:   \thp=" << p.effortValues.healthPoints << "\tatk=" << p.effortValues.attack << "\tdef=" << p.effortValues.defense << "\tspc=" << p.effortValues.special << "\tspd=" << p.effortValues.speed << std::endl;
  os << "  stats:\thp=" << p.stats.healthPoints << "\tatk=" << p.stats.attack << "\tdef=" << p.stats.defense << "\tspc=" << p.stats.special << "\tspd=" << p.stats.speed << std::endl;
  return os;
}

}
