<?php
/////////////////////////////////////////////////////////////////////////////////
// File : Source/PHP/BackEnd/CCGOptimizer.php
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
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

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions
define( "OPTIMIZER_MAX_SEARCH_DEPTH", 20 ); // TODO : Tweak this ...

/////////////////////////////////////////////////////////////////////////////////
// The SearchParameters class
class SearchParameters
{
    public function __construct()
    {
        $this->ReferenceHeroID = NULL;

        $this->RequestedSets = array();
        $this->ExcludedSets = array();
        $this->AllowBrokenSets = true;

        $this->RequestedMainStats = array( array(), array(), array() );

        $this->ForcedRunes = array();
        $this->ExcludedRunes = array();

        $this->AllowLockedRunes = false;
        $this->AllowEquippedRunes = true;
        //$this->UseMaxLevelMainStatsValues = true;
        //$this->UseMaxLevel12ForOddSlots = true;

        $this->StatsWeights = array(
            HERO_STAT_HP            => 0.0,
            HERO_STAT_ATTACK        => 0.0,
            HERO_STAT_DEFENSE       => 0.0,
            HERO_STAT_SPEED         => 0.0,
            HERO_STAT_CRIT_RATE     => 0.0,
            HERO_STAT_CRIT_DMG      => 0.0,
            HERO_STAT_HIT           => 0.0,
            HERO_STAT_RESISTANCE    => 0.0
        );
        $this->SearchDepth = 10;

        $this->TargetStatsMin = array(
            HERO_STAT_HP            => 0,
            HERO_STAT_ATTACK        => 0,
            HERO_STAT_DEFENSE       => 0,
            HERO_STAT_SPEED         => 0,
            HERO_STAT_CRIT_RATE     => 0,
            HERO_STAT_CRIT_DMG      => 0,
            HERO_STAT_HIT           => 0,
            HERO_STAT_RESISTANCE    => 0
        );
        $this->TargetStatsMax = array(
            HERO_STAT_HP            => PHP_INT_MAX,
            HERO_STAT_ATTACK        => PHP_INT_MAX,
            HERO_STAT_DEFENSE       => PHP_INT_MAX,
            HERO_STAT_SPEED         => PHP_INT_MAX,
            HERO_STAT_CRIT_RATE     => PHP_INT_MAX,
            HERO_STAT_CRIT_DMG      => PHP_INT_MAX,
            HERO_STAT_HIT           => PHP_INT_MAX,
            HERO_STAT_RESISTANCE    => PHP_INT_MAX
        );
    }

    // Helpers
    public function Validate():bool {
        // Must request at least one rune set
        $iRequestedSetCount = count( $this->RequestedSets );
        if ( $iRequestedSetCount == 0 )
            return false;

        // Must not have duplicate requested sets
        for( $i = 0; $i < $iRequestedSetCount; ++$i ) {
            $iSet = $this->RequestedSets[$i];
            for( $j = $i + 1; $j < $iRequestedSetCount; ++$j ) {
                if ( $iSet == $this->RequestedSets[$j] )
                    return false;
            }
        }
        
        // Must not have a set both requested and excluded
        for( $iRequested = 0; $iRequested < $iRequestedSetCount; ++$iRequested ) {
            if ( in_array($this->RequestedSets[$iRequested], $this->ExcludedSets) )
                return false;
        }

        // Must specify at least one main stat in one slot
        $iRequestedMainStatSlot2Count = count( $this->RequestedMainStats[0] );
        $iRequestedMainStatSlot4Count = count( $this->RequestedMainStats[1] );
        $iRequestedMainStatSlot6Count = count( $this->RequestedMainStats[2] );
        if (
            $iRequestedMainStatSlot2Count == 0 &&
            $iRequestedMainStatSlot4Count == 0 &&
            $iRequestedMainStatSlot6Count == 0
        )
            return false;

        // Should not force more than 5 runes (duh!)
        $iForcedRunesCount = count( $this->ForcedRunes );
        if ( $iForcedRunesCount > 5 )
            return false;

        // Ensure no bogus config
        if ( $this->UseMaxLevelMainStatsValues == false )
            $this->UseMaxLevel12ForOddSlots = false;

        // Ensure weights are properly clamped
        for( $iStat = 0; $iStat < HERO_STAT_COUNT; ++$iStat ) {
            if ( $this->StatsWeights[$iStat] < 0.0 )
                $this->StatsWeights[$iStat] = 0.0;
            else if ( $this->StatsWeights[$iStat] > 1.0 )
                $this->StatsWeights[$iStat] = 1.0;
        }

        // Ensure search depth is not too crazy !
        if ( $this->SearchDepth > OPTIMIZER_MAX_SEARCH_DEPTH )
            $this->SearchDepth = OPTIMIZER_MAX_SEARCH_DEPTH;

        // Must have at least one target stat with finite boundary
        $bInfiniteBoundary = true;
        for( $iStat = 0; $iStat < HERO_STAT_COUNT; ++$iStat ) {
            if ( $this->TargetStatsMin < 0 )
                $this->TargetStatsMin = 0;
            if ( $this->TargetStatsMax < $this->TargetStatsMin )
                $this->TargetStatsMax = $this->TargetStatsMin;
            if ( $this->TargetStatsMin > 0 || $this->TargetStatsMax < PHP_INT_MAX ) {
                $bInfiniteBoundary = false;
                break;
            }
        }
        if ( $bInfiniteBoundary )
            return false;

        // Validation Done !
        return true;
    }

    // Members
    public $ReferenceHeroID; // HeroID, optional

        // Set Filtering
    public $RequestedSets;   // array( RUNE_SET_* )
    public $ExcludedSets;    // array( RUNE_SET_* )
    public $AllowBrokenSets; // default = true

        // Main Stats Filtering
    public $RequestedMainStats; // array( Slot2, Slot4, Slot6 )

        // Rune Filtering
    public $ForcedRunes;   // array( rune ids ), may specify several runes for same slot
    public $ExcludedRunes; // array( rune ids )

    public $AllowLockedRunes;           // default = false
    public $AllowEquippedRunes;         // default = true
    //public $UseMaxLevelMainStatsValues; // default = true, only for main stats
    //public $UseMaxLevel12ForOddSlots;   // default = true, only if UseMaxLevelMainStatsValues = true

        // Search Behaviour
    public $StatsWeights; // array( HERO_STAT_* => Weight ), Weights in [0;1], 0.0 = ignore
    public $SearchDepth;  // default = 10, how much runes to consider per slot

        // Target Stats Constraints
    public $TargetStatsMin; // array( HERO_STAT_* => MinValue ), 0 = unconstrained
    public $TargetStatsMax; // array( HERO_STAT_* => MaxValue ), 0 = unconstrained
}

/////////////////////////////////////////////////////////////////////////////////
// The RuneSlotPool class
class RuneSlotPool
{
    public function __construct( int $iRuneSlot )
    {
        $this->RuneSlot = $iRuneSlot;

        $this->IsForced = false;

        $this->AvailableSets = array();
        for( $i = 0; $i < RUNE_SET_COUNT; ++$i ) {
            $this->AvailableSets[$i] = false;
        }
        $this->MainPoolsSize = 0;
        $this->MainPools = array();

        $this->AvailableBrokenSets = array();
        for( $i = 0; $i < RUNE_SET_COUNT; ++$i ) {
            $this->AvailableBrokenSets[$i] = false;
        }
        $this->BrokenPoolsSize = 0;
        $this->BrokenPools = array();

        $this->m_bFinalized = false;
        $this->m_hMainPoolsHeaps = array();
        $this->m_hBrokenPoolsHeaps = array();
    }

    // Methods
    public function IsEmpty():bool {
        return ( ($this->MainPoolsSize + $this->BrokenPoolsSize) == 0 );
    }
    public function GetTotalSize():int {
        return ( $this->MainPoolsSize + $this->BrokenPoolsSize );
    }

    public function IsMainSetAvailable( int $iRuneSet ):bool {
        assert( $iRuneSet < RUNE_SET_COUNT );
        return $this->AvailableSets[$iRuneSet];
    }
    public function IsBrokenSetAvailable( int $iRuneSet ):bool {
        assert( $iRuneSet < RUNE_SET_COUNT );
        return $this->AvailableBrokenSets[$iRuneSet];
    }
    public function IsSetAvailable( int $iRuneSet ):bool {
        assert( $iRuneSet < RUNE_SET_COUNT );
        return ( $this->AvailableSets[$iRuneSet] || $this->AvailableBrokenSets[$iRuneSet] );
    }

    public function AddMainPoolRune( int $iRuneID, float $fRating ):void {
        assert( !$this->m_bFinalized );
        $hCCGOPManager = &CCGOPManager::GetSingleton();
        $hRune = &$hCCGOPManager->GetRune( $iRuneID );
        assert( $hRune->GetSlot() == $this->RuneSlot );
        $iRuneSet = $hRune->GetSet();
        if ( !$this->AvailableSets[$iRuneSet] ) {
            $this->AvailableSets[$iRuneSet] = true;
            $this->m_hMainPoolsHeaps[$iRuneSet] = new Heap( "RuneSlotPool::Comparator" );
        }
        $this->m_hMainPoolsHeaps[$iRuneSet]->Merge( array($iRuneID, $fRating) );
    }
    public function AddBrokenPoolRune( int $iRuneID, float $fRating ):void {
        assert( !$this->m_bFinalized );
        $hCCGOPManager = &CCGOPManager::GetSingleton();
        $hRune = &$hCCGOPManager->GetRune( $iRuneID );
        assert( $hRune->GetSlot() == $this->RuneSlot );
        $iRuneSet = $hRune->GetSet();
        if ( !$this->AvailableBrokenSets[$iRuneSet] ) {
            $this->AvailableBrokenSets[$iRuneSet] = true;
            $this->m_hBrokenPoolsHeaps[$iRuneSet] = new Heap( "RuneSlotPool::Comparator" );
        }
        $this->m_hBrokenPoolsHeaps[$iRuneSet]->Merge( array($iRuneID, $fRating) );
    }

    public function FinalizeSorting():void {
        for( $iSet = 0; $iSet < RUNE_SET_COUNT; ++$iSet ) {
            if ( $this->AvailableSets[$iSet] ) {
                $this->MainPools[$iSet] = array();
                $iCount = 0;
                while( !$this->m_hMainPoolsHeaps[$iSet]->IsEmpty() ) {
                    $this->m_hMainPoolsHeaps[$iSet]->Extract( $this->MainPools[$iSet][$iCount] );
                    ++$iCount;
                }
                $this->MainPoolsSize += $iCount;
            }
            if ( $this->AvailableBrokenSets[$iSet] ) {
                $this->BrokenPools[$iSet] = array();
                $iCount = 0;
                while( !$this->m_hBrokenPoolsHeaps[$iSet]->IsEmpty() ) {
                    $this->m_hBrokenPoolsHeaps[$iSet]->Extract( $this->BrokenPools[$iSet][$iCount] );
                    ++$iCount;
                }
                $this->BrokenPoolsSize += $iCount;
            }
        }
        
        $this->m_bFinalized = true;
        $this->m_hMainPoolsHeaps = NULL;
        $this->m_hBrokenPoolsHeaps = NULL;
    }

    // Helpers
    public static function Comparator( array & $arrLeft, array & $arrRight ):int {
        // Compare based on ratings
        if ( $arrLeft[1] > $arrRight[1] )
            return +1;
        if ( $arrLeft[1] < $arrRight[1] )
            return -1;
        return 0;
    }

    // Members
    public $RuneSlot; // rune slot this pool contains

    public $IsForced; // true if rune pool has been forced by user (therefore is small)

    public $AvailableSets; // available sets for main pools
    public $MainPoolsSize; // total runes in main pools
    public $MainPools;     // requested sets runes

    public $AvailableBrokenSets; // available sets for broken pools
    public $BrokenPoolsSize;     // total runes in broken pools
    public $BrokenPools;         // off-sets runes

    private $m_bFinalized;
    private $m_hMainPoolsHeaps; // Heap sorting
    private $m_hBrokenPoolsHeaps; // Heap sorting
}

/////////////////////////////////////////////////////////////////////////////////
// The CCGOptimizer class
class CCGOptimizer
{
    // Singleton interface
    public static function &GetSingleton():CCGOptimizer {
        if ( CCGOptimizer::$m_hInstance == NULL )
            CCGOptimizer::$m_hInstance = new CCGOptimizer();
        return CCGOptimizer::$m_hInstance;
    }
    protected static $m_hInstance;

    // Constructor / Destructor
    public function __construct()
    {
        $this->m_hSearchParams = new SearchParameters();
        $this->m_arrRuneSlotPools = array();

        $this->m_iEstimatedPermutations = 0;
	}
	public function __destruct()
    {
		// nothing to do
    }

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
}

?>