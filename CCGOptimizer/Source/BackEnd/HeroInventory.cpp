/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/HeroInventory.cpp
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
// Includes
#include "HeroInventory.h"

#include "CCGOPManager.h"

/////////////////////////////////////////////////////////////////////////////////
// HeroInventory implementation
HeroInventory::HeroInventory():
    m_mapHeroInventory()
{
    m_iNextFreeHeroID = 0;

    m_mapHeroInventory.Create();
}
HeroInventory::~HeroInventory()
{
    m_mapHeroInventory.Destroy();
}

Void HeroInventory::ImportFromXML( XMLNode * pNode )
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("inventory_heroes")) == 0 );

    m_mapHeroInventory.Clear();

    UInt iHeroCount = pNode->GetChildCount();
    HeroID iBiggestID = 0;

    for ( UInt i = 0; i < iHeroCount; ++i ) {
        XMLNode * pHeroNode = pNode->GetChildNByTag( TEXT("hero"), i );
        Hero hHero;
        hHero.ImportFromXML( pHeroNode );
        m_mapHeroInventory.Insert( hHero.GetID(), hHero );
        if ( hHero.GetID() > iBiggestID )
            iBiggestID = hHero.GetID();
    }

    m_iNextFreeHeroID = iBiggestID + 1;
}
Void HeroInventory::ExportToXML( XMLNode * pNode ) const
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("inventory_heroes")) == 0 );

    HeroMap::Iterator itHero = m_mapHeroInventory.Begin();

    while( !(itHero.IsNull()) ) {
        XMLNode * pHeroNode = XMLFn->CreateNode( TEXT("hero"), false );
        const Hero * pHero = itHero.GetItemPtr();
        pHero->ExportToXML( pHeroNode );
        pNode->AppendChild( pHeroNode );
        ++itHero;
    }
}

Void HeroInventory::FilterSearch( Array<HeroID> * outResults, const HeroQueryMap & mapQueries ) const
{
    Assert( outResults != NULL );
    Assert( outResults->IsCreated() );
    Assert( mapQueries.IsCreated() );

    UInt i, iCount;

    // Search
    HeroMap::Iterator itHero = m_mapHeroInventory.Begin();
    while( !(itHero.IsNull()) ) {
        HeroID iHeroID = itHero.GetKey();
        const Hero * pHero = itHero.GetItemPtr();

        // Filter Name
        if ( mapQueries.Contains(HERO_QUERY_NAME) ) {
            if ( StringFn->Cmp( pHero->GetName(), mapQueries[HERO_QUERY_NAME].hQueryName.strName ) != 0 )
                continue;
        }

        // Filter Faction
        if ( mapQueries.Contains(HERO_QUERY_FACTION) ) {
            if ( pHero->GetFaction() != mapQueries[HERO_QUERY_FACTION].hQueryFaction.iFaction )
                continue;
        }

        // Filter Rank
        if ( mapQueries.Contains(HERO_QUERY_RANK) ) {
            if ( pHero->GetRank() != mapQueries[HERO_QUERY_RANK].hQueryRank.iRank )
                continue;
        }

        // Filter Level
        if ( mapQueries.Contains(HERO_QUERY_LEVEL) ) {
            if ( pHero->GetLevel() < mapQueries[HERO_QUERY_LEVEL].hQueryLevel.iLevel )
                continue;
        }
        
        // Filter Evolved
        if ( mapQueries.Contains(HERO_QUERY_EVOLVED) ) {
            if ( pHero->IsEvolved() != mapQueries[HERO_QUERY_EVOLVED].hQueryEvolved.bEvolved )
                continue;
        }

        // Filter GearSet
        if ( mapQueries.Contains(HERO_QUERY_GEARSET) ) {
            Bool bFilterOut = true;
            iCount = pHero->GetGearSetCount();
            for ( i = 0; i < iCount; ++i ) {
                if ( pHero->GetGearSet(i) == mapQueries[HERO_QUERY_GEARSET].hQueryGearSet.iGearSetID ) {
                    bFilterOut = false;
                    break;
                }
            }
            if ( bFilterOut )
                continue;
        }

        // Filter Runes
        if ( mapQueries.Contains(HERO_QUERY_RUNES) ) {
            Bool bFilterOut;
            Bool bAndElseOr = mapQueries[HERO_QUERY_RUNES].hQueryRunes.bAndElseOr;
            iCount = mapQueries[HERO_QUERY_RUNES].hQueryRunes.iRuneCount;
            UInt iGearSetCount = pHero->GetGearSetCount();
            if ( bAndElseOr ) { // match all specified runes
                bFilterOut = false;
                for( i = 0; i < iCount; ++i ) {
                    Bool bFound = false;
                    for( UInt iGearSet = 0; iGearSet < iGearSetCount; ++iGearSet ) {
                        GearSetID iGearSetID = pHero->GetGearSet(iGearSet);
                        const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );
                        if ( pGearSet->HasEquippedRune( mapQueries[HERO_QUERY_RUNES].hQueryRunes.arrRunes[i] ) ) {
                            bFound = true;
                            break;
                        }
                    }
                    if ( !bFound ) {
                        bFilterOut = true;
                        break;
                    }
                }
            } else { // match at least one specified rune
                bFilterOut = true;
                for( i = 0; i < iCount; ++i ) {
                    Bool bFound = false;
                    for( UInt iGearSet = 0; iGearSet < iGearSetCount; ++iGearSet ) {
                        GearSetID iGearSetID = pHero->GetGearSet(iGearSet);
                        const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );
                        if ( pGearSet->HasEquippedRune( mapQueries[HERO_QUERY_RUNES].hQueryRunes.arrRunes[i] ) ) {
                            bFound = true;
                            break;
                        }
                    }
                    if ( bFound ) {
                        bFilterOut = false;
                        break;
                    }
                }
            }
            if ( bFilterOut )
                continue;
        }

        // Passed all filters, Collect
        outResults->Push( iHeroID );

        // Next Hero
        ++itHero;
    }
}


