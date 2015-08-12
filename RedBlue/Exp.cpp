#include "RedBlue.hpp"

namespace RedBlue {

int calc_exp_fast(int level) {
  return (4 * level * level * level) / 5;
}

int calc_exp_medium_fast(int level) {
	return level * level * level;
}

int calc_exp_medium_slow(int level) {
  if (level == 1) return 0;
	return ((6 * level * level * level) / 5) - (15 * level * level) + (100 * level) - 140;
}

int calc_exp_slow(int level) {
	return (5 * level * level * level) / 4;
}

int calc_specie_exp(Specie::Tag s, int level) {
  switch (s) {
  case Specie::bulbasaur:
  case Specie::ivysaur:
  case Specie::venusaur: return calc_exp_medium_slow(level);
  default: return 100;
  }
}

}
