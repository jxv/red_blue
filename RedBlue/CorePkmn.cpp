#include <cmath>
#include <cassert>
#include "RedBlue.hpp"

namespace RedBlue {

CorePkmn::CorePkmn(CoreStats iv, Specie::Tag specie, int level, MoveSet moveSet)
: mSpecie(specie)
, mIV(iv)
, mEV{0,0,0,0,0}
, mLevel(level)
, mExp(CalcSpecieExp(specie, level))
, mMoves(moveSet.mMoves)
, mMoveCount(moveSet.mMoveCount)
, mPPs(moveSet.mPPs)
, mNonVolStatus(NonVolStatus::None)
{
  UpdateStats();
  mHP = mStats.hp;
}

void CorePkmn::Evolve(Specie::Tag specie) {
  assert(CanSpecieEvolveTo(mSpecie, mLevel, specie));
  mSpecie = specie;
}

void CorePkmn::RestoreHP() { mHP = mStats.hp; }

void CorePkmn::RestoreHP(int hp) {
  assert(mHP < mStats.hp);
  mHP += hp;
  if (mHP > mStats.hp) mHP = mStats.hp;
}

void CorePkmn::DamageHP(int hp) {
  assert(mHP > 0);
  mHP -= hp;
  if (mHP < 0) mHP = 0;
  if (mHP == 0) mNonVolStatus = NonVolStatus::None;
}

void CorePkmn::AddExp(int exp) {
  const int oldExp = mExp;
  const int maxExp = CalcSpecieExp(mSpecie, 100);
  assert(exp <= maxExp);
  if (mExp == maxExp) return;
  mExp += exp;
  if (mExp > maxExp) mExp = maxExp;
  UpdateLevel();
}

bool validateEV(const CoreStats &e) {
  return
    (e.hp & 0xffff) == e.hp &&
    (e.attack & 0xffff) == e.attack &&
    (e.defense & 0xffff) == e.defense &&
    (e.speed & 0xffff) == e.speed &&
    (e.special & 0xffff) == e.special;
}

void CorePkmn::AddEV(CoreStats ev) {
  assert(validateEV(mEV));
  assert(validateEV(ev));
  const auto  oldEV = mEV;
  // ev = mEV + ev;
  // TODO
}

void CorePkmn::Burn() {
  assert(IsAlive());
  assert(mNonVolStatus == NonVolStatus::None);
  mNonVolStatus = NonVolStatus::Burn;
}

void CorePkmn::Freeze() {
  assert(IsAlive());
  assert(mNonVolStatus == NonVolStatus::None);
  mNonVolStatus = NonVolStatus::Freeze;
}

void CorePkmn::Paralyze() {
  assert(IsAlive());
  assert(mNonVolStatus == NonVolStatus::None);
  mNonVolStatus = NonVolStatus::Paralysis;
}

void CorePkmn::Poison() {
  assert(IsAlive());
  assert(mNonVolStatus == NonVolStatus::None || mNonVolStatus == NonVolStatus::Toxic);
  mNonVolStatus = NonVolStatus::Poison;
}

void CorePkmn::Sleep() {
  assert(IsAlive());
  assert(mNonVolStatus == NonVolStatus::None);
  mNonVolStatus = NonVolStatus::Sleep;
}

void CorePkmn::Intoxicate() {
  assert(IsAlive());
  assert(mNonVolStatus == NonVolStatus::None);
  mNonVolStatus = NonVolStatus::Toxic;
}

void CorePkmn::RestoreNonVolStatus() { mNonVolStatus = NonVolStatus::None; }

void CorePkmn::SwapMove(int idx0, int idx1) {
  assert(idx0 >= 0 && idx0 < mMoveCount);
  assert(idx1 >= 0 && idx1 < mMoveCount);
  std::swap(mMoves[idx0], mMoves[idx1]);
}

void CorePkmn::LearnMove(Move move, int idx) {
  assert(idx >= 0 && idx < mMoveCount);
  assert(/* CanLearnMove(mSpecie, move) */ true);
  assert(/* !HasMove(move) */ true);
  mMoves[idx] = move;
  /// TODO: Reset PP 
  mPPs[idx] = (PP) { .cur = 15, .max = 15, .stage = 0 };
}

void CorePkmn::UsePP(int idx) {
  assert(idx >= 0 && idx < mMoveCount);
  assert(mPPs[idx].cur > 0);
  --mPPs[idx].cur;
}

void CorePkmn::RestorePP() {
  for (auto& pp : mPPs) {
    pp.cur = pp.max;
  }
}

void CorePkmn::RestorePP(int idx) {
  assert(idx >= 0 && idx < mMoveCount);
  auto& pp = mPPs[idx];
  pp.cur = pp.max;
}

void CorePkmn::RestorePP(int idx, int val) {
  assert(idx >= 0 && idx < mMoveCount);
  auto& pp = mPPs[idx];
  pp.cur += val;
  pp.cur %= pp.max + 1;
}

void CorePkmn::IncrementPPStage(int idx) {
  assert(idx >= 0 && idx < mMoveCount);
  auto& pp = mPPs[idx];
  assert(pp.stage >= 0 && pp.stage < 6);
  ++pp.stage;
}

Specie::Tag CorePkmn::GetSpecie() const { return mSpecie; }

int CorePkmn::GetHP() const { return mHP; }

int CorePkmn::GetExp() const { return mExp; }

NonVolStatus::Tag CorePkmn::GetNonVolStatus() const { return mNonVolStatus; }

int CorePkmn::GetMoveCount() const { return mMoveCount; }

Move CorePkmn::GetMove(int idx) const {

  assert(idx >= 0 && idx < mMoveCount);
  return mMoves[idx];
}

const PP& CorePkmn::GetPP(int idx) const {

  assert(idx >= 0 && idx < mMoveCount);
  return mPPs[idx];
}

int CorePkmn::GetLevel() const { return mLevel; }

CoreStats CorePkmn::GetStats() const { return mStats; }

void CorePkmn::UpdateLevel() {
  assert(mLevel >= 1 && mLevel <= 100);
  while (mLevel < 100 && CalcSpecieExp(mSpecie, mLevel + 1) < mExp) ++mLevel;
}

void CorePkmn::UpdateStats() {
  assert(mLevel >= 1 && mLevel <= 100);
  auto compute = [&](int iv, int ev, int base) -> int {
    return ((iv + base + (std::sqrt(ev) / 8) + 50) * mLevel) / 50;
  };
  auto base = GetSpecieBaseStats(mSpecie);
  mStats.hp = compute(mIV.hp, mEV.hp, base.hp) + 10;
  mStats.attack = compute(mIV.attack, mEV.attack, base.attack) + 5;
  mStats.defense = compute(mIV.defense, mEV.defense, base.defense) + 5;
  mStats.special = compute(mIV.special, mEV.special, base.special) + 5;
  mStats.speed = compute(mIV.speed, mEV.speed, base.speed) + 5;
}

bool CorePkmn::IsAlive() const {
  assert(mHP >= 0 && mHP <= mStats.hp);
  return mHP > 0;
}

std::ostream& operator<<(std::ostream& os, const CorePkmn& cp) {
  os << "NAME" << std::endl;
  os << "  Specie: " << GetSpecieName(cp.mSpecie) << std::endl;
  os << "  HP: " << cp.mHP << std::endl;
  os << "  Exp: " << cp.mExp << std::endl;
  os << "  Level: " << cp.mLevel << std::endl;
  os << "  NonVolStatus: " << cp.mNonVolStatus << std::endl;
  os << "  Moves:" << std::endl;
  for (auto i = 0; i < cp.mMoveCount; ++i) {
    os << "  [" << i << "] " << cp.mMoves[i] << "\tcur=" << cp.mPPs[i].cur << "\tmax=" << cp.mPPs[i].max << "\tstage=" << cp.mPPs[i].stage << std::endl;
  }
  os << "  IV:   \thp=" << cp.mIV.hp << "\tatk=" << cp.mIV.attack << "\tdef=" << cp.mIV.defense << "\tspc=" << cp.mIV.special << "\tspd=" << cp.mIV.speed << std::endl;
  os << "  EV:   \thp=" << cp.mEV.hp << "\tatk=" << cp.mEV.attack << "\tdef=" << cp.mEV.defense << "\tspc=" << cp.mEV.special << "\tspd=" << cp.mEV.speed << std::endl;
  os << "  Stats:\thp=" << cp.mStats.hp << "\tatk=" << cp.mStats.attack << "\tdef=" << cp.mStats.defense << "\tspc=" << cp.mStats.special << "\tspd=" << cp.mStats.speed << std::endl;
  return os;
}

}
