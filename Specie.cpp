#include <cmath>
#include <cassert>
#include "RedBlue.h"

namespace RedBlue {

int GetSpecieID(Specie s) { return ToUType(s) + 1; }

NonVolStatus RemoveToxic(NonVolStatus nvs) {
  return nvs == NonVolStatus::Toxic ? NonVolStatus::Poison : nvs;
}

bool CanSpecieEvolveTo(Specie s, int level, Specie t) {
  switch (s) {
  case Specie::Bulbasaur: return t == Specie::Ivysaur && level >= 16;
  case Specie::Ivysaur: return t == Specie::Venusaur && level >= 32;
  case Specie::Eevee: return t == Specie::Jolteon || t == Specie::Flareon || t == Specie::Vaporeon;
  default: return false;
  }
}

const std::string GetSpecieName(Specie s) {
  switch (s) {
  case Specie::Bulbasaur: return "BULBASAUR";
  case Specie::Ivysaur: return "IVYSAUR";
  case Specie::Venusaur: return "VENUSAUR";
  default: return "Specie";
  }
}

}
