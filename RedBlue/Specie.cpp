#include <cmath>
#include <cassert>
#include "RedBlue.hpp"

namespace RedBlue {

int GetSpecieID(Specie s) { return ToUType(s) + 1; }

NonVolStatus RemoveToxic(NonVolStatus nvs) { return nvs == NonVolStatus::Toxic ? NonVolStatus::Poison : nvs; }

bool CanSpecieEvolveTo(Specie pkmn, int level, Specie p)
{
  switch (pkmn) {
  case Specie::Bulbasaur: return p == Specie::Ivysaur && level >= 16;
  case Specie::Ivysaur: return p == Specie::Venusaur && level >= 32;
  case Specie::Eevee: return p == Specie::Jolteon || p == Specie::Flareon || p == Specie::Vaporeon;
  default: return false;
  }
}

const std::string GetSpecieName(Specie specie)
{
  switch (specie) {
  case Specie::Bulbasaur: return "BULBASAUR";
  case Specie::Ivysaur: return "IVYSAUR";
  case Specie::Venusaur: return "VENUSAUR";
  default: return "Specie";
  }
}

}
