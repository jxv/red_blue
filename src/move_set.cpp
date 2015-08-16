#include <cassert>
#include "red_blue.h"

namespace red_blue {

MoveSet::MoveSet()
: moves{}
, move_count(0) {
}

MoveSet::MoveSet(Move m0,
  PowerPointStage s0)
: moves{m0}
, move_count(1) {
  init_power_points_set();
}

MoveSet::MoveSet(Move m0, Move m1,
  PowerPointStage s0,
  PowerPointStage s1)
: moves{m0, m1}
, move_count(2) {
  init_power_points_set();
}

MoveSet::MoveSet(Move m0, Move m1, Move m2,
  PowerPointStage s0,
  PowerPointStage s1,
  PowerPointStage s2)
: moves{m0, m1, m2}
, move_count(3) {
  init_power_points_set();
}

MoveSet::MoveSet(Move m0, Move m1, Move m2, Move m3,
  PowerPointStage s0,
  PowerPointStage s1,
  PowerPointStage s2,
  PowerPointStage s3)
: moves{m0, m1, m2, m3}
, move_count(4) {
  init_power_points_set();
}

void MoveSet::init_power_points_set() {
  for (auto i = 0; i < move_count; ++i) {
    power_point_set[i] = PowerPoints(moves[i]);
  }
}

}
