#include "RedBlue.h"

namespace RedBlue {

CoreStats operator-(const CoreStats &a) { return { -a.healthPoints, -a.attack, -a.defense, -a.speed, -a.special }; }

CoreStats operator+(const CoreStats &a, const CoreStats &b) {
  return {
    a.healthPoints + b.healthPoints,
    a.attack + b.attack,
    a.defense + b.defense,
    a.special + b.special,
    a.speed + b.speed
  };
}

CoreStats operator-(const CoreStats &a, const CoreStats &b) { return a + (-b); }

CoreStats GetSpecieBaseStats(Specie s) noexcept {
  switch (s) {
  case Specie::Bulbasaur: return { 45, 49, 49, 65, 45 };
  case Specie::Ivysaur: return { 60, 62, 63, 80, 60 };
  case Specie::Venusaur: return { 80, 82, 83, 100, 80 };
  case Specie::Charmander: return { 39, 52, 43, 50, 65 };
  case Specie::Charmeleon: return { 58, 64, 58, 65, 80 };
  case Specie::Charizard: return { 78, 84, 78, 85, 100 };
  case Specie::Squirtle: return { 44, 48, 65, 50 , 43 };
  case Specie::Wartortle: return { 59, 63, 80, 65, 58 };
  case Specie::Blastoise: return { 79, 83, 100, 85, 78 };
  case Specie::Caterpie: return { 45, 30, 35, 20, 45 };
  case Specie::Metapod: return { 50, 20, 55, 25, 30 };
  case Specie::Butterfree: return { 60, 45, 50, 80, 70 };
  case Specie::Weedle: return { 40, 35, 30, 20, 50 };
  case Specie::Kakuna: return { 45, 25, 50, 25, 35 };
  case Specie::Beedrill: return { 65, 80, 40, 45, 75 };
  case Specie::Pidgey: return { 40, 45, 40, 35, 56 };
  case Specie::Pidgeotto: return { 63, 60, 55, 50, 71 };
  case Specie::Pidgeot: return { 83, 80, 75, 70, 91 };
  };
}

CoreStats MakeIndividualValues(int atk, int def, int spc, int spd) {
  assert((atk & 0xf) == atk);
  assert((def & 0xf) == def);
  assert((spc & 0xf) == spc);
  assert((spd & 0xf) == spd);
  const int hp = ((0x1 & atk) << 3) | ((0x1 & def) << 2) | ((0x1 & spd) << 1) | (0x1 & spc);
  return { hp, atk, def, spc, spd };
}

}
