#include <cmath>
#include <cassert>
#include "RedBlue.hpp"

namespace RedBlue {

int get_specie_id(Specie::Tag s) { return s + 1; }

NonVolStatus::Tag remove_toxic(NonVolStatus::Tag nvs) { return nvs == NonVolStatus::toxic ? NonVolStatus::poison : nvs; }

bool can_specie_evolve_to(Specie::Tag s, int level, Specie::Tag t) {
  switch (s) {
  case Specie::bulbasaur: return t == Specie::ivysaur && level >= 16;
  case Specie::ivysaur: return t == Specie::venusaur && level >= 32;
  case Specie::eevee: return t == Specie::jolteon || t == Specie::flareon || t == Specie::vaporeon;
  default: return false;
  }
}

const std::string get_specie_name(Specie::Tag specie) {
  switch (specie) {
  case Specie::bulbasaur: return "BULBASAUR";
  case Specie::ivysaur: return "IVYSAUR";
  case Specie::venusaur: return "VENUSAUR";
  default: return "Specie";
  }
}

}
