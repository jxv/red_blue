#include <cassert>
#include "red_blue.h"

namespace red_blue {

const PowerPoints def_pp = PowerPoints(Move::Tackle);

MoveSet::MoveSet()
: moves{}
, power_point_set{def_pp, def_pp, def_pp, def_pp}
, size(0) {
}

MoveSet::MoveSet(Move m0,
  PowerPointStage s0)
: moves{m0}
, power_point_set{def_pp, def_pp, def_pp, def_pp}
, size(1) {
  init_power_point_set();
}

MoveSet::MoveSet(Move m0, Move m1,
  PowerPointStage s0,
  PowerPointStage s1)
: moves{m0, m1}
, power_point_set{def_pp, def_pp, def_pp, def_pp}
, size(2) {
  init_power_point_set();
}

MoveSet::MoveSet(Move m0, Move m1, Move m2,
  PowerPointStage s0,
  PowerPointStage s1,
  PowerPointStage s2)
: moves{m0, m1, m2}
, power_point_set{def_pp, def_pp, def_pp, def_pp}
, size(3) {
  init_power_point_set();
}

MoveSet::MoveSet(Move m0, Move m1, Move m2, Move m3,
  PowerPointStage s0,
  PowerPointStage s1,
  PowerPointStage s2,
  PowerPointStage s3)
: moves{m0, m1, m2, m3}
, power_point_set{def_pp, def_pp, def_pp, def_pp}
, size(4) {
  init_power_point_set();
}

void MoveSet::init_power_point_set() {
  for (auto i = 0; i < size; ++i) {
    power_point_set[i] = PowerPoints(moves[i]);
  }
}

int MoveSet::get_size() const {
  return size;
}

Move MoveSet::get_move(int idx) const {
  assert(idx >= 0 && idx < size);
  return moves[idx];
}

const PowerPoints& MoveSet::get_power_points(int idx) const {
  assert(idx >= 0 && idx < size);
  return power_point_set[idx];
}

void MoveSet::swap(int idx0, int idx1) {
  assert(idx0 >= 0 && idx0 < size);
  assert(idx1 >= 0 && idx1 < size);
  {
    auto tmp = moves[idx0];
    moves[idx0] = moves[idx1];
    moves[idx1] = tmp;
  }
  {
    auto tmp = power_point_set[idx0];
    power_point_set[idx0] = power_point_set[idx1];
    power_point_set[idx1] = tmp;
  }
}

void MoveSet::learn(Move m, int idx) {
  assert((idx >= 0 && idx < size) || (idx == size && size < 4));
  moves[idx] = m;
  power_point_set[idx] = PowerPoints(m);
  if (idx == size) ++size;
}

void MoveSet::use(int idx) {
  assert(idx >= 0 && idx < size);
  power_point_set[idx].use();
}

void MoveSet::restore() {
  for (int i = 0; i < size; ++i) {
    power_point_set[i].restore_full();
  }
}

void MoveSet::restore(int idx) {
  assert(idx >= 0 && idx < size);
  power_point_set[idx].restore_full();
}

void MoveSet::restore(int idx, int addition) {
  assert(idx >= 0 && idx < size);
  power_point_set[idx].restore(addition);
}

void MoveSet::increment_stage(int idx) {
  assert(idx >= 0 && idx < size);
}

}
