/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Rune.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Representation
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Header prelude
#ifndef CCGOP_BACKEND_RUNE_H
#define CCGOP_BACKEND_RUNE_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "GameData.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Rune IDs
typedef UInt RuneID;

// GearSet ID
#ifndef GearSetID
    typedef UInt GearSetID;
#endif // GearSetID

// Prototypes
class CCGOPManager;
class RuneInventory;

/////////////////////////////////////////////////////////////////////////////////
// The Rune class
class Rune
{
public:
    Rune();
    Rune( RuneID iRuneID, UInt iSlot, RuneSet iSet, RuneRank iRank, RuneQuality iQuality, UInt iLevel,
          RuneStat iMainStat, RuneStat iInnateStat, UInt iInnateStatValue,
          UInt iRandomStatCount, const RuneStat * arrRandomStats, const UInt * arrRandomStatValues );
    ~Rune();

    // Import/Export
    Void ImportFromXML( XMLNode * pNode );
    Void ExportToXML( XMLNode * pNode ) const;

    // Rune Characteristics
    inline RuneID GetID() const;
    inline UInt GetSlot() const;
    inline RuneSet GetSet() const;
    inline RuneRank GetRank() const;
    inline RuneQuality GetQuality() const;
    inline UInt GetLevel() const;

    inline RuneStat GetMainStat() const;
    inline UInt GetMainStatValue() const;

    inline RuneStat GetInnateStat() const;
    inline UInt GetInnateStatValue() const;

    inline RuneStat GetRandomStat( UInt iIndex ) const;
    inline UInt GetRandomStatValue( UInt iIndex ) const;

    // Rune Stat Queries
    inline UInt HasMainStat( RuneStat iRuneStat ) const;
    inline UInt HasInnateStat( RuneStat iRuneStat ) const;
    UInt HasRandomStat( RuneStat iRuneStat ) const;
    UInt HasSubStat( RuneStat iRuneStat ) const;

    // Rune Locks
    inline Bool IsLocked() const;
    inline Void Lock();
    inline Void Unlock();

    // GearSet Equip
    inline Bool IsEquipped() const;
    inline UInt GetGearSetCount() const;
    inline GearSetID GetGearSet( UInt iIndex ) const;
    inline Bool HasGearSet( GearSetID iGearSetID ) const;

    // Score system
    inline Float GetScoreEfficiency() const;
    inline Float GetScoreDamage() const;
    inline Float GetScoreTanking() const;

private:
    // Internals
    friend class CCGOPManager;
    friend class RuneInventory;

    inline UInt _EquipToGearSet( GearSetID iGearSetID );
    inline Void _UnequipFromGearSet( GearSetID iGearSetID );
    inline Void _UnequipFromAllGearSets();

    // Helpers
    Void _ComputeScores();

    // Descriptor
    RuneID m_iRuneID;
    UInt m_iSlot;
    RuneSet m_iSet;
    RuneRank m_iRank;
    RuneQuality m_iQuality;
    UInt m_iLevel;

    RuneStat m_iMainStat;
    RuneStat m_iInnateStat;
    UInt m_iInnateStatValue;
    RuneStat m_arrRandomStats[RUNE_RANDOM_STAT_COUNT];
    UInt m_arrRandomStatValues[RUNE_RANDOM_STAT_COUNT];

    // State
    Bool m_bLocked;
    Array<GearSetID> m_arrEquippedGearSets;

    // Score System
    Float m_fScoreEfficiency; // How close the rune is to max rolls
    Float m_fScoreDamage;     // How much damage the rune provides (factor attack and crit)
    Float m_fScoreTanking;    // How much tankyness the rune provides (factor hp and def)
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "Rune.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_RUNE_H

