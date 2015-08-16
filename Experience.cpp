#include "RedBlue.h"

namespace RedBlue {

int CalculateExperienceFast(int level) {
  return (4 * level * level * level) / 5;
}

int CalculateExperienceMediumFast(int level) {
  return level * level * level;
}

int CalculateExperienceMediumSlow(int level) {
  if (level == 1) return 0;
  return ((6 * level * level * level) / 5) - (15 * level * level) + (100 * level) - 140;
}

int CalculateExperienceSlow(int level) {
  return (5 * level * level * level) / 4;
}

int CalculateSpecieExperience(Specie s, int level) {
  switch (s) {
  case Specie::Bulbasaur:
  case Specie::Ivysaur:
  case Specie::Venusaur: return CalculateExperienceMediumSlow(level);
  default: return 100;
  }
}

}
