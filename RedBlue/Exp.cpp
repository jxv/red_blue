#include "RedBlue.hpp"

namespace RedBlue {

int CalcExpFast(int level)
{
  return (4 * level * level * level) / 5;
}

int CalcExpMediumFast(int level)
{
	return level * level * level;
}

int CalcExpMediumSlow(int level)
{
  if (level == 1) return 0;
	return ((6 * level * level * level) / 5) - (15 * level * level) + (100 * level) - 140;
}

int CalcExpSlow(int level)
{
	return (5 * level * level * level) / 4;
}

int CalcSpecieExp(Specie s, int level)
{
  switch (s) {
  case Specie::Bulbasaur:
  case Specie::Ivysaur:
  case Specie::Venusaur: return CalcExpMediumSlow(level);
  default: return 100;
  }
}

}
