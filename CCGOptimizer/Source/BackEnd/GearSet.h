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

    // Rune Equip
    inline RuneID GetEquippedRune( UInt iSlot ) const;
    inline UInt HasEquippedRune( RuneID iRuneID ) const;

    // Hero Attach
    inline UInt GetAttachedHeroCount() const;
    inline HeroID GetAttachedHero( UInt iIndex ) const;
    inline Bool HasAttachedHero( HeroID iHeroID ) const;

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

    inline UInt _AttachToHero( HeroID iHeroID );
    inline Void _DetachFromHero( HeroID iHeroID );
    inline Void _DetachFromAllHeroes();

    // Helpers
    Void _ComputeScores();

    // Descriptor
    GearSetID m_iGearSetID;
    GChar m_strName[GAMEDATA_NAMES_MAX_LENGTH];

    // State
    RuneID m_arrEquippedRunes[RUNE_SLOT_COUNT];
    Array<HeroID> m_arrAttachedHeroes;

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

