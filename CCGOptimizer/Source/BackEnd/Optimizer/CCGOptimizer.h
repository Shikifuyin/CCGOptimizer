/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Optimizer/CCGOptimizer.h
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
// Header prelude
#ifndef CCGOP_BACKEND_OPTIMIZER_CCGOPTIMIZER_H
#define CCGOP_BACKEND_OPTIMIZER_CCGOPTIMIZER_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "../CCGOPManager.h"

#include "SearchParameters.h"
#include "RuneSlotPool.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Result Builds
typedef struct _optimizer_result {
    RuneID arrRunes[RUNE_SLOT_COUNT];
    Float arrRatings[RUNE_SLOT_COUNT];
} OptimizerResult;

/////////////////////////////////////////////////////////////////////////////////
// The CCGOptimizer class
class CCGOptimizer
{
    // Discrete singleton interface
public:
    inline static CCGOptimizer * GetInstance();

private:
    CCGOptimizer();
    ~CCGOptimizer();

public:
    // Search Parameters
    inline SearchParameters * GetSearchParameters();

    // Search Results
    inline UInt GetEstimatedPermutations() const;

    // public function GetBuildCount():int {
    // }
    // public function GetAllBuilds():array {
    // }k

    // Main Search Algorithm
    Bool OptimizeBegin();
    Bool OptimizeStep( UInt iPermutations );

private:
    // Heuristics
    Float _ComputeRating( const Rune * pRune );

    // Search Sub-Routines
    Bool _BuildRuneSlotPools();
    Void _EstimatePermutations();

    Bool _GetNextPermutation();

    // Members
    SearchParameters m_hSearchParams;
    RuneSlotPool m_arrRuneSlotPools[RUNE_SLOT_COUNT];

    Bool m_bOptimizing;
    UInt m_iEstimatedPermutations;

    OptimizerResult m_hCurrentPermutation;

    Array<OptimizerResult> m_arrResults;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "CCGOptimizer.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_OPTIMIZER_CCGOPTIMIZER_H

