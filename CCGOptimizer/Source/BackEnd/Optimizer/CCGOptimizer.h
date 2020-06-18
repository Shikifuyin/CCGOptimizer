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
    public function &GetSearchParameters():SearchParameters {
        return $this->m_hSearchParams;
    }

    // Search Results
    public function GetEstimatedPermutations():int {
        return $this->m_iEstimatedPermutations;
    }

    // public function GetBuildCount():int {
    // }
    // public function GetAllBuilds():array {
    // }

    // Main Search Algorithm
    public function Optimize():bool {
        // Validate Search Parameters
        $bValidSearch = $this->m_hSearchParams->Validate();
        if ( !$bValidSearch )
            return false;

        // Reset search data
        /////////////////////////////////

        // Filter Rune Pool
        $bSuccess = $this->_BuildSlotPools();
        if ( !$bSuccess )
            return false;

        // Explore all permutations (!!)
        $this->_ExplorePermutations();

        // Done !
        return true;
    }

    // Search Sub-Routines
    private function _BuildSlotPools():bool {
        $hCCGOP = &CCGOPManager::GetSingleton();

        $this->m_arrRuneSlotPools = array();

        // Build each slot pools independantly
        for( $iSlot = 0; $iSlot < RUNE_SLOT_COUNT; ++$iSlot ) {
            $this->m_arrRuneSlotPools[$iSlot] = new RuneSlotPool( $iSlot );

            // Check forced runes first
            $iForcedRunesCount = count( $this->m_hSearchParams->ForcedRunes );
            for( $i = 0; $i < $iForcedRunesCount; ++$i ) {
                $iRuneID = $this->m_hSearchParams->ForcedRunes[$i];
                $hRune = &$hCCGOP->GetRune( $iRuneID );
                if ( $hRune->GetSlot() == $iSlot ) {
                    $this->m_arrRuneSlotPools[$iSlot]->IsForced = true;
                    $this->m_arrRuneSlotPools[$iSlot]->AddMainPoolRune( $iRuneID, $this->_ComputeRating($hRune) );
                }
            }
            // Slot is forced, stop here
            if ( $this->m_arrRuneSlotPools[$iSlot]->IsForced ) {
                // Finalize Sorting
                $this->m_arrRuneSlotPools[$iSlot]->FinalizeSorting();
                continue;
            }

            // First Pass : MainPool runes

            // Query this slot
            $arrQueries = array();
            $arrQueries[RUNE_QUERY_SLOT] = array( $iSlot );

            // Query requested sets
            $arrQueries[RUNE_QUERY_SET] = $this->m_hSearchParams->RequestedSets;

            // Query main stats for even slots ( even slots have odd values :s )
            if ( $iSlot % 2 == 1 ) {
                $iIndex = floor( $iSlot / 2 );
                $iCount = count( $this->m_hSearchParams->RequestedMainStats[$iIndex] );
                if ( $iCount > 0 ) {
                    $arrQueries[RUNE_QUERY_MAINSTAT] = $this->m_hSearchParams->RequestedMainStats[$iIndex];
                }
            }

            // Perform the query
            $arrCollection = $hCCGOP->FilterRunes(
                $arrQueries,
                $this->m_hSearchParams->ExcludedRunes,
                $this->m_hSearchParams->AllowLockedRunes,
                $this->m_hSearchParams->AllowEquippedRunes
            );

            // Populate main pool
            $iCount = count( $arrCollection );
            for( $i = 0; $i < $iCount; ++$i ) {
                $hRune = &$hCCGOP->GetRune( $arrCollection[$i] );
                $this->m_arrRuneSlotPools[$iSlot]->AddMainPoolRune( $arrCollection[$i], $this->_ComputeRating($hRune) );
            }

            // Second Pass : BrokenPool runes
            if ( $this->m_hSearchParams->AllowBrokenSets ) {
                // Query non-requested sets
                $arrQueries[RUNE_QUERY_SET] = array();
                for( $iSet = 0; $iSet < RUNE_SET_COUNT; ++$iSet ) {
                    // Exclude Requested sets, we already have them
                    if ( in_array($iSet, $this->m_hSearchParams->RequestedSets) )
                        continue;

                    // Handle Excluded Sets here
                    if ( in_array($iSet, $this->m_hSearchParams->ExcludedSets) )
                        continue;

                    // Request this set
                    array_push( $arrQueries[RUNE_QUERY_SET], $iSet );
                }

                // Perform the query
                $arrCollection = $hCCGOP->FilterRunes(
                    $arrQueries,
                    $this->m_hSearchParams->ExcludedRunes,
                    $this->m_hSearchParams->AllowLockedRunes,
                    $this->m_hSearchParams->AllowEquippedRunes
                );

                // Populate broken pool
                $iCount = count( $arrCollection );
                for( $i = 0; $i < $iCount; ++$i ) {
                    $hRune = &$hCCGOP->GetRune( $arrCollection[$i] );
                    $this->m_arrRuneSlotPools[$iSlot]->AddBrokenPoolRune( $arrCollection[$i], $this->_ComputeRating($hRune) );
                }
            }

            // Finalize Sorting
            $this->m_arrRuneSlotPools[$iSlot]->FinalizeSorting();

            // Check for failure at this point (most likely failed to match main stats ...)
            if ( $this->m_arrRuneSlotPools[$iSlot]->IsEmpty() )
                return false;
        }

        // Done
        $this->_EstimatePermutations();
        return true;
    }
    private function _ExplorePermutations():void {
        // Computational heaviness is here ...

    }

    // Helpers
    private function _ComputeRating( Rune & $hRune ):float {
        // All the magic happens here ...
        $fRating = 0.0;

        // 

        return $fRating;
    }
    private function _EstimatePermutations():void {
        $this->m_iEstimatedPermutations = 1;
        for( $iSlot = 0; $iSlot < RUNE_SLOT_COUNT; ++$iSlot ) {
            $this->m_iEstimatedPermutations *= $this->m_arrRuneSlotPools[$iSlot]->GetTotalSize();
        }
    }

    // Members
    private $m_hSearchParams;
    private $m_arrRuneSlotPools;

    private $m_iEstimatedPermutations;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "CCGOptimizer.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_OPTIMIZER_CCGOPTIMIZER_H

