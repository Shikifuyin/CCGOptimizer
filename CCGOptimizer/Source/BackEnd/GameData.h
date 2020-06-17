/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/GameData.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
/////////////////////////////////////////////////////////////////////////////////
// Description : Game-Specific Data
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : Requires more investigation ...
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Header prelude
#ifndef CCGOP_BACKEND_GAMEDATA_H
#define CCGOP_BACKEND_GAMEDATA_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/System/System.h"

#include "Lib/Datastruct/Array/Array.h"
#include "Lib/Datastruct/Map/TreeMap.h"

#include "Lib/File/XML/XML.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions
#define GameDataFn GameData::GetInstance()

#define GAMEDATA_FILE_RUNES TEXT("XML/GameData_Runes.xml")
#define GAMEDATA_FILE_HEROES TEXT("XML/GameData_Heroes.xml")

#define GAMEDATA_NAMES_MAX_LENGTH 128

    // Runes
#define RUNE_SLOT_COUNT         6
#define RUNE_RANDOM_STAT_COUNT  4
#define RUNE_MAX_LEVEL          15

enum RuneSet {
    RUNE_SET_BLESSING = 0,
    RUNE_SET_ATTACK,
    RUNE_SET_DEFENSE,
    RUNE_SET_AGILE,
    RUNE_SET_WILD,
    RUNE_SET_DESTRUCTION,
    RUNE_SET_FOCUS,
    RUNE_SET_STALWART,
    RUNE_SET_DESPERATION,
    RUNE_SET_DRAIN,
    RUNE_SET_FRENZY,
    RUNE_SET_BERSERK,
    RUNE_SET_COUNTER,
    RUNE_SET_GUARD,
    RUNE_SET_IMMUNITY,
    RUNE_SET_RAVAGE,
    RUNE_SET_PRAYER,
    RUNE_SET_CONFLICT,
    RUNE_SET_UNITY,
    RUNE_SET_HIT,
    RUNE_SET_FORTITUDE,
    RUNE_SET_COUNT
};

enum RuneRank {
    RUNE_RANK_1S = 0,
    RUNE_RANK_2S,
    RUNE_RANK_3S,
    RUNE_RANK_4S,
    RUNE_RANK_5S,
    RUNE_RANK_6S,
    RUNE_RANK_COUNT
};

enum RuneQuality {
    RUNE_QUALITY_COMMON = 0, // White
    RUNE_QUALITY_MAGIC,      // Green
    RUNE_QUALITY_RARE,       // Blue
    RUNE_QUALITY_HEROIC,     // Purple
    RUNE_QUALITY_LEGENDARY,  // Red
    RUNE_QUALITY_COUNT
};

enum RuneStat {
    RUNE_STAT_HP_FLAT = 0,
    RUNE_STAT_HP_PERCENT,
    RUNE_STAT_ATTACK_FLAT,
    RUNE_STAT_ATTACK_PERCENT,
    RUNE_STAT_DEFENSE_FLAT,
    RUNE_STAT_DEFENSE_PERCENT,
    RUNE_STAT_SPEED,
    RUNE_STAT_CRIT_RATE,
    RUNE_STAT_CRIT_DMG,
    RUNE_STAT_HIT,
    RUNE_STAT_RESISTANCE,
    RUNE_STAT_COUNT
};

    // Heroes
#define HERO_MAX_LEVEL 40

enum HeroFaction {
    HERO_FACTION_LAWFUL = 0,
    HERO_FACTION_CHAOTIC,
    HERO_FACTION_EVIL,
    HERO_FACTION_LIGHT,
    HERO_FACTION_DARK,
    HERO_FACTION_COUNT
};

enum HeroRank {
    HERO_RANK_1S = 0,
    HERO_RANK_2S,
    HERO_RANK_3S,
    HERO_RANK_4S,
    HERO_RANK_5S,
    HERO_RANK_6S,
    HERO_RANK_COUNT
};

enum HeroStat {
    HERO_STAT_HP = 0,
    HERO_STAT_ATTACK,
    HERO_STAT_DEFENSE,
    HERO_STAT_SPEED,
    HERO_STAT_CRIT_RATE,
    HERO_STAT_CRIT_DMG,
    HERO_STAT_HIT,
    HERO_STAT_RESISTANCE,
    HERO_STAT_COUNT
};

enum HeroSanctify {
    HERO_SANCTIFY_NONE = 0,
    HERO_SANCTIFY_HP,
    HERO_SANCTIFY_ATT,
    HERO_SANCTIFY_DEF,
    HERO_SANCTIFY_HIT,
    HERO_SANCTIFY_RES,
    HERO_SANCTIFY_COUNT
};

typedef struct _hero_data {
    GChar strName[GAMEDATA_NAMES_MAX_LENGTH];
    HeroFaction iFaction;
    HeroRank iNaturalRank;
    UInt arrBaseStats[HERO_STAT_COUNT * HERO_RANK_COUNT * HERO_MAX_LEVEL];
    UInt arrBaseStatsEvolved[HERO_STAT_COUNT * HERO_RANK_COUNT * HERO_MAX_LEVEL];
} HeroData;

/////////////////////////////////////////////////////////////////////////////////
// The GameData class
class GameData
{
    // Discrete singleton interface
public:
    inline static GameData * GetInstance();

private:
    GameData();
    ~GameData();

public:
    // Import (No Export Needed)
    Void ImportFromXML();

    // Constant Names
    inline const GChar * GetRuneStatName( RuneStat iRuneStat ) const;
    inline const GChar * GetHeroStatName( HeroStat iHeroStat ) const;

    // Rune Data
    inline UInt GetRuneSetSize( RuneSet iRuneSet ) const;

    inline Bool IsRuneMainStatAllowed( RuneStat iRuneStat, UInt iSlot ) const;
    inline UInt GetRuneMainStatValue( RuneStat iRuneStat, RuneRank iRank, UInt iLevel ) const;

    inline UInt GetRuneStatMinRoll( RuneStat iRuneStat, RuneRank iRank ) const;
    inline UInt GetRuneStatMaxRoll( RuneStat iRuneStat, RuneRank iRank ) const;
    
    // Hero Data
    inline UInt GetHeroRankMaxLevel( HeroRank iRank ) const;
    inline UInt GetHeroSanctifyBonus( HeroSanctify iSanctify ) const;

    inline Bool IsHeroNameValid( const GChar * strHeroName ) const;
    inline HeroFaction GetHeroFaction( const GChar * strHeroName ) const;
    inline HeroRank GetHeroNaturalRank( const GChar * strHeroName ) const;
    inline UInt GetHeroBaseStat( const GChar * strHeroName, HeroStat iHeroStat, HeroRank iRank, UInt iLevel, Bool bEvolved ) const;

private:
    // Rune Data
    UInt m_arrRuneSetSizes[RUNE_SET_COUNT];
    Bool m_arrRuneMainStatsAllowed[RUNE_STAT_COUNT * RUNE_SLOT_COUNT];
    UInt m_arrRuneMainStatsValues[RUNE_STAT_COUNT * RUNE_RANK_COUNT * RUNE_MAX_LEVEL];
    UInt m_arrRuneSubStatsMinRoll[RUNE_STAT_COUNT * RUNE_RANK_COUNT];
    UInt m_arrRuneSubStatsMaxRoll[RUNE_STAT_COUNT * RUNE_RANK_COUNT];

    // Hero Data
    UInt m_arrHeroRankMaxLevel[HERO_RANK_COUNT];
    UInt m_arrHeroSanctifyBonus[HERO_SANCTIFY_COUNT];

    typedef TreeMap<const GChar *, HeroData> HeroDataMap;
    HeroDataMap m_mapHeroData;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GameData.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_GAMEDATA_H
