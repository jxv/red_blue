#ifndef RedBlue_h
#define RedBlue_h

#include <iostream>
#include <cassert>
#include <tuple>
#include <experimental/optional>
#include "Util.h"

namespace RedBlue {

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

int GetSpecieID(Specie);

enum class Move {
  Absorb,
  Growl,
  Tackle,
  Wrap,
};

std::ostream& operator<<(std::ostream& os, Move);

enum class PowerPointStage {
  Zero,
  One,
  Two,
  Three,
  Four,
  Five,
  Six,
};

std::ostream& operator<<(std::ostream&, PowerPointStage);

class PowerPoints {
  int current;
  int maximum;
  PowerPointStage stage;
public:
  PowerPoints();
  PowerPoints(Move);
  int GetCurrent() const;
  int GetMaximum() const;
  PowerPointStage GetStage() const;
  void Use();
  void RestoreFull();
  void Restore(int points);
  void IncrementStage();
};

class Pokemon; 
class MoveSet {
  std::array<Move, 4> moves;
  std::array<PowerPoints, 4> powerPointSet;
  int moveCount;
public:
  MoveSet();
  MoveSet(Move,
    PowerPointStage stage0 = PowerPointStage::Zero);
  MoveSet(Move, Move,
    PowerPointStage stage0 = PowerPointStage::Zero,
    PowerPointStage stage1 = PowerPointStage::Zero);
  MoveSet(Move, Move, Move,
    PowerPointStage stage0 = PowerPointStage::Zero,
    PowerPointStage stage1 = PowerPointStage::Zero,
    PowerPointStage stage2 = PowerPointStage::Zero);
  MoveSet(Move, Move, Move, Move,
    PowerPointStage stage0 = PowerPointStage::Zero,
    PowerPointStage stage1 = PowerPointStage::Zero,
    PowerPointStage stage2 = PowerPointStage::Zero,
    PowerPointStage stage3 = PowerPointStage::Zero);
private:
  void InitPowerPointsSet();
  friend class Pokemon;
};

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

struct VolStatuses {
  int confusion;
  int flinch;
  int leechSeed;
  int nightmare;
  int partiallyTrapped;
};

struct CoreStats {
  int healthPoints;
  int attack;
  int defense;
  int special;
  int speed;
};

CoreStats operator-(const CoreStats &a);
CoreStats operator+(const CoreStats &a, const CoreStats &b);
CoreStats operator-(const CoreStats &a, const CoreStats &b);

enum ActiveStage {
  MinusSix,
  MinusFive,
  MinusFour,
  MinusThree,
  MinusTwo,
  MinusOne,
  Zero,
  PlusOne,
  PlusTwo,
  PlusThree,
  PlusFour,
  PlusFive,
  PlusSix,
};

template <typename T>
struct Active {
  T attack;
  T defense;
  T special;
  T speed;
  T evasion;
  T accuracy;
};

using ActiveStats = Active<int>;
using ActiveStages = Active<ActiveStage>;

class Pokemon {
  Specie specie;
  int healthPoints;
  int experience;
  CoreStats individualValues;
  CoreStats effortValues;
  NonVolStatus nonVolStatus;
  int moveCount;
  std::array<Move, 4> moves;
  std::array<PowerPoints, 4> powerPointSet;
  int level;
  CoreStats stats;
public:
  Pokemon(CoreStats iv, Specie, int level, MoveSet);
  Specie GetSpecie() const;
  int GetHealthPoints() const;
  int GetExperience() const;
  NonVolStatus GetNonVolStatus() const;
  int GetMoveCount() const;
  Move GetMove(int idx) const;
  const PowerPoints& GetPowerPoints(int idx) const;
  int GetLevel() const;
  CoreStats GetStats() const;
  bool IsAlive() const;
  void Evolve(Specie);
  void RestoreHealthPoints();
  void RestoreHealthPoints(int hp);
  void DamageHealthPoints(int hp);
  void AddExperience(int exp);
  void AddEffortValues(CoreStats);
  void Burn();
  void Freeze();
  void Paralyze();
  void Poison();
  void Sleep();
  void Intoxicate();
  void RestoreNonVolStatus();
  void SwapMove(int idx0, int idx1);
  void LearnMove(Move, int idx);
  void UsePowerPoint(int idx);
  void RestorePowerPoints();
  void RestorePowerPoints(int idx);
  void RestorePowerPoints(int idx, int addition);
  void IncrementPowerPointsStage(int idx);
private:
  void UpdateLevel();
  void UpdateStats();
  friend std::ostream& operator<<(std::ostream&, const Pokemon&);
};

std::ostream& operator<<(std::ostream&, const Pokemon&);

class Battlemon {
  std::experimental::optional<Specie> transform;
  VolStatuses volStatuses;
  ActiveStats stats;
  ActiveStages stages;
public:
  Battlemon(const Pokemon&);
  Specie GetSpecie(const Pokemon&) const;
  const VolStatuses& GetVolStatuses() const;
  const ActiveStats& GetStats() const;
  const ActiveStages& GetStages() const;
private:
  void UpdateStats(const Pokemon&);
  void UpdateAttack(const Pokemon&);
  void UpdateDefense(const Pokemon&);
  void UpdateSpecial(const Pokemon&);
  void UpdateSpeed(const Pokemon&);
  void UpdateAccuracy(const Pokemon&);
  void UpdateEvasion(const Pokemon&);
};

enum class Player {
  A,
  B,
};

enum class Seat {
  Hot,
  Cold,
};

enum class Instruction {
  AddHealthPoints,
  SubHealthPoints,
};

struct BattleInstruction {
  Instruction instruction;
  union {
  };
};

enum class Action {
  SwitchOut,
  Faint,
};

struct BattleAction {
  Action action;
  union {
    struct { } switchOut;
  };
};
  
class Battle {
  Player hot;
  Player cold;
  BattleAction battleAction;
public:
  Battle();
  Battlemon& GetHotBattlemon() const;
  Battlemon& GetColdBattlemon() const;
  Pokemon& GetHotPokemon() const;
  Pokemon& GetColdPokemon() const;
  const BattleAction& GetBattleAction() const;
  bool Step();
};

CoreStats GetSpecieBaseStats(Specie) noexcept;
CoreStats MakeIndividualValues(int atk, int def, int spc, int spd);

const std::string GetSpecieName(Specie);
bool CanSpecieEvolveTo(Specie, int level, Specie);
int CalculateSpecieExperience(Specie, int level);
int GetMoveMaximumPowerPoints(Move);
int CalculateMoveMaximumPowerPoints(Move, PowerPointStage);

}

#endif
