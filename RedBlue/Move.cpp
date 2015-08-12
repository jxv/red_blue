#include "RedBlue.hpp"

namespace RedBlue {

std::ostream& operator<<(std::ostream& os, Move::Tag move) {
  switch (move) {
  case Move::Absorb: os << "ABSORB"; break;
  case Move::Growl: os << "GROWL"; break;
  case Move::Tackle: os << "TACKLE"; break;
  case Move::Wrap: os << "WRAP"; break;
  }
}

int GetMoveMaxPP(Move::Tag) {
  return 10;
}

int CalcMoveMaxPP(Move::Tag, int stage) {
  return 10;
}

}
