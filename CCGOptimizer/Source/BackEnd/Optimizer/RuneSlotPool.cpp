/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Optimizer/RuneSlotPool.cpp
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
// Includes
#include "RuneSlotPool.h"

/////////////////////////////////////////////////////////////////////////////////
// RuneSlotPool implementation
RuneSlotPool::RuneSlotPool()
{
    UInt i;

    m_bFinalized = false;

    m_iRuneSlot = INVALID_OFFSET;
    m_bIsForced = false;

    for( i = 0; i < RUNE_SET_COUNT; ++i )
        m_arrAvailableMainSets[i] = false;

    for( i = 0; i < RUNE_SET_COUNT; ++i )
        m_arrAvailableOffSets[i] = false;

    m_bEnumerating = false;
    m_iEnumMainSetIndex = INVALID_OFFSET;
    m_iEnumOffSetIndex = INVALID_OFFSET;
}
RuneSlotPool::~RuneSlotPool()
{
    Assert( m_bFinalized );

    if ( m_arrMainSets.IsCreated() )
        m_arrMainSets.Destroy();
    if ( m_arrOffSets.IsCreated() )
        m_arrOffSets.Destroy();
}

Void RuneSlotPool::AddMainSetRune( RuneID iRuneID, Float fRating )
{
    Assert( m_iRuneSlot != INVALID_OFFSET );
    Assert( !m_bFinalized );

    const Rune * pRune = CCGOPFn->GetRune( iRuneID );
    Assert( pRune->GetSlot() == m_iRuneSlot );

    RuneSet iSet = pRune->GetSet();
    if ( !(m_arrAvailableMainSets[iSet]) )
        m_arrAvailableMainSets[iSet] = true;

    if ( !(m_hMainSetsHeap.IsCreated()) ) {
        m_hMainSetsHeap.SetComparator( _CompareRunePoolEntries );
        m_hMainSetsHeap.Create();
    }

    RunePoolEntry hEntry;
    hEntry.iRuneID = iRuneID;
    hEntry.fRating = fRating;
    m_hMainSetsHeap.Merge( hEntry );
}
Void RuneSlotPool::AddOffSetRune( RuneID iRuneID, Float fRating )
{
    Assert( m_iRuneSlot != INVALID_OFFSET );
    Assert( !m_bFinalized );

    const Rune * pRune = CCGOPFn->GetRune( iRuneID );
    Assert( pRune->GetSlot() == m_iRuneSlot );

    RuneSet iSet = pRune->GetSet();
    if ( !(m_arrAvailableOffSets[iSet]) )
        m_arrAvailableOffSets[iSet] = true;

    if ( !(m_hOffSetsHeap.IsCreated()) ) {
        m_hOffSetsHeap.SetComparator( _CompareRunePoolEntries );
        m_hOffSetsHeap.Create();
    }

    RunePoolEntry hEntry;
    hEntry.iRuneID = iRuneID;
    hEntry.fRating = fRating;
    m_hOffSetsHeap.Merge( hEntry );
}
Void RuneSlotPool::FinalizeSorting()
{
    Assert( m_iRuneSlot != INVALID_OFFSET );
    Assert( !m_bFinalized );

    if ( m_hMainSetsHeap.IsCreated() ) {
        m_arrMainSets.Create();
        while ( !(m_hMainSetsHeap.IsEmpty()) ) {
            RunePoolEntry hEntry;
            m_hMainSetsHeap.Extract( hEntry );
            m_arrMainSets.Push( hEntry );
        }
        m_hMainSetsHeap.Destroy();
    }

    if ( m_hOffSetsHeap.IsCreated() ) {
        m_arrOffSets.Create();
        while ( !(m_hOffSetsHeap.IsEmpty()) ) {
            RunePoolEntry hEntry;
            m_hOffSetsHeap.Extract( hEntry );
            m_arrOffSets.Push( hEntry );
        }
        m_hOffSetsHeap.Destroy();
    }
        
    m_bFinalized = true;
}

Void RuneSlotPool::Reset()
{
    Assert( m_bFinalized );

    UInt i;

    if ( m_arrMainSets.IsCreated() )
        m_arrMainSets.Destroy();
    if ( m_arrOffSets.IsCreated() )
        m_arrOffSets.Destroy();

    m_bFinalized = false;

    m_iRuneSlot = INVALID_OFFSET;
    m_bIsForced = false;

    for( i = 0; i < RUNE_SET_COUNT; ++i )
        m_arrAvailableMainSets[i] = false;

    for( i = 0; i < RUNE_SET_COUNT; ++i )
        m_arrAvailableOffSets[i] = false;

    m_bEnumerating = false;
    m_iEnumMainSetIndex = INVALID_OFFSET;
    m_iEnumOffSetIndex = INVALID_OFFSET;
}

Void RuneSlotPool::Enumerate()
{
    Assert( m_bFinalized );
    Assert( !m_bEnumerating );

    m_bEnumerating = true;
    m_iEnumMainSetIndex = 0;
    m_iEnumOffSetIndex = 0;
}
RuneID RuneSlotPool::EnumerateNextRune( Float * outRating )
{
    Assert( m_bFinalized );
    Assert( m_bEnumerating );

    Bool bMainSetEnd = ( m_iEnumMainSetIndex >= m_arrMainSets.Count() );
    Bool bOffSetEnd = ( m_iEnumOffSetIndex >= m_arrOffSets.Count() );

    // End of enumeration
    if ( bMainSetEnd && bOffSetEnd ) {
        m_bEnumerating = false;
        m_iEnumMainSetIndex = INVALID_OFFSET;
        m_iEnumOffSetIndex = INVALID_OFFSET;
        return INVALID_OFFSET;
    }

    // Only Main Set available case
    if ( bOffSetEnd ) {
        const RunePoolEntry & hEntry = m_arrMainSets[m_iEnumMainSetIndex];
        ++m_iEnumMainSetIndex;
        if ( outRating != NULL )
            *outRating = hEntry.fRating;
        return hEntry.iRuneID;
    }

    // Only Off Set available case
    if ( bMainSetEnd ) {
        const RunePoolEntry & hEntry = m_arrOffSets[m_iEnumOffSetIndex];
        ++m_iEnumOffSetIndex;
        if ( outRating != NULL )
            *outRating = hEntry.fRating;
        return hEntry.iRuneID;
    }

    // Both available, pick highest rating
    const RunePoolEntry & hMainEntry = m_arrMainSets[m_iEnumMainSetIndex];
    const RunePoolEntry & hOffEntry = m_arrOffSets[m_iEnumOffSetIndex];

    // Next is Main case
    if ( hMainEntry.fRating >= hOffEntry.fRating ) {
        ++m_iEnumMainSetIndex;
        if ( outRating != NULL )
            *outRating = hMainEntry.fRating;
        return hMainEntry.iRuneID;
    }

    // Next is Off case
    ++m_iEnumOffSetIndex;
    if ( outRating != NULL )
        *outRating = hOffEntry.fRating;
    return hOffEntry.iRuneID;
}

