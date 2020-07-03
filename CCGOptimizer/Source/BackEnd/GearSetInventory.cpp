/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/GearSetInventory.cpp
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
// Includes
#include "GearSetInventory.h"

/////////////////////////////////////////////////////////////////////////////////
// GearSetInventory implementation
GearSetInventory::GearSetInventory():
    m_mapGearSetInventory()
{
    m_iNextFreeGearSetID = 0;

    m_mapGearSetInventory.SetComparator( _Compare_GearSetID );
    m_mapGearSetInventory.Create();
}
GearSetInventory::~GearSetInventory()
{
    m_mapGearSetInventory.Destroy();
}

Void GearSetInventory::ImportFromXML( XMLNode * pNode )
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("inventory_gearsets")) == 0 );

    m_mapGearSetInventory.Clear();

    UInt iGearSetCount = pNode->GetChildCount();
    GearSetID iBiggestID = 0;

    for ( UInt i = 0; i < iGearSetCount; ++i ) {
        XMLNode * pGearSetNode = pNode->GetChildNByTag( TEXT("gearset"), i );
        GearSet hGearSet;
        hGearSet.ImportFromXML( pGearSetNode );
        m_mapGearSetInventory.Insert( hGearSet.GetID(), hGearSet );
        if ( hGearSet.GetID() > iBiggestID )
            iBiggestID = hGearSet.GetID();
    }

    m_iNextFreeGearSetID = iBiggestID + 1;
}
Void GearSetInventory::ExportToXML( XMLNode * pNode ) const
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("inventory_gearsets")) == 0 );

    GearSetMap::Iterator itGearSet = m_mapGearSetInventory.Begin();

    while( !(itGearSet.IsNull()) ) {
        XMLNode * pGearSetNode = XMLFn->CreateNode( TEXT("gearset"), false );
        const GearSet * pGearSet = itGearSet.GetItemPtr();
        pGearSet->ExportToXML( pGearSetNode );
        pNode->AppendChild( pGearSetNode );
        ++itGearSet;
    }
}

Void GearSetInventory::FilterSearch( Array<GearSetID> * outResults, const GearSetQueryMap & mapQueries ) const
{
    Assert( outResults != NULL );
    Assert( outResults->IsCreated() );
    Assert( mapQueries.IsCreated() );

    UInt i, iCount;

    // Search
    GearSetMap::Iterator itGearSet = m_mapGearSetInventory.Begin();
    while( !(itGearSet.IsNull()) ) {
        GearSetID iGearSetID = itGearSet.GetKey();
        const GearSet * pGearSet = itGearSet.GetItemPtr();

        // Filter Name
        if ( mapQueries.Contains(GEARSET_QUERY_NAME) ) {
            if ( StringFn->Cmp( pGearSet->GetName(), mapQueries[GEARSET_QUERY_NAME].hQueryName.strName ) != 0 ) {
                ++itGearSet;
                continue;
            }
        }

        // Filter Heroes
        if ( mapQueries.Contains(GEARSET_QUERY_HEROES) ) {
            Bool bFilterOut;
            Bool bAndElseOr = mapQueries[GEARSET_QUERY_HEROES].hQueryHeroes.bAndElseOr;
            iCount = mapQueries[GEARSET_QUERY_HEROES].hQueryHeroes.iHeroCount;
            if ( bAndElseOr ) { // match all specified heroes
                bFilterOut = false;
                for( i = 0; i < iCount; ++i ) {
                    HeroID iHeroID = mapQueries[GEARSET_QUERY_HEROES].hQueryHeroes.arrHeroes[i];
                    if ( !(pGearSet->HasAttachedHero(iHeroID)) ) {
                        bFilterOut = true;
                        break;
                    }
                }
            } else { // match at least one specified hero
                bFilterOut = true;
                for( i = 0; i < iCount; ++i ) {
                    HeroID iHeroID = mapQueries[GEARSET_QUERY_HEROES].hQueryHeroes.arrHeroes[i];
                    if ( pGearSet->HasAttachedHero(iHeroID) ) {
                        bFilterOut = false;
                        break;
                    }
                }
            }
            if ( bFilterOut ) {
                ++itGearSet;
                continue;
            }
        }

        // Filter Runes
        if ( mapQueries.Contains(GEARSET_QUERY_RUNES) ) {
            Bool bFilterOut;
            Bool bAndElseOr = mapQueries[GEARSET_QUERY_RUNES].hQueryRunes.bAndElseOr;
            iCount = mapQueries[GEARSET_QUERY_RUNES].hQueryRunes.iRuneCount;
            if ( bAndElseOr ) { // match all specified heroes
                bFilterOut = false;
                for( i = 0; i < iCount; ++i ) {
                    RuneID iRuneID = mapQueries[GEARSET_QUERY_RUNES].hQueryRunes.arrRunes[i];
                    if ( pGearSet->HasEquippedRune(iRuneID) == INVALID_OFFSET ) {
                        bFilterOut = true;
                        break;
                    }
                }
            } else { // match at least one specified hero
                bFilterOut = true;
                for( i = 0; i < iCount; ++i ) {
                    RuneID iRuneID = mapQueries[GEARSET_QUERY_RUNES].hQueryRunes.arrRunes[i];
                    if ( pGearSet->HasEquippedRune(iRuneID) != INVALID_OFFSET ) {
                        bFilterOut = false;
                        break;
                    }
                }
            }
            if ( bFilterOut ) {
                ++itGearSet;
                continue;
            }
        }

        // Filter State
        if ( mapQueries.Contains(GEARSET_QUERY_STATE) ) {
            Bool bComplete = true;
            Bool bEmpty = true;
            iCount = RUNE_SLOT_COUNT;
            for( i = 0; i < iCount; ++i ) {
                if ( pGearSet->GetEquippedRune( i ) == INVALID_OFFSET )
                    bComplete = false;
                else
                    bEmpty = false;
            }
            if ( bComplete != mapQueries[GEARSET_QUERY_STATE].hQueryState.bComplete ) {
                ++itGearSet;
                continue;
            }
            if ( bEmpty != mapQueries[GEARSET_QUERY_STATE].hQueryState.bEmpty ) {
                ++itGearSet;
                continue;
            }
        }

        // Filter Efficiency
        if ( mapQueries.Contains(GEARSET_QUERY_EFFICIENCY) ) {
            if ( pGearSet->GetScoreEfficiency() < mapQueries[GEARSET_QUERY_EFFICIENCY].hQueryEfficiency.fThreshold ) {
                ++itGearSet;
                continue;
            }
        }

        // Filter Damage
        if ( mapQueries.Contains(GEARSET_QUERY_DAMAGE) ) {
            if ( pGearSet->GetScoreDamage() < mapQueries[GEARSET_QUERY_DAMAGE].hQueryDamage.fThreshold ) {
                ++itGearSet;
                continue;
            }
        }

        // Filter Tanking
        if ( mapQueries.Contains(GEARSET_QUERY_TANKING) ) {
            if ( pGearSet->GetScoreTanking() < mapQueries[GEARSET_QUERY_TANKING].hQueryTanking.fThreshold ) {
                ++itGearSet;
                continue;
            }
        }

        // Passed all filters, Collect
        outResults->Push( iGearSetID );

        // Next GearSet
        ++itGearSet;
    }
}

/////////////////////////////////////////////////////////////////////////////////

Int GearSetInventory::_Compare_GearSetID( const GearSetID & rLeft, const GearSetID & rRight, Void * pUserData )
{
    if ( rLeft < rRight )
        return +1;
    if ( rLeft > rRight )
        return -1;
    return 0;
}

