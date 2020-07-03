/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/RuneInventory.cpp
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
// Includes
#include "RuneInventory.h"

/////////////////////////////////////////////////////////////////////////////////
// RuneQueryMap Comparator
Int RuneQueryMap_Compare( const RuneQuery & rLeft, const RuneQuery & rRight, Void * pUserData )
{
    if ( rLeft < rRight )
        return +1;
    if ( rLeft > rRight )
        return +1;
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneInventory implementation
RuneInventory::RuneInventory():
    m_mapRuneInventory()
{
    m_iNextFreeRuneID = 0;

    m_mapRuneInventory.SetComparator( _Compare_RuneID );
    m_mapRuneInventory.Create();
}
RuneInventory::~RuneInventory()
{
    m_mapRuneInventory.Destroy();
}

Void RuneInventory::ImportFromXML( XMLNode * pNode )
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("inventory_runes")) == 0 );

    m_mapRuneInventory.Clear();

    UInt iRuneCount = pNode->GetChildCount();
    RuneID iBiggestID = 0;

    for ( UInt i = 0; i < iRuneCount; ++i ) {
        XMLNode * pRuneNode = pNode->GetChildNByTag( TEXT("rune"), i );
        Rune hRune;
        hRune.ImportFromXML( pRuneNode );
        m_mapRuneInventory.Insert( hRune.GetID(), hRune );
        if ( hRune.GetID() > iBiggestID )
            iBiggestID = hRune.GetID();
    }

    m_iNextFreeRuneID = iBiggestID + 1;
}
Void RuneInventory::ExportToXML( XMLNode * pNode ) const
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("inventory_runes")) == 0 );

    RuneMap::Iterator itRune = m_mapRuneInventory.Begin();

    while( !(itRune.IsNull()) ) {
        XMLNode * pRuneNode = XMLFn->CreateNode( TEXT("rune"), false );
        const Rune * pRune = itRune.GetItemPtr();
        pRune->ExportToXML( pRuneNode );
        pNode->AppendChild( pRuneNode );
        ++itRune;
    }
}

Void RuneInventory::FilterSearch( Array<RuneID> * outResults, const RuneQueryMap & mapQueries, const Array<RuneID> * arrExcluded, Bool bAllowLocked, Bool bAllowEquipped ) const
{
    Assert( outResults != NULL );
    Assert( outResults->IsCreated() );
    Assert( mapQueries.IsCreated() );

    UInt i, iCount;

    // Search
    RuneMap::Iterator itRune = m_mapRuneInventory.Begin();
    while( !(itRune.IsNull()) ) {
        RuneID iRuneID = itRune.GetKey();
        const Rune * pRune = itRune.GetItemPtr();

        // Filter Excluded
        if ( arrExcluded != NULL ) {
            Assert( arrExcluded->IsCreated() );
            if ( arrExcluded->Search(iRuneID) != INVALID_OFFSET ) {
                ++itRune;
                continue;
            }
        }

        // Filter Locked
        if ( !bAllowLocked ) {
            if ( pRune->IsLocked() ) {
                ++itRune;
                continue;
            }
        }

        // Filter Equipped
        if ( !bAllowEquipped ) {
            if ( pRune->IsEquipped() ) {
                ++itRune;
                continue;
            }
        }

        // Filter Slot
        if ( mapQueries.Contains(RUNE_QUERY_SLOT) ) {
            Bool bFilterOut = true;
            iCount = mapQueries[RUNE_QUERY_SLOT].hQuerySlot.iSlotCount;
            for( i = 0; i < iCount; ++i ) {
                UInt iSlot = mapQueries[RUNE_QUERY_SLOT].hQuerySlot.arrSlots[i];
                if ( pRune->GetSlot() == iSlot ) {
                    bFilterOut = false;
                    break;
                }
            }
            if ( bFilterOut ) {
                ++itRune;
                continue;
            }
        }

        // Filter Set
        if ( mapQueries.Contains(RUNE_QUERY_SET) ) {
            Bool bFilterOut = true;
            iCount = mapQueries[RUNE_QUERY_SET].hQuerySet.iSetCount;
            for( i = 0; i < iCount; ++i ) {
                RuneSet iSet = mapQueries[RUNE_QUERY_SET].hQuerySet.arrSets[i];
                if ( pRune->GetSet() == iSet ) {
                    bFilterOut = false;
                    break;
                }
            }
            if ( bFilterOut ) {
                ++itRune;
                continue;
            }
        }

        // Filter MainStat
        if ( mapQueries.Contains(RUNE_QUERY_MAINSTAT) ) {
            Bool bFilterOut = true;
            iCount = mapQueries[RUNE_QUERY_MAINSTAT].hQueryMainStat.iStatCount;
            for( i = 0; i < iCount; ++i ) {
                RuneStat iStat = mapQueries[RUNE_QUERY_MAINSTAT].hQueryMainStat.arrStats[i];
                if ( pRune->GetMainStat() == iStat ) {
                    bFilterOut = false;
                    break;
                }
            }
            if ( bFilterOut ) {
                ++itRune;
                continue;
            }
        }

        // Filter SubStats
        if ( mapQueries.Contains(RUNE_QUERY_SUBSTATS) ) {
            Bool bFilterOut;
            Bool bAndElseOr = mapQueries[RUNE_QUERY_SUBSTATS].hQuerySubStats.bAndElseOr;
            iCount = mapQueries[RUNE_QUERY_SUBSTATS].hQuerySubStats.iStatCount;
            if ( bAndElseOr ) { // match all specified sub stats
                bFilterOut = false;
                for( i = 0; i < iCount; ++i ) {
                    RuneStat iStat = mapQueries[RUNE_QUERY_SUBSTATS].hQuerySubStats.arrStats[i];
                    UInt iStatThreshold = mapQueries[RUNE_QUERY_SUBSTATS].hQuerySubStats.arrStatValues[i];
                    UInt iStatValue = 0;
                    if ( pRune->HasSubStat(iStat) )
                        iStatValue = pRune->GetSubStatValue( iStat );
                    if ( iStatValue < iStatThreshold ) {
                        bFilterOut = true;
                        break;
                    }
                }
            } else { // match at least one specified sub stat
                bFilterOut = true;
                for( i = 0; i < iCount; ++i ) {
                    RuneStat iStat = mapQueries[RUNE_QUERY_SUBSTATS].hQuerySubStats.arrStats[i];
                    UInt iStatThreshold = mapQueries[RUNE_QUERY_SUBSTATS].hQuerySubStats.arrStatValues[i];
                    UInt iStatValue = 0;
                    if ( pRune->HasSubStat(iStat) )
                        iStatValue = pRune->GetSubStatValue( iStat );
                    if ( iStatValue >= iStatThreshold ) {
                        bFilterOut = false;
                        break;
                    }
                }
            }
            if ( bFilterOut ) {
                ++itRune;
                continue;
            }
        }

        // Filter Efficiency
        if ( mapQueries.Contains(RUNE_QUERY_EFFICIENCY) ) {
            if ( pRune->GetScoreEfficiency() < mapQueries[RUNE_QUERY_EFFICIENCY].hQueryEfficiency.fThreshold ) {
                ++itRune;
                continue;
            }
        }

        // Filter Damage
        if ( mapQueries.Contains(RUNE_QUERY_DAMAGE) ) {
            if ( pRune->GetScoreDamage() < mapQueries[RUNE_QUERY_DAMAGE].hQueryDamage.fThreshold ) {
                ++itRune;
                continue;
            }
        }

        // Filter Tanking
        if ( mapQueries.Contains(RUNE_QUERY_TANKING) ) {
            if ( pRune->GetScoreTanking() < mapQueries[RUNE_QUERY_TANKING].hQueryTanking.fThreshold ) {
                ++itRune;
                continue;
            }
        }

        // Passed all filters, Collect
        outResults->Push( iRuneID );

        // Next Rune
        ++itRune;
    }
}

/////////////////////////////////////////////////////////////////////////////////

Int RuneInventory::_Compare_RuneID( const RuneID & rLeft, const RuneID & rRight, Void * pUserData )
{
    if ( rLeft < rRight )
        return +1;
    if ( rLeft > rRight )
        return -1;
    return 0;
}

