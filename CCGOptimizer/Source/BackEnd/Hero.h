/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Hero.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Hero Representation
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
#ifndef CCGOP_BACKEND_HERO_H
#define CCGOP_BACKEND_HERO_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "GameData.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Hero IDs
typedef UInt HeroID;

// GearSet ID
#ifndef GearSetID
    typedef UInt GearSetID;
#endif // GearSetID

// GearSets Per Hero
#define HERO_MAX_GEARSETS 64

// Prototypes
class CCGOPManager;
class HeroInventory;

/////////////////////////////////////////////////////////////////////////////////
// The Hero class
class Hero
{
public:
	Hero();
	Hero( HeroID iHeroID, const GChar * strName, HeroRank iRank, UInt iLevel, Bool bEvolved, HeroSanctify iSanctify );
	~Hero();

	// Import/Export
	Void ImportFromXML( XMLNode * pNode );
	Void ExportToXML( XMLNode * pNode ) const;

	// Hero Characteristics
	inline HeroID GetID() const;
	inline const GChar * GetName() const;
	inline HeroFaction GetFaction() const;
	inline HeroRank GetRank() const;
	inline UInt GetLevel() const;
	inline Bool IsEvolved() const;
	inline Bool IsSanctified() const;
	inline HeroSanctify GetSanctification() const;
	inline Void SetSanctification( HeroSanctify iSanctify );

	// GearSet Attach
	inline UInt GetGearSetCount() const;
	inline GearSetID GetGearSet( UInt iIndex ) const;
	Bool HasGearSet( GearSetID iGearSetID ) const;

	inline GearSetID GetSelectedGearSet() const;
	inline Void SelectGearSet( GearSetID iGearSetID );
	inline Void UnselectGearSet();

private:
	// Internals
	friend class CCGOPManager;
	friend class HeroInventory;

	UInt _AttachGearSet( GearSetID iGearSetID );
	Void _DetachGearSet( GearSetID iGearSetID );
	inline Void _DetachAllGearSets();

    // Descriptor
	HeroID m_iHeroID;
	GChar m_strName[GAMEDATA_NAMES_MAX_LENGTH];
	HeroFaction m_iFaction;
	HeroRank m_iRank;
	UInt m_iLevel;
	Bool m_bEvolved;
	HeroSanctify m_iSanctify;

    // State
	UInt m_iAttachedGearSetsCount;
	GearSetID m_arrAttachedGearSets[HERO_MAX_GEARSETS];
	GearSetID m_iSelectedGearSet;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "Hero.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_HERO_H

