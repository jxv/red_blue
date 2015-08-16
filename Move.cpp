#include "RedBlue.h"

namespace RedBlue {

std::ostream& operator<<(std::ostream& os, Move move) {
  switch (move) {
  case Move::Absorb: os << "ABSORB"; break;
  case Move::Growl: os << "GROWL"; break;
  case Move::Tackle: os << "TACKLE"; break;
  case Move::Wrap: os << "WRAP"; break;
  }
}

int GetMoveMaximumPowerPoints(Move) {
  return 10;
}

int CalculateMoveMaximumPowerPoints(Move, PowerPointStage) {
  return 10;
}

}
