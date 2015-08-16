#include <cmath>
#include <cassert>
#include "red_blue.h"

namespace red_blue {

int get_id(Specie s) { return ToUType(s) + 1; }

bool can_evolve_to(Specie s, int level, Specie t) {
  switch (s) {
  case Specie::Bulbasaur: return t == Specie::Ivysaur && level >= 16;
  case Specie::Ivysaur: return t == Specie::Venusaur && level >= 32;
  case Specie::Eevee: return t == Specie::Jolteon || t == Specie::Flareon || t == Specie::Vaporeon;
  default: return false;
  }
}

const std::string get_name(Specie s) {
  switch (s) {
  case Specie::Bulbasaur: return "BULBASAUR";
  case Specie::Ivysaur: return "IVYSAUR";
  case Specie::Venusaur: return "VENUSAUR";
  default: return "Specie";
  }
}

std::ostream& operator<<(std::ostream& os, Specie s) {
  switch (s) {
  case Specie::Bulbasaur: os << "BULBASAUR"; break;
  case Specie::Ivysaur: os << "IVYSAUR"; break;
  case Specie::Venusaur: os << "VENUSAUR"; break;
  default: assert(false);
  }
  return os;
}

}
