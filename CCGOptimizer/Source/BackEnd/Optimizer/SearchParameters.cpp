/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Optimizer/SearchParameters.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Optimized Search Parameters
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Include
#include "SearchParameters.h"

/////////////////////////////////////////////////////////////////////////////////
// SearchParameters implementation
SearchParameters::SearchParameters():
    arrRequestedSets(32), arrExcludedSets(32),
    arrRequestedMainStatsSlot2(8), arrRequestedMainStatsSlot4(8), arrRequestedMainStatsSlot6(8),
    arrForcedRunes(32), arrExcludedRunes(32)
{
    UInt i;

    pReferenceHero = NULL;

    arrRequestedSets.Create();
    arrExcludedSets.Create();
    bAllowOffSets = true;

    arrRequestedMainStatsSlot2.Create();
    arrRequestedMainStatsSlot4.Create();
    arrRequestedMainStatsSlot6.Create();

    arrForcedRunes.Create();
    arrExcludedRunes.Create();

    bAllowLockedRunes = false;
    bAllowEquippedRunes = true;
    bUseMaxLevelMainStatsValues = true;
    bUseMaxLevel12ForOddSlots = true;

    for( i = 0; i < HERO_STAT_COUNT; ++i )
        arrStatsWeights[i] = 0.0f;

    iSearchDepth = 10;

    for( i = 0; i < HERO_STAT_COUNT; ++i ) {
        arrTargetStatsMin[i] = 0;
        arrTargetStatsMax[i] = UINT_MAX;
    }
}
SearchParameters::~SearchParameters()
{
    arrRequestedSets.Destroy();
    arrExcludedSets.Destroy();

    arrRequestedMainStatsSlot2.Destroy();
    arrRequestedMainStatsSlot4.Destroy();
    arrRequestedMainStatsSlot6.Destroy();

    arrForcedRunes.Destroy();
    arrExcludedRunes.Destroy();
}

Bool SearchParameters::Validate()
{
    UInt i, j;

    // Must request at least one rune set
    UInt iRequestedSetCount = arrRequestedSets.Count();
    if ( iRequestedSetCount == 0 )
        return false;

    // Must not have duplicate requested sets
    for( i = 0; i < iRequestedSetCount; ++i ) {
        RuneSet iSet = arrRequestedSets[i];
        for( j = i + 1; j < iRequestedSetCount; ++j ) {
            if ( iSet == arrRequestedSets[j] )
                return false;
        }
    }
        
    // Must not have a set both requested and excluded
    for( i = 0; i < iRequestedSetCount; ++i ) {
        if ( arrExcludedSets.Search(arrRequestedSets[i]) != INVALID_OFFSET )
            return false;
    }

    // Must specify at least one main stat in one slot
    UInt iRequestedMainStatSlot2Count = arrRequestedMainStatsSlot2.Count();
    UInt iRequestedMainStatSlot4Count = arrRequestedMainStatsSlot4.Count();
    UInt iRequestedMainStatSlot6Count = arrRequestedMainStatsSlot6.Count();
    if ( iRequestedMainStatSlot2Count == 0 &&
         iRequestedMainStatSlot4Count == 0 &&
         iRequestedMainStatSlot6Count == 0 )
        return false;

    // Should not force more than 5 runes (duh!)
    UInt iForcedRunesCount = arrForcedRunes.Count();
    if ( iForcedRunesCount > 5 )
        return false;

    // Ensure no bogus config
    if ( bUseMaxLevelMainStatsValues == false )
        bUseMaxLevel12ForOddSlots = false;

    // Ensure weights are properly clamped
    for( i = 0; i < HERO_STAT_COUNT; ++i ) {
        if ( arrStatsWeights[i] < 0.0f )
            arrStatsWeights[i] = 0.0f;
        else if ( arrStatsWeights[i] > 1.0f )
            arrStatsWeights[i] = 1.0f;
    }

    // Ensure search depth is not too crazy !
    if ( iSearchDepth > OPTIMIZER_MAX_SEARCH_DEPTH )
        iSearchDepth = OPTIMIZER_MAX_SEARCH_DEPTH;

    // Must have at least one target stat with finite boundary
    Bool bInfiniteBoundary = true;
    for( i = 0; i < HERO_STAT_COUNT; ++i ) {
        if ( arrTargetStatsMin[i] < 0 )
            arrTargetStatsMin[i] = 0;
        if ( arrTargetStatsMax[i] < arrTargetStatsMin[i] )
            arrTargetStatsMax[i] = arrTargetStatsMin[i];
        if ( arrTargetStatsMin[i] > 0 || arrTargetStatsMax[i] < UINT_MAX )
            bInfiniteBoundary = false;
    }
    if ( bInfiniteBoundary )
        return false;

    // Validation Done !
    return true;
}
