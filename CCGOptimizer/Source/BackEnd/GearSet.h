/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/GearSet.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Gear Sets
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
#ifndef CCGOP_BACKEND_GEARSET_H
#define CCGOP_BACKEND_GEARSET_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "Rune.h"
#include "Hero.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Heroes Per GearSet
#define GEARSET_MAX_HEROES 64

// Prototypes
class CCGOPManager;
class GearSetInventory;

/////////////////////////////////////////////////////////////////////////////////
// The GearSet class
class GearSet
{
public:
    GearSet();
    GearSet( GearSetID iGearSetID, const GChar * strName );
    ~GearSet();

    // Import/Export
    Void ImportFromXML( XMLNode * pNode );
    Void ExportToXML( XMLNode * pNode ) const;

	// ID
    inline GearSetID GetID() const;

	// Name
    inline const GChar * GetName() const;
    inline Void SetName( const GChar * strName );

    // Active Sets
    Bool HasActiveSet( RuneSet iRuneSet, UInt * outAmount = NULL ) const;

    inline Bool HasFull6Set() const;
    inline UInt GetActiveSetCount() const;
    inline RuneSet GetActiveSet( UInt iIndex ) const;

    // Effective Stats
    inline UInt GetEffectiveStatPercent( HeroStat iHeroStat, Bool bMaxedRunes, Bool bMax12OddSlots ) const;
    inline UInt GetEffectiveStatFlat( HeroStat iHeroStat, Bool bMaxedRunes, Bool bMax12OddSlots ) const;

    // Rune Equip
    inline RuneID GetEquippedRune( UInt iSlot ) const;
    inline UInt HasEquippedRune( RuneID iRuneID ) const;

    // Hero Attach
    inline UInt GetAttachedHeroCount() const;
    inline HeroID GetAttachedHero( UInt iIndex ) const;
    Bool HasAttachedHero( HeroID iHeroID ) const;

    // Score system
    inline Float GetScoreEfficiency() const;
    inline Float GetScoreDamage() const;
    inline Float GetScoreTanking() const;

private:
    // Internals
    friend class CCGOPManager;
    friend class GearSetInventory;

    inline Void _EquipRune( RuneID iRuneID, UInt iSlot );
    inline Void _UnequipRune( UInt iSlot );
    inline Void _UnequipAllRunes();

    UInt _AttachToHero( HeroID iHeroID );
    Void _DetachFromHero( HeroID iHeroID );
    inline Void _DetachFromAllHeroes();

    // Helpers
    Void _ComputeActiveSets();
    Void _ComputeEffectiveStats();

    Void _ComputeScores();

    // Descriptor
    GearSetID m_iGearSetID;
    GChar m_strName[GAMEDATA_NAMES_MAX_LENGTH];

    Bool m_bHasFull6Set;
    UInt m_iActiveSetsCount;
    RuneSet m_arrActiveSets[4]; // Max is 3

    UInt m_arrEffectiveStatsPercent[HERO_STAT_COUNT];
    UInt m_arrEffectiveStatsFlat[HERO_STAT_COUNT];

    UInt m_arrEffectiveStatsPercentMaxed[HERO_STAT_COUNT];
    UInt m_arrEffectiveStatsFlatMaxed[HERO_STAT_COUNT];

    UInt m_arrEffectiveStatsPercentMaxed12Odd[HERO_STAT_COUNT];
    UInt m_arrEffectiveStatsFlatMaxed12Odd[HERO_STAT_COUNT];

    // State
    RuneID m_arrEquippedRunes[RUNE_SLOT_COUNT];

    UInt m_iAttachedHeroesCount;
    HeroID m_arrAttachedHeroes[GEARSET_MAX_HEROES];

    // Score System
    Float m_fScoreEfficiency;
    Float m_fScoreDamage;
    Float m_fScoreTanking;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSet.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_GEARSET_H

