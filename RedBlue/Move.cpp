#include "RedBlue.hpp"

namespace RedBlue {

std::ostream& operator<<(std::ostream& os, Move::Tag move) {
  switch (move) {
  case Move::absorb: os << "ABSORB"; break;
  case Move::growl: os << "GROWL"; break;
  case Move::tackle: os << "TACKLE"; break;
  case Move::wrap: os << "WRAP"; break;
  }
}

int get_move_max_pp(Move::Tag) {
  return 10;
}

int calc_move_max_pp(Move::Tag, int stage) {
  return 10;
}

}
