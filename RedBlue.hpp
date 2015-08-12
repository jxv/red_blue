#ifndef RedBlue_hpp
#define RedBlue_hpp

#include <iostream>
#include <cassert>
#include <tuple>
#include "Util.hpp"

///.
namespace RedBlue {

struct Specie {
  ///.
  enum Tag {
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
  static const int count = 1 + Mew;
};

struct Move {
  ///.
  enum Tag {
    Absorb,
    Growl,
    Tackle,
    Wrap,
  };
  static const int count = 1 + Wrap;
};

std::ostream& operator<<(std::ostream& os, Move::Tag);

struct PP {
  int cur;
  int max;
  int stage;
};

class CorePkmn;

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

struct Badge {
  ///.
  enum Tag {
    Boulder,
    Cascade,
    Thunder,
    Rainbow,
    Soul,
    Marsh,
    Fire,
    Earth,
  };
  static const int count = 1 + Earth;
};

///.
using Badges = FixedSet<Badge::Tag, Badge::count>;

struct NonVolStatus {
  ///.
  enum Tag {
    Burn,
    Freeze,
    Paralysis,
    Poison,
    None,
    Sleep,
    Toxic,
  };
  static const int count = 1 + Toxic;
};

std::ostream& operator<<(std::ostream&, NonVolStatus::Tag);

struct VolStatus {
  ///.
  enum Tag {
    Confusion,
    Flinch,
    LeechSeed,
    Nightmare,
    PartiallyTrapped,
  };
  static const int count = 1 + PartiallyTrapped;
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

CoreStats operator-(const CoreStats &a);
CoreStats operator+(const CoreStats &a, const CoreStats &b);
CoreStats operator-(const CoreStats &a, const CoreStats &b);

struct ActiveStats {
  int attack;
  int defense;
  int special;
  int speed;
  int evasion;
  int accuracy;
};

class CorePkmn {
public:
  CorePkmn(CoreStats iv, Specie::Tag, int level, MoveSet);
  //
  void Evolve(Specie::Tag);
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
  Specie::Tag GetSpecie() const;
  int GetHP() const;
  int GetExp() const;
  NonVolStatus::Tag GetNonVolStatus() const;
  int GetMoveCount() const;
  Move GetMove(int idx) const;
  const PP& GetPP(int idx) const;
  int GetLevel() const;
  CoreStats GetStats() const;
  bool IsAlive() const;
private:
  Specie::Tag mSpecie;
  int mHP;
  int mExp;
  CoreStats mIV;
  CoreStats mEV;
  NonVolStatus::Tag mNonVolStatus;
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
  //
private:
  CorePkmn& mCorePkmn;
  opt::optional<Specie::Tag> mTransform;
  VolStatuses mVolStatuses;
  ActiveStats mStats;
  ActiveStats mStages;
  //
  void CalcAttack();
  void CalcDefense();
  void CalcSpecial();
  void CalcSpeed();
  void CalcAccuracy();
  void CalcEvasion();
};

struct Player {
  ///.
  enum Tag {
    A,
    B,
  };
  static const int count = 1 + B;
};
  
using ActiveTable = Table<Player, ActivePkmn, Player::count>;
using CoresTable = Table<Player, std::array<CorePkmn, 6>, Player::count>;

class Battle {
public:
  Battle();
  //
  ActivePkmn& GetHotActivePkmn();
  ActivePkmn& GetColdActivePkmn();
  CorePkmn& GetHotCorePkmn();
  CorePkmn& GetColdCorePkmn();
  //
private:
  Player::Tag mHot;
  Player::Tag mCold;
};

CoreStats GetSpecieBaseStats(Specie::Tag) noexcept;
CoreStats MakeIV(int atk, int def, int spc, int spd);

int GetSpecieID(Specie::Tag);
const std::string GetSpecieName(Specie::Tag);
bool CanSpecieEvolveTo(Specie::Tag, int level, Specie::Tag);
int CalcSpecieExp(Specie::Tag, int level);
int GetMoveMaxPP(Move::Tag);
int CalcMoveMaxPP(Move::Tag, int stage);

}

#endif
