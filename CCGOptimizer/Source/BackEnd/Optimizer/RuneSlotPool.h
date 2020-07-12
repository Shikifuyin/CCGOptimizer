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

    // Sets Availability
    inline UInt GetMainSetsCount() const;
    inline UInt GetOffSetsCount() const;

    inline Bool IsSetAvailable( RuneSet iRuneSet ) const;
    inline Bool IsMainSetAvailable( RuneSet iRuneSet ) const;
    inline Bool IsOffSetAvailable( RuneSet iRuneSet ) const;

    inline Float GetMainSetBestRating() const;
    inline Float GetOffSetBestRating() const;

    // Direct Access
    inline RuneID GetMainSetRune( UInt iIndex, Float * outRating = NULL ) const;
    inline RuneID GetOffSetRune( UInt iIndex, Float * outRating = NULL ) const;

    // Construction Procedure
    inline Void SetSlot( UInt iSlot );
    inline Void SetForced();
    Void AddMainSetRune( RuneID iRuneID, Float fRating );
    Void AddOffSetRune( RuneID iRuneID, Float fRating );
    Void FinalizeSorting();

    Void Reset();

    // Enumeration
    inline Bool IsEnumerating() const;
    Void Enumerate();
    RuneID EnumerateNextRune( Float * outRating = NULL );

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

    Bool m_arrAvailableMainSets[RUNE_SET_COUNT];
    Bool m_arrAvailableOffSets[RUNE_SET_COUNT];

    PoolHeap m_hMainSetsHeap;
    PoolHeap m_hOffSetsHeap;

    Array<RunePoolEntry> m_arrMainSets;
    Array<RunePoolEntry> m_arrOffSets;

    Bool m_bEnumerating;
    UInt m_iEnumMainSetIndex;
    UInt m_iEnumOffSetIndex;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneSlotPool.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_OPTIMIZER_RUNESLOTPOOL_H

