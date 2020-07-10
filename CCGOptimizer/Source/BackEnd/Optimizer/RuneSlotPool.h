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
#include "Lib/Datastruct/Array/Array.h"
#include "Lib/Datastruct/Tree/Heap.h"

#include "../CCGOPManager.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

/////////////////////////////////////////////////////////////////////////////////
// The RuneSlotPool class
class RuneSlotPool
{
public:
    RuneSlotPool();
    ~RuneSlotPool();

    // Global access
    inline UInt GetSlot() const;
    inline Bool IsForced() const;

    inline Bool IsEmpty() const;
    inline UInt GetTotalCount() const;

    inline Bool IsSetAvailable( RuneSet iRuneSet ) const;

    // Main Sets Pool access
    inline UInt GetMainSetsTotalCount() const;

    inline Bool IsMainSetAvailable( RuneSet iRuneSet ) const;
    inline Float GetMainSetBestRating( RuneSet iRuneSet ) const;

    inline UInt GetMainSetCount( RuneSet iRuneSet ) const;
    inline RuneID GetMainSetRune( RuneSet iRuneSet, UInt iIndex, Float * outRating = NULL ) const;

    // Off Sets Pool access
    inline UInt GetOffSetsTotalCount() const;

    inline Bool IsOffSetAvailable( RuneSet iRuneSet ) const;
    inline Float GetOffSetBestRating( RuneSet iRuneSet ) const;

    inline UInt GetOffSetCount( RuneSet iRuneSet ) const;
    inline RuneID GetOffSetRune( RuneSet iRuneSet, UInt iIndex, Float * outRating = NULL ) const;

    // Construction Procedure
    inline Void SetSlot( UInt iSlot );
    inline Void SetForced();
    Void AddMainSetRune( RuneID iRuneID, Float fRating );
    Void AddOffSetRune( RuneID iRuneID, Float fRating );
    Void FinalizeSorting();

    Void Reset();

private:
    typedef struct _rune_pool_entry {
        RuneID iRuneID;
        Float fRating;
    } RunePoolEntry;
    typedef Heap<RunePoolEntry> PoolHeap;

    inline static Int _CompareRunePoolEntries( const RunePoolEntry & hLeft, const RunePoolEntry & hRight );

    Bool m_bFinalized;

    UInt m_iRuneSlot;
    Bool m_bIsForced; // True if rune pool has been forced by user (therefore is small)

    UInt m_iMainSetsTotalCount;
    Bool m_arrAvailableMainSets[RUNE_SET_COUNT];
    PoolHeap m_arrMainSetsHeaps[RUNE_SET_COUNT];
    Array<RunePoolEntry> m_arrMainSets[RUNE_SET_COUNT];

    UInt m_iOffSetsTotalCount;
    Bool m_arrAvailableOffSets[RUNE_SET_COUNT];
    PoolHeap m_arrOffSetsHeaps[RUNE_SET_COUNT];
    Array<RunePoolEntry> m_arrOffSets[RUNE_SET_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneSlotPool.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_OPTIMIZER_RUNESLOTPOOL_H

