#include <cassert>
#include "RedBlue.hpp"

namespace RedBlue {

MoveSet::MoveSet()
: moves{}
, move_count(0) {
}

MoveSet::MoveSet(Move::Tag move0, int stage0)
: moves{move0}
, move_count(1) {
  init_pps();
}

MoveSet::MoveSet(Move::Tag move0, Move::Tag move1, int stage0 , int stage1)
: moves{move0, move1}
, move_count(2) {
  init_pps();
}

MoveSet::MoveSet(Move::Tag move0, Move::Tag move1, Move::Tag move2, int stage0 , int stage1, int stage2)
: moves{move0, move1, move2}
, move_count(3) {
  init_pps();
}

MoveSet::MoveSet(Move::Tag move0, Move::Tag move1, Move::Tag move2, Move::Tag move3, int stage0, int stage1, int stage2, int stage3)
: moves{move0, move1, move2, move3}
, move_count(4) {
  init_pps();
}

void MoveSet::init_pps() {
  for (auto i = 0; i < move_count; ++i) {
    const int pp = calc_move_max_pp(moves[i], 0);
    pps[i] = { .cur = pp, .max = pp, .stage = 0 };
  }
}

}
