/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Optimizer/CCGOptimizer.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Optimized Search Implementation
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
#include "CCGOptimizer.h"

/////////////////////////////////////////////////////////////////////////////////
// CCGOptimizer implementation
CCGOptimizer::CCGOptimizer():
    m_hSearchParams()
{
    m_iEstimatedPermutations = 0;
}
CCGOptimizer::~CCGOptimizer()
{
	// nothing to do
}

Bool CCGOptimizer::Optimize()
{
    // Validate Search Parameters
    Bool bValid = m_hSearchParams.Validate();
    if ( !bValid )
        return false;

    // Reset search data
    for( UInt iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot )
        m_arrRuneSlotPools[iSlot].Reset();

    // Filter Rune Pool
    Bool bSuccess = _BuildRuneSlotPools();
    if ( !bSuccess )
        return false;

    // Explore all permutations (!!)
    bSuccess = _ExplorePermutations();

    // Done !
    return bSuccess;
}

/////////////////////////////////////////////////////////////////////////////////

Float CCGOptimizer::_ComputeRating( const Rune * pRune )
{
    // All the magic happens here ...
    Float fRating = 0.0f;

    //////////////////////////////////////

    return fRating;
}

Bool CCGOptimizer::_BuildRuneSlotPools()
{
    UInt i;

    // Prepare for Rune Queries
    RuneQueryParameter hQueryParams;
    RuneQueryMap hQueryMap;
    hQueryMap.Create();

    Array<RuneID> arrQueryResults;
    arrQueryResults.Create();

    // Build each slot pools independantly
    for( UInt iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {

        // Init
        m_arrRuneSlotPools[iSlot].SetSlot( iSlot );

        // Check forced runes first
        UInt iForcedRunesCount = m_hSearchParams.arrForcedRunes.Count();
        for( i = 0; i < iForcedRunesCount; ++i ) {
            RuneID iRuneID = m_hSearchParams.arrForcedRunes[i];
            const Rune * pRune = CCGOPFn->GetRune( iRuneID );
            if ( pRune->GetSlot() == iSlot ) {
                m_arrRuneSlotPools[iSlot].SetForced();
                m_arrRuneSlotPools[iSlot].AddMainSetRune( iRuneID, _ComputeRating(pRune) );
            }
        }
        // Slot is forced, stop here
        if ( m_arrRuneSlotPools[iSlot].IsForced() ) {
            // Finalize Sorting
            m_arrRuneSlotPools[iSlot].FinalizeSorting();
            continue;
        }

        // First Pass : Main-Sets runes
        hQueryMap.Clear();
        arrQueryResults.Clear();

        // Query this slot
        hQueryParams.hQuerySlot.iSlotCount = 1;
        hQueryParams.hQuerySlot.arrSlots[0] = iSlot;
        hQueryMap.Insert( RUNE_QUERY_SLOT, hQueryParams );

        // Query requested sets
        hQueryParams.hQuerySet.iSetCount = m_hSearchParams.arrRequestedSets.Count();
        for( i = 0; i < hQueryParams.hQuerySet.iSetCount; ++i )
            hQueryParams.hQuerySet.arrSets[i] = m_hSearchParams.arrRequestedSets[i];
        hQueryMap.Insert( RUNE_QUERY_SET, hQueryParams );

        // Query main stats for even slots ( even slots have odd values :s )
        if ( iSlot == 1 ) { // Slot 2
            hQueryParams.hQueryMainStat.iStatCount = m_hSearchParams.arrRequestedMainStatsSlot2.Count();
            for( i = 0; i < hQueryParams.hQueryMainStat.iStatCount; ++i )
                hQueryParams.hQueryMainStat.arrStats[i] = m_hSearchParams.arrRequestedMainStatsSlot2[i];
        } else if ( iSlot == 3 ) { // Slot 4
            hQueryParams.hQueryMainStat.iStatCount = m_hSearchParams.arrRequestedMainStatsSlot4.Count();
            for( i = 0; i < hQueryParams.hQueryMainStat.iStatCount; ++i )
                hQueryParams.hQueryMainStat.arrStats[i] = m_hSearchParams.arrRequestedMainStatsSlot4[i];
        } else if ( iSlot == 5 ) { // Slot 6
            hQueryParams.hQueryMainStat.iStatCount = m_hSearchParams.arrRequestedMainStatsSlot6.Count();
            for( i = 0; i < hQueryParams.hQueryMainStat.iStatCount; ++i )
                hQueryParams.hQueryMainStat.arrStats[i] = m_hSearchParams.arrRequestedMainStatsSlot6[i];
        }
        hQueryMap.Insert( RUNE_QUERY_MAINSTAT, hQueryParams );

        // Perform the query
        CCGOPFn->FilterRunes (
            &arrQueryResults, hQueryMap,
            &(m_hSearchParams.arrExcludedRunes),
            m_hSearchParams.bAllowLockedRunes,
            m_hSearchParams.bAllowEquippedRunes
        );

        // Populate Main-Sets pool
        UInt iFilteredRuneCount = arrQueryResults.Count();
        for( i = 0; i < iFilteredRuneCount; ++i ) {
            const Rune * pRune = CCGOPFn->GetRune( arrQueryResults[i] );
            m_arrRuneSlotPools[iSlot].AddMainSetRune( arrQueryResults[i], _ComputeRating(pRune) );
        }

        // Second Pass : Off-Sets runes
        arrQueryResults.Clear();

        // Check if we're allowed to use Off-Sets
        if ( m_hSearchParams.bAllowOffSets ) {

            // Query non-requested sets
            hQueryParams.hQuerySet.iSetCount = 0;
            for( i = 0; i < RUNE_SET_COUNT; ++i ) {
                // Exclude Requested sets, we already have them
                if ( m_hSearchParams.arrRequestedSets.Search((RuneSet)i) != INVALID_OFFSET )
                    continue;

                // Handle Excluded Sets here
                if ( m_hSearchParams.arrExcludedSets.Search((RuneSet)i) != INVALID_OFFSET )
                    continue;

                // Request this set
                hQueryParams.hQuerySet.arrSets[hQueryParams.hQuerySet.iSetCount] = (RuneSet)i;
                ++(hQueryParams.hQuerySet.iSetCount);
            }
            hQueryMap[RUNE_QUERY_SET] = hQueryParams;

            // Perform the query
            CCGOPFn->FilterRunes (
                &arrQueryResults, hQueryMap,
                &(m_hSearchParams.arrExcludedRunes),
                m_hSearchParams.bAllowLockedRunes,
                m_hSearchParams.bAllowEquippedRunes
            );

            // Populate Off-Sets pool
            iFilteredRuneCount = arrQueryResults.Count();
            for( i = 0; i < iFilteredRuneCount; ++i ) {
                const Rune * pRune = CCGOPFn->GetRune( arrQueryResults[i] );
                m_arrRuneSlotPools[iSlot].AddOffSetRune( arrQueryResults[i], _ComputeRating(pRune) );
            }

        }

        // Finalize Sorting
        m_arrRuneSlotPools[iSlot].FinalizeSorting();

        // Check for failure at this point (most likely failed to match main stats ...)
        if ( m_arrRuneSlotPools[iSlot].IsEmpty() ) {
            arrQueryResults.Destroy();
            hQueryMap.Destroy();
            return false;
        }
    }

    // Estimate Permutations
    _EstimatePermutations();

    // Done
    arrQueryResults.Destroy();
    hQueryMap.Destroy();

    return true;
}
Bool CCGOptimizer::_ExplorePermutations()
{
    // Computational heaviness is here ...
    return true;
}

Void CCGOptimizer::_EstimatePermutations()
{
    // This is the Upper Bound
    m_iEstimatedPermutations = 1;
    for( UInt iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot )
        m_iEstimatedPermutations *= m_arrRuneSlotPools[iSlot].GetTotalCount();
}

