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
    m_hSearchParams(), m_arrResults( 1024 )
{
    m_iPermutationsCount = 0;

    m_bOptimizing = false;
    m_iExploredPermutation = 0;
    for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
        m_hCurrentPermutation.arrRunes[i] = NULL;
        m_hCurrentPermutation.arrRatings[i] = 0.0f;
    }

    m_arrResults.Create();
}
CCGOptimizer::~CCGOptimizer()
{
	m_arrResults.Destroy();
}

Bool CCGOptimizer::OptimizeBegin()
{
    Assert( !m_bOptimizing );

    UInt iSlot;

    // Validate Search Parameters
    Bool bValid = m_hSearchParams.Validate();
    if ( !bValid )
        return false;

    // Reset search data
    for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot )
        m_arrRuneSlotPools[iSlot].Reset();
    m_arrResults.Clear();

    // Build Rune Slot Pools
    Bool bSuccess = _BuildRuneSlotPools();
    if ( !bSuccess )
        return false;

    // Count Permutations
    _CountPermutations();

    // Start Optimizing
    m_bOptimizing = true;
    m_iExploredPermutation = 0;
    for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
        m_arrRuneSlotPools[iSlot].Enumerate();
        RuneID iRuneID = m_arrRuneSlotPools[iSlot].EnumerateNextRune( m_hCurrentPermutation.arrRatings + iSlot );
        m_hCurrentPermutation.arrRunes[iSlot] = CCGOPFn->GetRune( iRuneID );
    }

    // Done !
    return true;
}
Bool CCGOptimizer::OptimizeStep( UInt iPermutations )
{
    Assert( m_bOptimizing );

    // We're allowed to explore up to iPermutations for this step
    UInt iExploredPermutations = 0;
    while( iExploredPermutations < iPermutations ) {
        // Test current permutation
        if ( _TestValidSets() ) {
            if ( _TestValidStats() )
                m_arrResults.Push( m_hCurrentPermutation );
        }
        ++m_iExploredPermutation;

        // Next Permutation
        Bool bContinue = _GetNextPermutation();

        // End of Optimization case
        if ( !bContinue ) {
            m_bOptimizing = false;
            return false;
        }

        // Proceed
        ++iExploredPermutations;
    }

    // More to compute, delay to next idle time
    return true;
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
    hQueryMap.SetComparator( RuneQueryMap_Compare );
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
            hQueryMap.Insert( RUNE_QUERY_MAINSTAT, hQueryParams );
        } else if ( iSlot == 3 ) { // Slot 4
            hQueryParams.hQueryMainStat.iStatCount = m_hSearchParams.arrRequestedMainStatsSlot4.Count();
            for( i = 0; i < hQueryParams.hQueryMainStat.iStatCount; ++i )
                hQueryParams.hQueryMainStat.arrStats[i] = m_hSearchParams.arrRequestedMainStatsSlot4[i];
            hQueryMap.Insert( RUNE_QUERY_MAINSTAT, hQueryParams );
        } else if ( iSlot == 5 ) { // Slot 6
            hQueryParams.hQueryMainStat.iStatCount = m_hSearchParams.arrRequestedMainStatsSlot6.Count();
            for( i = 0; i < hQueryParams.hQueryMainStat.iStatCount; ++i )
                hQueryParams.hQueryMainStat.arrStats[i] = m_hSearchParams.arrRequestedMainStatsSlot6[i];
            hQueryMap.Insert( RUNE_QUERY_MAINSTAT, hQueryParams );
        }

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

    // Done
    arrQueryResults.Destroy();
    hQueryMap.Destroy();

    return true;
}

Void CCGOptimizer::_CountPermutations()
{
    m_iPermutationsCount = 1;
    for( UInt iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot )
        m_iPermutationsCount *= m_arrRuneSlotPools[iSlot].GetTotalCount();
}
Bool CCGOptimizer::_GetNextPermutation()
{
    for( Int iSlot = RUNE_SLOT_COUNT - 1; iSlot >= 0; --iSlot ) {
        // Step Inner-most Loop
        Float fRating;
        RuneID iRuneID = m_arrRuneSlotPools[iSlot].EnumerateNextRune( &fRating );

        // Loop continues, no need to go further up
        if ( iRuneID != INVALID_OFFSET ) {
            m_hCurrentPermutation.arrRunes[iSlot] = CCGOPFn->GetRune( iRuneID );
            m_hCurrentPermutation.arrRatings[iSlot] = fRating;
            break;
        }

        // Loop has ended

        // Top-most loop case : End of enumeration
        if ( iSlot == 0 )
            return false;

        // Restart loop
        m_arrRuneSlotPools[iSlot].Enumerate();
        iRuneID = m_arrRuneSlotPools[iSlot].EnumerateNextRune( &fRating );
        m_hCurrentPermutation.arrRunes[iSlot] = CCGOPFn->GetRune( iRuneID );
        m_hCurrentPermutation.arrRatings[iSlot] = fRating;

        // Go up to parent loop
    }

    // Done
    return true;
}
Bool CCGOptimizer::_TestValidSets()
{
    UInt iSet, iSlot;

    // Compute Set Counts
    UInt arrSetCounts[RUNE_SET_COUNT];
    for( iSet = 0; iSet < RUNE_SET_COUNT; ++iSet )
        arrSetCounts[iSet] = 0;
    for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
        const Rune * pRune = m_hCurrentPermutation.arrRunes[iSlot];
        ++( arrSetCounts[pRune->GetSet()] );
    }

    // Enumerate requested sets
    UInt iRequestedSetsCount = m_hSearchParams.arrRequestedSets.Count();
    for( iSet = 0; iSet < iRequestedSetsCount; ++iSet ) {
        UInt iSetSize = GameDataFn->GetRuneSetSize( (RuneSet)iSet );
        if ( arrSetCounts[iSet] < iSetSize )
            return false;
        arrSetCounts[iSet] -= iSetSize;
    }

    // Passed !
    return true;
}
Bool CCGOptimizer::_TestValidStats()
{
    UInt iHeroStat, iSlot;

    // Enum all hero stats
    for ( iHeroStat = 0; iHeroStat < HERO_STAT_COUNT; ++iHeroStat ) {
        // Check if there is a requirement
        if ( m_hSearchParams.arrTargetStatsMin[iHeroStat] == 0 && m_hSearchParams.arrTargetStatsMax[iHeroStat] == UINT_MAX )
            continue;

        // Compute total stat
		Bool bStatIsPercent = false;
		Bool bStatIsBoth = false;
		UInt iStatFlatTotal = 0;
		UInt iStatPercentTotal = 0;

		switch( iHeroStat ) {
			case HERO_STAT_HP: {
					bStatIsBoth = true;
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						const Rune * pRune = m_hCurrentPermutation.arrRunes[iSlot];
						RuneRank iRank = pRune->GetRank();

						// Use effective level
						UInt iLevel = pRune->GetLevel();
						if ( m_hSearchParams.bUseMaxLevelMainStatsValues ) {
							if ( m_hSearchParams.bUseMaxLevel12ForOddSlots && ((iSlot & 1) == 0) )
								iLevel = RUNE_MAX_LEVEL - 3;
							else
								iLevel = RUNE_MAX_LEVEL;
						}
						
						// Main stat
						if ( pRune->GetMainStat() == RUNE_STAT_HP_FLAT )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HP_FLAT, iRank, iLevel );
						else if ( pRune->GetMainStat() == RUNE_STAT_HP_PERCENT )
							iStatPercentTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HP_PERCENT, iRank, iLevel );

						// Innate stat
						if ( pRune->GetInnateStat() == RUNE_STAT_HP_FLAT )
							iStatFlatTotal += pRune->GetInnateStatValue();
						else if ( pRune->GetInnateStat() == RUNE_STAT_HP_PERCENT )
							iStatPercentTotal += pRune->GetInnateStatValue();

						// Random stats
						if ( pRune->HasRandomStat(RUNE_STAT_HP_FLAT) )
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_HP_FLAT );
						if ( pRune->HasRandomStat(RUNE_STAT_HP_PERCENT) )
							iStatPercentTotal += pRune->GetRandomStatValue( RUNE_STAT_HP_PERCENT );
					}
				} break;
			case HERO_STAT_ATTACK: {
					bStatIsBoth = true;
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						const Rune * pRune = m_hCurrentPermutation.arrRunes[iSlot];
						RuneRank iRank = pRune->GetRank();

						// Use effective level
						UInt iLevel = pRune->GetLevel();
						if ( m_hSearchParams.bUseMaxLevelMainStatsValues ) {
							if ( m_hSearchParams.bUseMaxLevel12ForOddSlots && ((iSlot & 1) == 0) )
								iLevel = RUNE_MAX_LEVEL - 3;
							else
								iLevel = RUNE_MAX_LEVEL;
						}
						
						// Main stat
						if ( pRune->GetMainStat() == RUNE_STAT_ATTACK_FLAT )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_ATTACK_FLAT, iRank, iLevel );
						else if ( pRune->GetMainStat() == RUNE_STAT_ATTACK_PERCENT )
							iStatPercentTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_ATTACK_PERCENT, iRank, iLevel );

						// Innate stat
						if ( pRune->GetInnateStat() == RUNE_STAT_ATTACK_FLAT )
							iStatFlatTotal += pRune->GetInnateStatValue();
						else if ( pRune->GetInnateStat() == RUNE_STAT_ATTACK_PERCENT )
							iStatPercentTotal += pRune->GetInnateStatValue();

						// Random stats
						if ( pRune->HasRandomStat(RUNE_STAT_ATTACK_FLAT) )
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_FLAT );
						if ( pRune->HasRandomStat(RUNE_STAT_ATTACK_PERCENT) )
							iStatPercentTotal += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_PERCENT );
					}
				} break;
			case HERO_STAT_DEFENSE: {
					bStatIsBoth = true;
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						const Rune * pRune = m_hCurrentPermutation.arrRunes[iSlot];
						RuneRank iRank = pRune->GetRank();

						// Use effective level
						UInt iLevel = pRune->GetLevel();
						if ( m_hSearchParams.bUseMaxLevelMainStatsValues ) {
							if ( m_hSearchParams.bUseMaxLevel12ForOddSlots && ((iSlot & 1) == 0) )
								iLevel = RUNE_MAX_LEVEL - 3;
							else
								iLevel = RUNE_MAX_LEVEL;
						}
						
						// Main stat
						if ( pRune->GetMainStat() == RUNE_STAT_DEFENSE_FLAT )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_DEFENSE_FLAT, iRank, iLevel );
						else if ( pRune->GetMainStat() == RUNE_STAT_DEFENSE_PERCENT )
							iStatPercentTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_DEFENSE_PERCENT, iRank, iLevel );

						// Innate stat
						if ( pRune->GetInnateStat() == RUNE_STAT_DEFENSE_FLAT )
							iStatFlatTotal += pRune->GetInnateStatValue();
						else if ( pRune->GetInnateStat() == RUNE_STAT_DEFENSE_PERCENT )
							iStatPercentTotal += pRune->GetInnateStatValue();

						// Random stats
						if ( pRune->HasRandomStat(RUNE_STAT_DEFENSE_FLAT) )
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_FLAT );
						if ( pRune->HasRandomStat(RUNE_STAT_DEFENSE_PERCENT) )
							iStatPercentTotal += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_PERCENT );
					}
				} break;
			case HERO_STAT_SPEED: {
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						const Rune * pRune = m_hCurrentPermutation.arrRunes[iSlot];
						RuneRank iRank = pRune->GetRank();

						// Use effective level
						UInt iLevel = pRune->GetLevel();
						if ( m_hSearchParams.bUseMaxLevelMainStatsValues ) {
							if ( m_hSearchParams.bUseMaxLevel12ForOddSlots && ((iSlot & 1) == 0) )
								iLevel = RUNE_MAX_LEVEL - 3;
							else
								iLevel = RUNE_MAX_LEVEL;
						}

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_SPEED )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_SPEED, iRank, iLevel );
						else if ( pRune->GetInnateStat() == RUNE_STAT_SPEED )
							iStatFlatTotal += pRune->GetInnateStatValue();
						else if ( pRune->HasRandomStat(RUNE_STAT_SPEED) )
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_SPEED );
					}
				} break;
			case HERO_STAT_CRIT_RATE: {
					bStatIsPercent = true;
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						const Rune * pRune = m_hCurrentPermutation.arrRunes[iSlot];
						RuneRank iRank = pRune->GetRank();

						// Use effective level
						UInt iLevel = pRune->GetLevel();
						if ( m_hSearchParams.bUseMaxLevelMainStatsValues ) {
							if ( m_hSearchParams.bUseMaxLevel12ForOddSlots && ((iSlot & 1) == 0) )
								iLevel = RUNE_MAX_LEVEL - 3;
							else
								iLevel = RUNE_MAX_LEVEL;
						}

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_CRIT_RATE )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_CRIT_RATE, iRank, iLevel );
						else if ( pRune->GetInnateStat() == RUNE_STAT_CRIT_RATE )
							iStatFlatTotal += pRune->GetInnateStatValue();
						else if ( pRune->HasRandomStat(RUNE_STAT_CRIT_RATE) )
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_CRIT_RATE );
					}
				} break;
			case HERO_STAT_CRIT_DMG: {
					bStatIsPercent = true;
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						const Rune * pRune = m_hCurrentPermutation.arrRunes[iSlot];
						RuneRank iRank = pRune->GetRank();

						// Use effective level
						UInt iLevel = pRune->GetLevel();
						if ( m_hSearchParams.bUseMaxLevelMainStatsValues ) {
							if ( m_hSearchParams.bUseMaxLevel12ForOddSlots && ((iSlot & 1) == 0) )
								iLevel = RUNE_MAX_LEVEL - 3;
							else
								iLevel = RUNE_MAX_LEVEL;
						}

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_CRIT_DMG )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_CRIT_DMG, iRank, iLevel );
						else if ( pRune->GetInnateStat() == RUNE_STAT_CRIT_DMG )
							iStatFlatTotal += pRune->GetInnateStatValue();
						else if ( pRune->HasRandomStat(RUNE_STAT_CRIT_DMG) )
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_CRIT_DMG );
					}
				} break;
			case HERO_STAT_HIT: {
					bStatIsPercent = true;
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						const Rune * pRune = m_hCurrentPermutation.arrRunes[iSlot];
						RuneRank iRank = pRune->GetRank();

						// Use effective level
						UInt iLevel = pRune->GetLevel();
						if ( m_hSearchParams.bUseMaxLevelMainStatsValues ) {
							if ( m_hSearchParams.bUseMaxLevel12ForOddSlots && ((iSlot & 1) == 0) )
								iLevel = RUNE_MAX_LEVEL - 3;
							else
								iLevel = RUNE_MAX_LEVEL;
						}

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_HIT )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HIT, iRank, iLevel );
						else if ( pRune->GetInnateStat() == RUNE_STAT_HIT )
							iStatFlatTotal += pRune->GetInnateStatValue();
						else if ( pRune->HasRandomStat(RUNE_STAT_HIT) )
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_HIT );
					}
				} break;
			case HERO_STAT_RESISTANCE: {
					bStatIsPercent = true;
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						const Rune * pRune = m_hCurrentPermutation.arrRunes[iSlot];
						RuneRank iRank = pRune->GetRank();

						// Use effective level
						UInt iLevel = pRune->GetLevel();
						if ( m_hSearchParams.bUseMaxLevelMainStatsValues ) {
							if ( m_hSearchParams.bUseMaxLevel12ForOddSlots && ((iSlot & 1) == 0) )
								iLevel = RUNE_MAX_LEVEL - 3;
							else
								iLevel = RUNE_MAX_LEVEL;
						}

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_RESISTANCE )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_RESISTANCE, iRank, iLevel );
						else if ( pRune->GetInnateStat() == RUNE_STAT_RESISTANCE )
							iStatFlatTotal += pRune->GetInnateStatValue();
						else if ( pRune->HasRandomStat(RUNE_STAT_RESISTANCE) )
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_RESISTANCE );
					}
				} break;
			default: Assert(false); break;
		}

		// Retrieve Reference Hero
		const Hero * pRefHero = m_hSearchParams.pReferenceHero;

		// Compare stats
		if ( pRefHero == NULL ) {
			// Pure stats case
			if ( bStatIsPercent ) {
				if ( iStatFlatTotal < m_hSearchParams.arrTargetStatsMin[iHeroStat] )
					return false;
				if ( iStatFlatTotal > m_hSearchParams.arrTargetStatsMax[iHeroStat] )
					return false;
			} else if ( bStatIsBoth ) {
				UInt iMinPercent = ( m_hSearchParams.arrTargetStatsMin[iHeroStat] && 0xffff0000 ) >> 16;
				UInt iMinFlat = ( m_hSearchParams.arrTargetStatsMin[iHeroStat] && 0x0000ffff );
				UInt iMaxPercent = ( m_hSearchParams.arrTargetStatsMax[iHeroStat] && 0xffff0000 ) >> 16;
				UInt iMaxFlat = ( m_hSearchParams.arrTargetStatsMax[iHeroStat] && 0x0000ffff );

				if ( iStatPercentTotal < iMinPercent )
					return false;
				if ( iStatPercentTotal > iMaxPercent )
					return false;
				if ( iStatFlatTotal < iMinFlat )
					return false;
				if ( iStatFlatTotal > iMaxFlat )
					return false;
			} else {
				if ( iStatFlatTotal < m_hSearchParams.arrTargetStatsMin[iHeroStat] )
					return false;
				if ( iStatFlatTotal > m_hSearchParams.arrTargetStatsMax[iHeroStat] )
					return false;
			}
		} else {
			// Reference Hero stats case
			UInt iBaseValue = GameDataFn->GetHeroBaseStat( pRefHero->GetName(), (HeroStat)iHeroStat, pRefHero->GetRank(), pRefHero->GetLevel(), pRefHero->IsEvolved() );

			if ( pRefHero->IsSanctified() ) {
				HeroSanctify iSanctify = pRefHero->GetSanctification();
				UInt iSanctifyBonus = GameDataFn->GetHeroSanctifyBonus( iSanctify );
				switch( iSanctify ) {
					case HERO_SANCTIFY_HP:
						if ( iHeroStat == HERO_STAT_HP )
							iBaseValue += (UInt)( ((Float)iSanctifyBonus) * 0.01f * (Float)iBaseValue );
						break;
					case HERO_SANCTIFY_ATT:
						if ( iHeroStat == HERO_STAT_ATTACK )
							iBaseValue += (UInt)( ((Float)iSanctifyBonus) * 0.01f * (Float)iBaseValue );
						break;
					case HERO_SANCTIFY_DEF:
						if ( iHeroStat == HERO_STAT_DEFENSE )
							iBaseValue += (UInt)( ((Float)iSanctifyBonus) * 0.01f * (Float)iBaseValue );
						break;
					case HERO_SANCTIFY_HIT:
						if ( iHeroStat == HERO_STAT_HIT )
							iBaseValue += iSanctifyBonus;
						break;
					case HERO_SANCTIFY_RES:
						if ( iHeroStat == HERO_STAT_RESISTANCE )
							iBaseValue += iSanctifyBonus;
						break;
					default: Assert(false); break;
				}
			}

			UInt iBonusValue = iStatFlatTotal + (UInt)( ((Float)iStatPercentTotal) * 0.01f * (Float)iBaseValue );
			UInt iTotalValue = iBaseValue + iBonusValue;

			if ( iTotalValue < m_hSearchParams.arrTargetStatsMin[iHeroStat] )
				return false;
			if ( iTotalValue > m_hSearchParams.arrTargetStatsMax[iHeroStat] )
				return false;
		}
    }

	// Passed !
	return true;
}

