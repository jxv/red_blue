#include <cmath>
#include <cassert>
#include "RedBlue.hpp"

namespace RedBlue {

int GetSpecieID(Specie::Tag s) { return s + 1; }

NonVolStatus::Tag RemoveToxic(NonVolStatus::Tag nvs) { return nvs == NonVolStatus::Toxic ? NonVolStatus::Poison : nvs; }

bool CanSpecieEvolveTo(Specie::Tag s, int level, Specie::Tag t) {
  switch (s) {
  case Specie::Bulbasaur: return t == Specie::Ivysaur && level >= 16;
  case Specie::Ivysaur: return t == Specie::Venusaur && level >= 32;
  case Specie::Eevee: return t == Specie::Jolteon || t == Specie::Flareon || t == Specie::Vaporeon;
  default: return false;
  }
}

const std::string GetSpecieName(Specie::Tag specie) {
  switch (specie) {
  case Specie::Bulbasaur: return "BULBASAUR";
  case Specie::Ivysaur: return "IVYSAUR";
  case Specie::Venusaur: return "VENUSAUR";
  default: return "Specie";
  }
}

}
