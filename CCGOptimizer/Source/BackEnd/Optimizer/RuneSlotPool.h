/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Optimizer/RuneSlotPool.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Optimized Search Pooled Runes
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
#ifndef CCGOP_BACKEND_OPTIMIZER_RUNESLOTPOOL_H
#define CCGOP_BACKEND_OPTIMIZER_RUNESLOTPOOL_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "Lib/Datastruct/Tree/Heap.h"

#include "../CCGOPManager.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

/////////////////////////////////////////////////////////////////////////////////
// The RuneSlotPool class
class RuneSlotPool
{
public:
    RuneSlotPool::RuneSlotPool( int $iRuneSlot )
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
    RuneSlotPool::RuneSlotPool()
    {
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

private:
    private $m_bFinalized;
    private $m_hMainPoolsHeaps; // Heap sorting
    private $m_hBrokenPoolsHeaps; // Heap sorting
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneSlotPool.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_OPTIMIZER_RUNESLOTPOOL_H

