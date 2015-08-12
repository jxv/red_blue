#ifndef RedBlue_hpp
#define RedBlue_hpp

#include <iostream>
#include <cassert>
#include <tuple>
#include "Util.hpp"

///.
namespace RedBlue {

///.
enum class Specie {
  Bulbasaur,
  Ivysaur,
  Venusaur,
  Charmander,
  Charmeleon,
  Charizard,
  Squirtle,
  Wartortle,
  Blastoise,
  Caterpie,
  Metapod,
  Butterfree,
  Weedle,
  Kakuna,
  Beedrill,
  Pidgey,
  Pidgeotto,
  Pidgeot,
  Rattata,
  Raticate,
  Spearow,
  Fearow,
  Ekans,
  Arbok,
  Pikachu,
  Raichu,
  Sandshrew,
  Sandslash,
  NidoranFemale,
  Nidorina,
  Nidoqueen,
  NidoranMale,
  Nidorino,
  Nidoking,
  Clefairy,
  Clefable,
  Vulpix,
  Ninetales,
  Jigglypuff,
  Wigglytuff,
  Zubat,
  Golbat,
  Oddish,
  Gloom,
  Vileplume,
  Paras,
  Parasect,
  Venonat,
  Venomoth,
  Diglett,
  Dugtrio,
  Meowth,
  Persian,
  Psyduck,
  Golduck,
  Mankey,
  Primeape,
  Growlithe,
  Arcanine,
  Poliwag,
  Poliwhirl,
  Poliwrath,
  Abra,
  Kadabra,
  Alakazam,
  Machop,
  Machoke,
  Machamp,
  Bellsprout,
  Weepinbell,
  Victreebel,
  Tentacool,
  Tentacruel,
  Geodude,
  Graveler,
  Golem,
  Ponyta,
  Rapidash,
  Slowpoke,
  Slowbrow,
  Magnemite,
  Magneton,
  FarfetchD,
  Doduo,
  Dodrio,
  Seel,
  Dewgong,
  Grimer,
  Muk,
  Shellder,
  Cloyster,
  Gastly,
  Haunter,
  Gengar,
  Onix,
  Drowzee,
  Hypno,
  Krabby,
  Kingler,
  Voltorb,
  Electrode,
  Exeggcute,
  Exeggutor,
  Cubone,
  Marowak,
  Hitmonlee,
  Hitmonchan,
  Lickitung,
  Koffing,
  Weezing,
  Rhyhorn,
  Rhydon,
  Chansey,
  Tangela,
  Kangaskhan,
  Horsea,
  Seadra,
  Goldeen,
  Seaking,
  Staryu,
  Starmie,
  MrMime,
  Scyther,
  Jynx,
  Electabuzz,
  Magmar,
  Pinsir,
  Tauros,
  Magikarp,
  Gyarados,
  Lapras,
  Ditto,
  Eevee,
  Vaporeon,
  Jolteon,
  Flareon,
  Porygon,
  Omanyte,
  Omastar,
  Kabuto,
  Kabutops,
  Aerodactyl,
  Snorlax,
  Articuno,
  Zapdos,
  Moltres,
  Dratini,
  Dragonair,
  Dragonite,
  Mewtwo,
  Mew,
};

///.
enum class Move {
  Absorb,
  Growl,
  Tackle,
  Wrap,
};

std::ostream& operator<<(std::ostream& os, Move move);

///.
struct PP {
  int cur;
  int max;
  int stage;
};

class CorePkmn;

///.
class MoveSet {
public:
  MoveSet();
  MoveSet(Move, int stage0 = 0);
  MoveSet(Move, Move, int stage0 = 0, int stage1 = 0);
  MoveSet(Move, Move, Move, int stage0 = 0, int stage1 = 0, int stage2 = 0);
  MoveSet(Move, Move, Move, Move, int stage0 = 0, int stage1 = 0, int stage2 = 0, int stage3 = 0);
private: 
  std::array<Move, 4> mMoves;
  std::array<PP, 4> mPPs;
  int mMoveCount;
  //
  void InitPPs();
  //
  friend class CorePkmn;
};

///.
enum class Badge {
  Boulder,
  Cascade,
  Thunder,
  Rainbow,
  Soul,
  Marsh,
  Fire,
  Earth,
};

///.
using Badges = FixedSet<Badge, NextUType(Badge::Earth)>;

///.
enum class NonVolStatus {
  Burn,
  Freeze,
  Paralysis,
  Poison,
  None,
  Sleep,
  Toxic,
};

std::ostream& operator<<(std::ostream&, NonVolStatus);

///.
enum class VolStatus {
  Confusion,
  Flinch,
  LeechSeed,
  Nightmare,
  PartiallyTrapped,
};

struct VolStatuses {
  int confusion;
  int flinch;
  int leechSeed;
  int nightmare;
  int partiallyTrapped;
};

struct CoreStats {
  int hp;
  int attack;
  int defense;
  int special;
  int speed;
};

CoreStats operator- (const CoreStats &a);
CoreStats operator+ (const CoreStats &a, const CoreStats &b);
CoreStats operator- (const CoreStats &a, const CoreStats &b);

struct ActiveStats {
  int attack;
  int defense;
  int special;
  int speed;
  int evasion;
  int accuracy;
};

///.
class CorePkmn {
public:
  CorePkmn(CoreStats iv, Specie, int level, MoveSet);
  //
  void Evolve(Specie);
  void RestoreHP();
  void RestoreHP(int hp);
  void DamageHP(int hp);
  void AddExp(int exp);
  void AddEV(CoreStats);
  void Burn();
  void Freeze();
  void Paralyze();
  void Poison();
  void Sleep();
  void Intoxicate();
  void RestoreNonVolStatus();
  void SwapMove(int idx0, int idx1);
  void LearnMove(Move, int idx);
  void UsePP(int idx);
  void RestorePP();
  void RestorePP(int idx);
  void RestorePP(int idx, int val);
  void IncrementPPStage(int idx);
  //
  Specie GetSpecie() const;
  int GetHP() const;
  int GetExp() const;
  NonVolStatus GetNonVolStatus() const;
  int GetMoveCount() const;
  Move GetMove(int idx) const;
  const PP& GetPP(int idx) const;
  int GetLevel() const;
  CoreStats GetStats() const;
  bool IsAlive() const;
private:
  Specie mSpecie;
  int mHP;
  int mExp;
  CoreStats mIV;
  CoreStats mEV;
  NonVolStatus mNonVolStatus;
  int mMoveCount;
  std::array<Move, 4> mMoves;
  std::array<PP, 4> mPPs;
  int mLevel;
  CoreStats mStats;
  //
  void UpdateLevel();
  void UpdateStats();
  //
  friend std::ostream& operator<<(std::ostream&, const CorePkmn&);
};

std::ostream& operator<<(std::ostream&, const CorePkmn&);

struct ActivePkmn {
public:
  const ActiveStats& GetStats() const;

private:
  CorePkmn& mCorePkmn;
  opt::optional<Specie> mTransform;
  VolStatuses mVolStatuses;
  ActiveStats mStats;
  ActiveStats mStages;
};

///.
enum class Player {
  A,
  B,
};
  
using ActiveTable = Table<Player, ActivePkmn, NextUType(Player::B)>;
using CoresTable = Table<Player, std::array<CorePkmn, 6>, NextUType(Player::B)>;

class Battle {
public:
  Battle();

  ActivePkmn& GetHotActivePkmn();
  ActivePkmn& GetColdActivePkmn();
  CorePkmn& GetHotCorePkmn();
  CorePkmn& GetColdCorePkmn();

private:
  Player mHot;
  Player mCold;
};

CoreStats GetSpecieBaseStats(Specie s) noexcept;
CoreStats MakeIV(int atk, int def, int spc, int spd);

int GetSpecieID(Specie s);
const std::string GetSpecieName(Specie);
bool CanSpecieEvolveTo(Specie, int level, Specie);

int CalcSpecieExp(Specie p, int level);
int CalcExpFast(int level);
int CalcExpMediumFast(int level);
int CalcExpMediumSlow(int level);
int CalcExpSlow(int level);

int GetMoveMaxPP(Move);
int CalcMoveMaxPP(Move, int stage);

}

#endif
