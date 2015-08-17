#ifndef RED_BLUE_H
#define RED_BLUE_H

#include <iostream>
#include <cassert>
#include <tuple>
#include <experimental/optional>
#include "red_blue/util.h"

namespace red_blue {

struct CoreStats;

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

int get_id(Specie);
const std::string get_name(Specie);
CoreStats get_base_stats(Specie);
bool can_evolve_to(Specie, int level, Specie);
int get_experience_by_level(Specie, int level);
std::ostream& operator<<(std::ostream& os, Specie);

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

enum class Move {
  Absorb,
  Growl,
  Tackle,
  Wrap,
};

int get_maximum_power_points(Move);
int get_maximum_power_points(Move, PowerPointStage);
std::ostream& operator<<(std::ostream& os, Move);

class PowerPoints {
  int current;
  int maximum;
  PowerPointStage stage;
public:
  PowerPoints();
  PowerPoints(Move);
  int get_current() const;
  int get_maximum() const;
  PowerPointStage get_stage() const;
  void use();
  void restore_full();
  void restore(int points);
  void increment_stage();
};

class Pokemon; 

class MoveSet {
  std::array<Move, 4> moves;
  std::array<PowerPoints, 4> power_point_set;
  int size;
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
  int get_size() const;
  Move get_move(int idx) const;
  const PowerPoints& get_power_points(int idx) const;
  void swap(int idx0, int idx1);
  void learn(Move, int idx);
  void use(int idx);
  void restore();
  void restore(int idx);
  void restore(int idx, int addition);
  void increment_stage(int idx);
private:
  void init_power_point_set();
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
  int leech_seed;
  int nightmare;
  int partially_trapped;
};

struct CoreStats {
  int health_points;
  int attack;
  int defense;
  int special;
  int speed;
};

CoreStats make_individual_values(int atk, int def, int spc, int spd);

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
  int health_points;
  int experience;
  CoreStats individual_values;
  CoreStats effort_values;
  NonVolStatus non_vol_status;
  int level;
  CoreStats stats;
public:
  MoveSet move_set;
public:
  Pokemon(CoreStats iv, Specie, int level, MoveSet);
  Specie get_specie() const;
  int get_health_points() const;
  int get_experience() const;
  NonVolStatus get_non_vol_status() const;
  int get_level() const;
  const CoreStats& get_stats() const;
  bool is_alive() const;
  void evolve(Specie);
  void restore_health_points();
  void restore_health_points(int hp);
  void damage_health_points(int hp);
  void add_experience(int exp);
  void add_effort_values(CoreStats);
  void burn();
  void freeze();
  void paralyze();
  void poison();
  void sleep();
  void intoxicate();
  void restore_non_vol_status();
private:
  void sync_level();
  void update_stats();
  friend std::ostream& operator<<(std::ostream&, const Pokemon&);
};

std::ostream& operator<<(std::ostream&, const Pokemon&);

class Battlemon {
  std::experimental::optional<Specie> transform;
  VolStatuses vol_statuses;
  ActiveStats stats;
  ActiveStages stages;
public:
  Battlemon(const Pokemon&);
  Specie get_specie(const Pokemon&) const;
  const VolStatuses& get_vol_statuses() const;
  const ActiveStats& get_stats() const;
  const ActiveStages& get_stages() const;
private:
  void update_stats(const Pokemon&);
  void update_attack(const Pokemon&);
  void update_defense(const Pokemon&);
  void update_special(const Pokemon&);
  void update_speed(const Pokemon&);
  void update_accuracy(const Pokemon&);
  void update_evasion(const Pokemon&);
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
    struct { 
    } switch_out;
  };
};
  
class Battle {
  Player hot;
  Player cold;
  BattleAction battle_action;
public:
  Battle();
  Battlemon& get_hot_battlemon() const;
  Battlemon& get_cold_battlemon() const;
  Pokemon& get_hot_pokemon() const;
  Pokemon& get_cold_pokemon() const;
  const BattleAction& get_battle_action() const;
  bool Step();
};


}

#endif
