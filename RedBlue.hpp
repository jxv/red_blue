#ifndef RedBlue_hpp
#define RedBlue_hpp

#include <iostream>
#include <cassert>
#include <tuple>
#include "Util.hpp"

namespace RedBlue {

struct Specie {
  enum Tag {
    bulbasaur,
    ivysaur,
    venusaur,
    charmander,
    charmeleon,
    charizard,
    squirtle,
    wartortle,
    blastoise,
    caterpie,
    metapod,
    butterfree,
    weedle,
    kakuna,
    beedrill,
    pidgey,
    pidgeotto,
    pidgeot,
    rattata,
    raticate,
    spearow,
    fearow,
    ekans,
    arbok,
    pikachu,
    raichu,
    sandshrew,
    sandslash,
    nidoran_female,
    nidorina,
    nidoqueen,
    nidoran_male,
    nidorino,
    nidoking,
    clefairy,
    clefable,
    vulpix,
    ninetales,
    jigglypuff,
    wigglytuff,
    zubat,
    golbat,
    oddish,
    gloom,
    vileplume,
    paras,
    parasect,
    venonat,
    venomoth,
    diglett,
    dugtrio,
    meowth,
    persian,
    psyduck,
    golduck,
    mankey,
    primeape,
    growlithe,
    arcanine,
    poliwag,
    poliwhirl,
    poliwrath,
    abra,
    kadabra,
    alakazam,
    machop,
    machoke,
    machamp,
    bellsprout,
    weepinbell,
    victreebel,
    tentacool,
    tentacruel,
    geodude,
    graveler,
    golem,
    ponyta,
    rapidash,
    slowpoke,
    slowbrow,
    magnemite,
    magneton,
    farfetch_d,
    doduo,
    dodrio,
    seel,
    dewgong,
    grimer,
    muk,
    shellder,
    cloyster,
    gastly,
    haunter,
    gengar,
    onix,
    drowzee,
    hypno,
    krabby,
    kingler,
    voltorb,
    electrode,
    exeggcute,
    exeggutor,
    cubone,
    marowak,
    hitmonlee,
    hitmonchan,
    lickitung,
    koffing,
    weezing,
    rhyhorn,
    rhydon,
    chansey,
    tangela,
    kangaskhan,
    horsea,
    seadra,
    goldeen,
    seaking,
    staryu,
    starmie,
    mr_Mime,
    scyther,
    jynx,
    electabuzz,
    magmar,
    pinsir,
    tauros,
    magikarp,
    gyarados,
    lapras,
    ditto,
    eevee,
    vaporeon,
    jolteon,
    flareon,
    porygon,
    omanyte,
    omastar,
    kabuto,
    kabutops,
    aerodactyl,
    snorlax,
    articuno,
    zapdos,
    moltres,
    dratini,
    dragonair,
    dragonite,
    mewtwo,
    mew,
  };
  static const int count = 1 + mew;
};

struct Move {
  enum Tag {
    absorb,
    growl,
    tackle,
    wrap,
  };
  static const int count = 1 + wrap;
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
  MoveSet(Move::Tag, int stage0 = 0);
  MoveSet(Move::Tag, Move::Tag, int stage0 = 0, int stage1 = 0);
  MoveSet(Move::Tag, Move::Tag, Move::Tag, int stage0 = 0, int stage1 = 0, int stage2 = 0);
  MoveSet(Move::Tag, Move::Tag, Move::Tag, Move::Tag, int stage0 = 0, int stage1 = 0, int stage2 = 0, int stage3 = 0);
private: 
  std::array<Move::Tag, 4> moves;
  std::array<PP, 4> pps;
  int move_count;
  //
  void init_pps();
  //
  friend class CorePkmn;
};

struct Badge {
  enum Tag {
    boulder,
    cascade,
    thunder,
    rainbow,
    soul,
    marsh,
    fire,
    earth,
  };
  static const int count = 1 + earth;
};

using Badges = FixedSet<Badge::Tag, Badge::count>;

struct NonVolStatus {
  enum Tag {
    burn,
    freeze,
    paralysis,
    poison,
    none,
    sleep,
    toxic,
  };
  static const int count = 1 + toxic;
};

std::ostream& operator<<(std::ostream&, NonVolStatus::Tag);

struct VolStatus {
  enum Tag {
    confusion,
    flinch,
    leech_seed,
    nightmare,
    partially_trapped,
  };
  static const int count = 1 + partially_trapped;
};

struct VolStatuses {
  int confusion;
  int flinch;
  int leech_seed;
  int nightmare;
  int partially_trapped;
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
  void evolve(Specie::Tag);
  void restore_hp();
  void restore_hp(int hp);
  void damage_hp(int hp);
  void add_exp(int exp);
  void add_ev(CoreStats);
  void burn();
  void freeze();
  void paralyze();
  void poison();
  void sleep();
  void intoxicate();
  void restore_nonvolstatus();
  void swap_move(int idx0, int idx1);
  void learn_move(Move::Tag, int idx);
  void use_pp(int idx);
  void restore_pp();
  void restore_pp(int idx);
  void restore_pp(int idx, int val);
  void increment_pp_stage(int idx);
  //
  Specie::Tag get_specie() const;
  int get_hp() const;
  int get_exp() const;
  NonVolStatus::Tag get_nonvolstatus() const;
  int get_move_count() const;
  Move::Tag get_move(int idx) const;
  const PP& get_pp(int idx) const;
  int get_level() const;
  CoreStats get_stats() const;
  bool is_alive() const;
private:
  Specie::Tag specie;
  int hp;
  int exp;
  CoreStats iv;
  CoreStats ev;
  NonVolStatus::Tag nonvolstatus;
  int move_count;
  std::array<Move::Tag, 4> moves;
  std::array<PP, 4> pps;
  int level;
  CoreStats stats;
  //
  void update_level();
  void update_stats();
  //
  friend std::ostream& operator<<(std::ostream&, const CorePkmn&);
};

std::ostream& operator<<(std::ostream&, const CorePkmn&);

struct ActivePkmn {
public:
  const ActiveStats& get_stats() const;
  //
private:
  CorePkmn& corepkmn;
  opt::optional<Specie::Tag> transform;
  VolStatuses volstatuses;
  ActiveStats stats;
  ActiveStats stages;
  //
  void update_attack();
  void update_defense();
  void update_special();
  void update_speed();
  void update_accuracy();
  void update_evasion();
};

struct Player {
  enum Tag {
    a,
    b,
  };
  static const int count = 1 + b;
};
  
using ActiveTable = Table<Player, ActivePkmn, Player::count>;
using CoresTable = Table<Player, std::array<CorePkmn, 6>, Player::count>;

class Battle {
public:
  Battle();
  //
  ActivePkmn& get_hot_activepkmn();
  ActivePkmn& get_cold_activepkmn();
  CorePkmn& get_hot_corepkmn();
  CorePkmn& get_cold_corepkmn();
  //
private:
  Player::Tag hot;
  Player::Tag cold;
};

CoreStats get_specie_base_stats(Specie::Tag) noexcept;
CoreStats make_iv(int atk, int def, int spc, int spd);

int get_specie_id(Specie::Tag);
const std::string get_specie_name(Specie::Tag);
bool can_specie_evolve_to(Specie::Tag, int level, Specie::Tag);
int calc_specie_exp(Specie::Tag, int level);
int get_move_max_pp(Move::Tag);
int calc_move_max_pp(Move::Tag, int stage);

}

#endif
