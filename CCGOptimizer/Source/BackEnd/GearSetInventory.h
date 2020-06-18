/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/GearSetInventory.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSet Inventory Manager
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
#ifndef CCGOP_BACKEND_GEARSETINVENTORY_H
#define CCGOP_BACKEND_GEARSETINVENTORY_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "GearSet.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Search Queries
enum GearSetQuery {
    GEARSET_QUERY_NAME = 0,
    GEARSET_QUERY_HEROES,
    GEARSET_QUERY_RUNES,
    GEARSET_QUERY_STATE,
    GEARSET_QUERY_EFFICIENCY,
    GEARSET_QUERY_DAMAGE,
    GEARSET_QUERY_TANKING
};

typedef union _gearset_query_parameter {
    // GEARSET_QUERY_NAME
    struct _query_name {
        GChar strName[GAMEDATA_NAMES_MAX_LENGTH];
    } hQueryName;

    // GEARSET_QUERY_HEROES
    struct _query_heroes {
        Bool bAndElseOr;
        UInt iHeroCount;
        HeroID arrHeroes[32];
    } hQueryHeroes;

    // GEARSET_QUERY_RUNES
    struct _query_runes {
        Bool bAndElseOr;
        UInt iRuneCount;
        RuneID arrRunes[32];
    } hQueryRunes;

    // GEARSET_QUERY_STATE
    struct _query_state {
        Bool bComplete;
        Bool bEmpty;
    } hQueryState;

    // GEARSET_QUERY_EFFICIENCY
    struct _query_efficiency {
        Float fThreshold;
    } hQueryEfficiency;

    // GEARSET_QUERY_DAMAGE
    struct _query_damage {
        Float fThreshold;
    } hQueryDamage;

    // GEARSET_QUERY_TANKING
    struct _query_tanking {
        Float fThreshold;
    } hQueryTanking;
} GearSetQueryParameter;

typedef TreeMap<GearSetQuery,GearSetQueryParameter> GearSetQueryMap;

// Prototypes
class CCGOPManager;

/////////////////////////////////////////////////////////////////////////////////
// The GearSetInventory class
class GearSetInventory
{
public:
    GearSetInventory();
    ~GearSetInventory();

    // Import/Export
    Void ImportFromXML( XMLNode * pNode );
    Void ExportToXML( XMLNode * pNode ) const;

    // GearSet Inventory
    inline UInt GetGearSetCount() const;
    inline const GearSet * GetGearSet( GearSetID iGearSetID ) const;
    inline GearSet * GetGearSet( GearSetID iGearSetID );

    // Search Engine
    Void FilterSearch( Array<GearSetID> * outResults, const GearSetQueryMap & mapQueries ) const;

private:
    // Internals
    friend class CCGOPManager;

    inline GearSetID _CreateGearSet( const GChar * strName );
    inline Void _DestroyGearSet( GearSetID iGearSetID );
    inline Void _DestroyAllGearSets();

    inline Void _UnequipAll();
    inline Void _DetachAll();

    // Helpers
    inline GearSetID _AllocateGearSetID();

    // Members
    GearSetID m_iNextFreeGearSetID;

    typedef TreeMap<GearSetID, GearSet> GearSetMap;
    GearSetMap m_mapGearSetInventory;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetInventory.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_GEARSETINVENTORY_H

