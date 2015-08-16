#include "red_blue.h"

namespace red_blue {

std::ostream& operator<<(std::ostream& os, Move move) {
  switch (move) {
  case Move::Absorb: os << "ABSORB"; break;
  case Move::Growl: os << "GROWL"; break;
  case Move::Tackle: os << "TACKLE"; break;
  case Move::Wrap: os << "WRAP"; break;
  }
}

int get_maximum_power_points(Move) {
  return 10;
}

int calculate_maximum_power_points(Move, PowerPointStage) {
  return 10;
}

}
