/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/HeroInventory.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Hero Inventory Manager
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Header prelude
#ifndef CCGOP_BACKEND_HEROINVENTORY_H
#define CCGOP_BACKEND_HEROINVENTORY_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "Rune.h"
#include "Hero.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Search Queries
enum HeroQuery {
    HERO_QUERY_NAME = 0,
    HERO_QUERY_FACTION,
    HERO_QUERY_RANK,
    HERO_QUERY_LEVEL,
    HERO_QUERY_EVOLVED,
    HERO_QUERY_GEARSET,
    HERO_QUERY_RUNES
};

typedef union _hero_query_parameter {
    // HERO_QUERY_NAME
    struct _query_name {
        GChar strName[GAMEDATA_NAMES_MAX_LENGTH];
    } hQueryName;

    // HERO_QUERY_FACTION
    struct _query_faction {
        HeroFaction iFaction;
    } hQueryFaction;

    // HERO_QUERY_RANK
    struct _query_rank {
        HeroRank iRank;
    } hQueryRank;

    // HERO_QUERY_LEVEL
    struct _query_level {
        UInt iLevel;
    } hQueryLevel;

    // HERO_QUERY_EVOLVED
    struct _query_evolved {
        Bool bEvolved;
    } hQueryEvolved;

    // HERO_QUERY_GEARSET
    struct _query_gearset {
        GearSetID iGearSetID;
    } hQueryGearSet;

    // HERO_QUERY_RUNES
    struct _query_runes {
        Bool bAndElseOr;
        UInt iRuneCount;
        RuneID arrRunes[32];
    } hQueryRunes;
} HeroQueryParameter;

typedef TreeMap<HeroQuery,HeroQueryParameter> HeroQueryMap;

// Prototypes
class CCGOPManager;

/////////////////////////////////////////////////////////////////////////////////
// The HeroInventory class
class HeroInventory
{
public:
    HeroInventory();
    ~HeroInventory();

    // Import/Export
    Void ImportFromXML( XMLNode * pNode );
    Void ExportToXML( XMLNode * pNode ) const;

    // Hero Inventory
    inline UInt GetHeroCount() const;
    inline const Hero * GetHero( HeroID iHeroID ) const;
    inline Hero * GetHero( HeroID iHeroID );

    // Selected GearSets
    inline Void UnselectAllGearSets();
    
    // Search Engine
    Void FilterSearch( Array<HeroID> * outResults, const HeroQueryMap & mapQueries ) const;

private:
    // Internals
    friend class CCGOPManager;

    inline HeroID _CreateHero( const GChar * strName, HeroRank iRank, UInt iLevel, Bool bEvolved, HeroSanctify iSanctify );
    inline Void _DestroyHero( HeroID iHeroID );
    inline Void _DestroyAllHeroes();

    inline Void _DetachAll();

    // Helpers
    inline HeroID _AllocateHeroID();

    // Members
    HeroID m_iNextFreeHeroID;

    typedef TreeMap<HeroID, Hero> HeroMap;
    HeroMap m_mapHeroInventory;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "HeroInventory.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_HEROINVENTORY_H


    // Sorting Rules
//define( "HERO_SORTING_ID",          "_HeroComparator_ID" );
//define( "HERO_SORTING_NAME",        "_HeroComparator_Name" );
//define( "HERO_SORTING_FACTION",     "_HeroComparator_Faction" );
//define( "HERO_SORTING_LEVEL",       "_HeroComparator_Level" );
//define( "HERO_SORTING_EVOLVED",     "_HeroComparator_Evolved" );
//define( "HERO_SORTING_HP",          "_HeroComparator_HP" );
//define( "HERO_SORTING_ATT",         "_HeroComparator_ATT" );
//define( "HERO_SORTING_DEF",         "_HeroComparator_DEF" );
//define( "HERO_SORTING_SPD",         "_HeroComparator_SPD" );
//define( "HERO_SORTING_CRITRATE",    "_HeroComparator_CritRate" );
//define( "HERO_SORTING_CRITDMG",     "_HeroComparator_CritDmg" );
//define( "HERO_SORTING_HIT",         "_HeroComparator_Hit" );
//define( "HERO_SORTING_RES",         "_HeroComparator_Res" );
//define( "HERO_SORTING_GEARSET",     "_HeroComparator_GearSet" );

// Sorted View
//public function GetHeroViewEntry( int $iIndex ):int {
//    assert( $iIndex < count($this->m_arrSortedView) );
//    return $this->m_arrSortedView[$iIndex];
//}
//
//public function SortHeroView( $strSortingRule ):void
//{
//    $this->m_arrSortedView = array();
//    $hHeap = new Heap( "HeroInventory::$strSortingRule", $this );
//    foreach( $this->m_arrHeroInventory as &$hHero ) {
//        $hHeap->Merge( $hHero->GetID() );
//    }
//    while( !$hHeap->IsEmpty() ) {
//        $iHeroID = NULL;
//        $hHeap->Extract( $iHeroID );
//        array_push( $this->m_arrSortedView, $iHeroID );
//    }
//}


//
//public static function _HeroComparator_ID( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    if ( $iLeftHeroID < $iRightHeroID )
//        return +1;
//    if ( $iLeftHeroID > $iRightHeroID )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_Name( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    return -( strcasecmp($hLeftHero->GetName(), $hRightHero->GetName()) );
//}
//public static function _HeroComparator_Faction( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hLeftHero->GetFaction();
//    $iRight = $hRightHero->GetFaction();
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_Level( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hLeftHero->GetLevel();
//    $iRight = $hRightHero->GetLevel();
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_Evolved( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hLeftHero->IsEvolved() ? 1 : 0;
//    $iRight = $hRightHero->IsEvolved() ? 1 : 0;
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_HP( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hGameData = &GameData::GetSingleton();
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_HP, $hLeftHero->IsEvolved() );
//    $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_HP, $hRightHero->IsEvolved() );
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_ATT( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hGameData = &GameData::GetSingleton();
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_ATTACK, $hLeftHero->IsEvolved() );
//    $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_ATTACK, $hRightHero->IsEvolved() );
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_DEF( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hGameData = &GameData::GetSingleton();
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_DEFENSE, $hLeftHero->IsEvolved() );
//    $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_DEFENSE, $hRightHero->IsEvolved() );
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_SPD( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hGameData = &GameData::GetSingleton();
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_SPEED, $hLeftHero->IsEvolved() );
//    $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_SPEED, $hRightHero->IsEvolved() );
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_CritRate( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hGameData = &GameData::GetSingleton();
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_CRIT_RATE, $hLeftHero->IsEvolved() );
//    $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_CRIT_RATE, $hRightHero->IsEvolved() );
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_CritDmg( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hGameData = &GameData::GetSingleton();
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_CRIT_DMG, $hLeftHero->IsEvolved() );
//    $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_CRIT_DMG, $hRightHero->IsEvolved() );
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_Hit( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hGameData = &GameData::GetSingleton();
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_HIT, $hLeftHero->IsEvolved() );
//    $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_HIT, $hRightHero->IsEvolved() );
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_Res( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hGameData = &GameData::GetSingleton();
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_RESISTANCE, $hLeftHero->IsEvolved() );
//    $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_RESISTANCE, $hRightHero->IsEvolved() );
//    if ( $iLeft < $iRight )
//        return +1;
//    if ( $iLeft > $iRight )
//        return -1;
//    return 0;
//}
//public static function _HeroComparator_GearSet( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
//    $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
//    $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
//    return -( strcasecmp($hLeftHero->GetSelectedGearSet(), $hRightHero->GetSelectedGearSet()) );
//}
//
