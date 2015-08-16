#include "red_blue.h"

namespace red_blue {

int get_experience_fast(int level) {
  return (4 * level * level * level) / 5;
}

int get_experience_medium_fast(int level) {
  return level * level * level;
}

int get_experience_medium_slow(int level) {
  if (level == 1) return 0;
  return ((6 * level * level * level) / 5) - (15 * level * level) + (100 * level) - 140;
}

int get_experience_slow(int level) {
  return (5 * level * level * level) / 4;
}

int get_experience_by_level(Specie s, int level) {
  switch (s) {
  case Specie::Bulbasaur:
  case Specie::Ivysaur:
  case Specie::Venusaur: return get_experience_medium_slow(level);
  default: return 100;
  }
}

}
