#include <stdio.h>

typedef enum {
  BULBASAUR,
  IVYSAUR,
  VENUSAUR,
  CHARMANDER,
  CHARMELEON,
  CHARIZARD,
  SQUIRTLE,
  WARTORTLE,
  BLASTOISE,
  CATERPIE,
  METAPOD,
  BUTTERFREE,
  WEEDLE,
  KAKUNA,
  BEEDRILL,
  PIDGEY,
  PIDGEOTTO,
  PIDGEOT,
  RATTATA,
  RATICATE,
  SPEAROW,
  FEAROW,
  EKANS,
  ARBOK,
  PIKACHU,
  RAICHU,
  SANDSHREW,
  SANDSLASH,
  NIDORANFEMALE,
  NIDORINA,
  NIDOQUEEN,
  NIDORANMALE,
  NIDORINO,
  NIDOKING,
  CLEFAIRY,
  CLEFABLE,
  VULPIX,
  NINETALES,
  JIGGLYPUFF,
  WIGGLYTUFF,
  ZUBAT,
  GOLBAT,
  ODDISH,
  GLOOM,
  VILEPLUME,
  PARAS,
  PARASECT,
  VENONAT,
  VENOMOTH,
  DIGLETT,
  DUGTRIO,
  MEOWTH,
  PERSIAN,
  PSYDUCK,
  GOLDUCK,
  MANKEY,
  PRIMEAPE,
  GROWLITHE,
  ARCANINE,
  POLIWAG,
  POLIWHIRL,
  POLIWRATH,
  ABRA,
  KADABRA,
  ALAKAZAM,
  MACHOP,
  MACHOKE,
  MACHAMP,
  BELLSPROUT,
  WEEPINBELL,
  VICTREEBEL,
  TENTACOOL,
  TENTACRUEL,
  GEODUDE,
  GRAVELER,
  GOLEM,
  PONYTA,
  RAPIDASH,
  SLOWPOKE,
  SLOWBROW,
  MAGNEMITE,
  MAGNETON,
  FARFETCHD,
  DODUO,
  DODRIO,
  SEEL,
  DEWGONG,
  GRIMER,
  MUK,
  SHELLDER,
  CLOYSTER,
  GASTLY,
  HAUNTER,
  GENGAR,
  ONIX,
  DROWZEE,
  HYPNO,
  KRABBY,
  KINGLER,
  VOLTORB,
  ELECTRODE,
  EXEGGCUTE,
  EXEGGUTOR,
  CUBONE,
  MAROWAK,
  HITMONLEE,
  HITMONCHAN,
  LICKITUNG,
  KOFFING,
  WEEZING,
  RHYHORN,
  RHYDON,
  CHANSEY,
  TANGELA,
  KANGASKHAN,
  HORSEA,
  SEADRA,
  GOLDEEN,
  SEAKING,
  STARYU,
  STARMIE,
  MRMIME,
  SCYTHER,
  JYNX,
  ELECTABUZZ,
  MAGMAR,
  PINSIR,
  TAUROS,
  MAGIKARP,
  GYARADOS,
  LAPRAS,
  DITTO,
  EEVEE,
  VAPOREON,
  JOLTEON,
  FLAREON,
  PORYGON,
  OMANYTE,
  OMASTAR,
  KABUTO,
  KABUTOPS,
  AERODACTYL,
  SNORLAX,
  ARTICUNO,
  ZAPDOS,
  MOLTRES,
  DRATINI,
  DRAGONAIR,
  DRAGONITE,
  MEWTWO,
  MEW,
  SPECIE_CNT
} specie_e;

typedef enum {
  PPS_0,
  PPS_1,
  PPS_2,
  PPS_3,
  PPS_4,
  PPS_5,
  PPS_6,
  PPS_CNT
} pps_e; // pps = power point stage

typedef enum {
  ABSORB,
  GROWL,
  TACKLE,
  MOVE_CNT
} move_e;

typedef struct {
  int cur;
  int max;
  pps_e stage;
} pp_s; // pp = power points

#define MAX_MOVES 4

typedef struct {
  move_e move[MAX_MOVES];
  pp_s pp[MAX_MOVES];
  int num;
} moveset_s;

typedef enum {
  BDG_BOULDER,
  BDG_CASCADE,
  BDG_THUNDER,
  BDG_RAINBOW,
  BDG_SOUL,
  BDG_MARSH,
  BDG_FIRE,
  BDG_EARTH,
  BDG_CNT
} bdg_e; // bdg = badge

typedef enum {
  NVS_BURN,
  NVS_FREEZE,
  NVS_PARALYSIS,
  NVS_POISON,
  NVS_SLEEP,
  NVS_TOXIC,
  NVS_CNT
} nvs_e; // non volatile status

typedef struct {
  int confusion;
  int flinch;
  int leech_seed;
  int nightmare;
  int partially_trapped;
} vs_s; // volatile status

typedef struct {
  int hp;
  int atk;
  int def;
  int spc;
  int spd;
} stats_s;

typedef struct {
  int atk;
  int def;
  int spc;
  int spd;
  int eva;
  int acc;
} battle_mod_s;

typedef struct {
  specie_e specie;
  int hp;
  int exp;
  stats_s iv;
  stats_s ev;
  nvs_e nvs;
  int lvl;
  stats_s stats;
  moveset_s moveset;
} pkmn_s;

typedef struct {
  specie_e transform;
  vs_s vs;
  battle_mod_s stats;
  battle_mod_s stages;
} battle_pkmn_mod_s;

int main() {
  return 0;
}
