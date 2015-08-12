#include <cassert>
#include "RedBlue.hpp"

namespace RedBlue {

MoveSet::MoveSet()
: mMoves{}
, mMoveCount(0) {
}

MoveSet::MoveSet(Move move0, int stage0)
: mMoves{move0}
, mMoveCount(1) {
  InitPPs();
}

MoveSet::MoveSet(Move move0, Move move1, int stage0 , int stage1)
: mMoves{move0, move1}
, mMoveCount(2) {
  InitPPs();
}

MoveSet::MoveSet(Move move0, Move move1, Move move2, int stage0 , int stage1, int stage2)
: mMoves{move0, move1, move2}
, mMoveCount(3) {
  InitPPs();
}

MoveSet::MoveSet(Move move0, Move move1, Move move2, Move move3, int stage0, int stage1, int stage2, int stage3)
: mMoves{move0, move1, move2, move3}
, mMoveCount(4) {
  InitPPs();
}

void MoveSet::InitPPs() {
  for (auto i = 0; i < mMoveCount; ++i) {
    const int pp = CalcMoveMaxPP(mMoves[i], 0);
    mPPs[i] = { .cur = pp, .max = pp, .stage = 0 };
  }
}

}
