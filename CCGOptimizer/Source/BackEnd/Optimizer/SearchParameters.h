/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Optimizer/SearchParameters.h
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
// Header prelude
#ifndef CCGOP_BACKEND_OPTIMIZER_SEARCHPARAMETERS_H
#define CCGOP_BACKEND_OPTIMIZER_SEARCHPARAMETERS_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "../CCGOPManager.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions
#define OPTIMIZER_MAX_SEARCH_DEPTH 20 // TODO : Tweak this ...

/////////////////////////////////////////////////////////////////////////////////
// The SearchParameters class
class SearchParameters
{
public:
    SearchParameters();
    ~SearchParameters();

    // Validation Procedure
    Bool Validate();

    // Members
    const Hero * pReferenceHero; // Optional

        // Set Filtering
    Array<RuneSet> arrRequestedSets;
    Array<RuneSet> arrExcludedSets;
    Bool bAllowOffSets; // default = true

        // Main Stats Filtering
    Array<RuneStat> arrRequestedMainStatsSlot2;
    Array<RuneStat> arrRequestedMainStatsSlot4;
    Array<RuneStat> arrRequestedMainStatsSlot6;

        // Rune Filtering
    Array<RuneID> arrForcedRunes; // May specify several runes for same slot
    Array<RuneID> arrExcludedRunes;

    Bool bAllowLockedRunes; // default = false
    Bool bAllowEquippedRunes; // default = true
    Bool bUseMaxLevelMainStatsValues; // default = true, only for main stats
    Bool bUseMaxLevel12ForOddSlots;   // default = true, only if UseMaxLevelMainStatsValues = true

        // Search Behaviour
    Float arrStatsWeights[HERO_STAT_COUNT]; // Weights in [0;1], 0 = ignore
    UInt iSearchDepth;                      // default = 10, How many runes to consider per slot

        // Target Stats Constraints (can be a combined %/flat value)
    UInt arrTargetStatsMin[HERO_STAT_COUNT]; // 0 = unconstrained
    UInt arrTargetStatsMax[HERO_STAT_COUNT]; // UINT_MAX = unconstrained
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "SearchParameters.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_OPTIMIZER_SEARCHPARAMETERS_H

