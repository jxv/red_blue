#include <cassert>
#include "RedBlue.h"

namespace RedBlue {

MoveSet::MoveSet()
: moves{}
, moveCount(0)
{}

MoveSet::MoveSet(Move m0,
  PowerPointStage s0)
: moves{m0}
, moveCount(1)
{ InitPowerPointsSet(); }

MoveSet::MoveSet(Move m0, Move m1,
  PowerPointStage s0,
  PowerPointStage s1)
: moves{m0, m1}
, moveCount(2)
{ InitPowerPointsSet(); }

MoveSet::MoveSet(Move m0, Move m1, Move m2,
  PowerPointStage s0,
  PowerPointStage s1,
  PowerPointStage s2)
: moves{m0, m1, m2}
, moveCount(3)
{ InitPowerPointsSet(); }

MoveSet::MoveSet(Move m0, Move m1, Move m2, Move m3,
  PowerPointStage s0,
  PowerPointStage s1,
  PowerPointStage s2,
  PowerPointStage s3)
: moves{m0, m1, m2, m3}
, moveCount(4)
{ InitPowerPointsSet(); }

void MoveSet::InitPowerPointsSet() {
  for (auto i = 0; i < moveCount; ++i) {
    powerPointSet[i] = PowerPoints(moves[i]);
  }
}

}
