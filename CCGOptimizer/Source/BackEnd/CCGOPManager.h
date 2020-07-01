/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/CCGOPManager.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOP Main Interface
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
#ifndef CCGOP_BACKEND_CCGOPMANAGER_H
#define CCGOP_BACKEND_CCGOPMANAGER_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "GameData.h"

#include "Rune.h"
#include "Hero.h"
#include "GearSet.h"

#include "RuneInventory.h"
#include "HeroInventory.h"
#include "GearSetInventory.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions
#define CCGOPFn CCGOPManager::GetInstance()

/////////////////////////////////////////////////////////////////////////////////
// The CCGOPManager class
class CCGOPManager
{
    // Discrete singleton interface
public:
    inline static CCGOPManager * GetInstance();

private:
    CCGOPManager();
    ~CCGOPManager();

public:
    // Import / Export
    Void ImportFromXML( const GChar * strFileName );
    Void ExportToXML( const GChar * strFileName ) const;

    // Rune Management
    inline UInt GetRuneCount() const;
    inline const Rune * GetRune( RuneID iRuneID ) const;
    inline Rune * GetRune( RuneID iRuneID );

    inline RuneInventory::RuneMap::Iterator EnumRunes() const;

    inline RuneID CreateRune( UInt iSlot, RuneSet iSet, RuneRank iRank, RuneQuality iQuality, UInt iLevel,
                              RuneStat iMainStat, RuneStat iInnateStat, UInt iInnateStatValue,
                              UInt iRandomStatCount, const RuneStat * arrRandomStats, const UInt * arrRandomStatValues );
    inline Void DestroyRune( RuneID iRuneID );
    inline Void DestroyAllRunes();

    inline Void LockAllRunes();
    inline Void UnlockAllRunes();

    // Hero Management
    inline UInt GetHeroCount() const;
    inline const Hero * GetHero( HeroID iHeroID ) const;
    inline Hero * GetHero( HeroID iHeroID );

    inline HeroInventory::HeroMap::Iterator EnumHeroes() const;

    inline HeroID CreateHero( const GChar * strName, HeroRank iRank, UInt iLevel, Bool bEvolved, HeroSanctify iSanctify );
    inline Void DestroyHero( HeroID iHeroID );
    inline Void DestroyAllHeroes();

    inline Void UnselectAllHeroGearSets();

    // GearSet Management
    inline UInt GetGearSetCount() const;
    inline const GearSet * GetGearSet( GearSetID iGearSetID ) const;
    inline GearSet * GetGearSet( GearSetID iGearSetID );

    inline GearSetID CreateGearSet( const GChar * strName );
    inline Void DestroyGearSet( GearSetID iGearSetID );
    inline Void DestroyAllGearSets();

    // Rune Equip management
    Bool EquipRuneToGearSet( RuneID iRuneID, GearSetID iGearSetID );
    Void UnequipRuneFromGearSet( RuneID iRuneID, GearSetID iGearSetID );
    Void UnequipAllRunesFromGearSet( GearSetID iGearSetID );
    Void UnequipRuneFromAllGearSets( RuneID iRuneID );
    Void UnequipAllRunes();

    // GearSet Attach management
    Bool AttachGearSetToHero( GearSetID iGearSetID, HeroID iHeroID );
    Void DetachGearSetFromHero( GearSetID iGearSetID, HeroID iHeroID );
    Void DetachAllGearSetsFromHero( HeroID iHeroID );
    Void DetachGearSetFromAllHeroes( GearSetID iGearSetID );
    Void DetachAllGearSets();

    // Search Engine
    inline Void FilterRunes( Array<RuneID> * outResults, const RuneQueryMap & mapQueries, const Array<RuneID> * arrExcluded, Bool bAllowLocked, Bool bAllowEquipped ) const;
    inline Void FilterHeroes( Array<HeroID> * outResults, const HeroQueryMap & mapQueries ) const;
    inline Void FilterGearSets( Array<GearSetID> * outResults, const GearSetQueryMap & mapQueries ) const;

    // Optimizer Engine

private:
    // Members
    RuneInventory m_hRuneInventory;
    HeroInventory m_hHeroInventory;
    GearSetInventory m_hGearSetInventory;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "CCGOPManager.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_CCGOPMANAGER_H

