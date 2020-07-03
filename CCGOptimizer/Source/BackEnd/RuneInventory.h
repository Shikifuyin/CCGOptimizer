/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/RuneInventory.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Inventory Manager
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
#ifndef CCGOP_BACKEND_RUNEINVENTORY_H
#define CCGOP_BACKEND_RUNEINVENTORY_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "Rune.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Search Queries
enum RuneQuery {
    RUNE_QUERY_SLOT = 0,
    RUNE_QUERY_SET,
    RUNE_QUERY_RANK,
    RUNE_QUERY_QUALITY,
    RUNE_QUERY_LEVEL,
    RUNE_QUERY_MAINSTAT,
    RUNE_QUERY_SUBSTATS,
    RUNE_QUERY_EFFICIENCY,
    RUNE_QUERY_DAMAGE,
    RUNE_QUERY_TANKING
};

typedef union _rune_query_parameter {
    // RUNE_QUERY_SLOT
    struct _query_slot {
        UInt iSlotCount;
        UInt arrSlots[RUNE_SLOT_COUNT];
    } hQuerySlot;

    // RUNE_QUERY_SET
    struct _query_set {
        UInt iSetCount;
        RuneSet arrSets[RUNE_SET_COUNT];
    } hQuerySet;

    // RUNE_QUERY_RANK
    struct _query_rank {
        UInt iRankCount;
        RuneRank arrRanks[RUNE_RANK_COUNT];
    } hQueryRank;

    // RUNE_QUERY_QUALITY
    struct _query_quality {
        UInt iQualityCount;
        RuneQuality arrQualities[RUNE_QUALITY_COUNT];
    } hQueryQuality;

    // RUNE_QUERY_LEVEL
    struct _query_level {
        UInt iLevelCount;
        UInt arrLevels[RUNE_MAX_LEVEL+1];
    } hQueryLevel;

    // RUNE_QUERY_MAINSTAT
    struct _query_mainstat {
        UInt iStatCount;
        RuneStat arrStats[RUNE_STAT_COUNT];
    } hQueryMainStat;

    // RUNE_QUERY_SUBSTATS
    struct _query_substats {
        Bool bAndElseOr;
        UInt iStatCount;
        RuneStat arrStats[RUNE_STAT_COUNT];
        UInt arrStatValues[RUNE_STAT_COUNT];
    } hQuerySubStats;

    // RUNE_QUERY_EFFICIENCY
    struct _query_efficiency {
        Float fThreshold;
    } hQueryEfficiency;

    // RUNE_QUERY_DAMAGE
    struct _query_damage {
        Float fThreshold;
    } hQueryDamage;

    // RUNE_QUERY_TANKING
    struct _query_tanking {
        Float fThreshold;
    } hQueryTanking;
} RuneQueryParameter;

Int RuneQueryMap_Compare( const RuneQuery & rLeft, const RuneQuery & rRight, Void * pUserData );
typedef TreeMap<RuneQuery,RuneQueryParameter> RuneQueryMap;

// Prototypes
class CCGOPManager;

/////////////////////////////////////////////////////////////////////////////////
// The RuneInventory class
class RuneInventory
{
public:
    typedef TreeMap<RuneID, Rune> RuneMap;

    RuneInventory();
    ~RuneInventory();

    // Import/Export
    Void ImportFromXML( XMLNode * pNode );
    Void ExportToXML( XMLNode * pNode ) const;

    // Rune Inventory
    inline UInt GetRuneCount() const;
    inline const Rune * GetRune( RuneID iRuneID ) const;
    inline Rune * GetRune( RuneID iRuneID );

    // Rune Locks
    inline Void LockAll();
    inline Void UnlockAll();

    // Search Engine
    Void FilterSearch( Array<RuneID> * outResults, const RuneQueryMap & mapQueries, const Array<RuneID> * arrExcluded, Bool bAllowLocked, Bool bAllowEquipped ) const;

private:
    // Internals
    friend class CCGOPManager;

    inline RuneID _CreateRune( UInt iSlot, RuneSet iSet, RuneRank iRank, RuneQuality iQuality, UInt iLevel,
                               RuneStat iMainStat, RuneStat iInnateStat, UInt iInnateStatValue,
                               UInt iRandomStatCount, const RuneStat * arrRandomStats, const UInt * arrRandomStatValues );
    inline Void _DestroyRune( RuneID iRuneID );
    inline Void _DestroyAllRunes();

    inline Void _UnequipAll();

    // Helpers
    inline RuneID _AllocateRuneID();

    // Members
    RuneID m_iNextFreeRuneID;

    static Int _Compare_RuneID( const RuneID & rLeft, const RuneID & rRight, Void * pUserData );
    RuneMap m_mapRuneInventory;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneInventory.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_RUNEINVENTORY_H

