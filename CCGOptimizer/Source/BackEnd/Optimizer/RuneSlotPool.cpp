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

    m_iMainSetsTotalCount = 0;
    for( i = 0; i < RUNE_SET_COUNT; ++i )
        m_arrAvailableMainSets[i] = false;

    m_iOffSetsTotalCount = 0;
    for( i = 0; i < RUNE_SET_COUNT; ++i )
        m_arrAvailableOffSets[i] = false;
}
RuneSlotPool::~RuneSlotPool()
{
    Assert( m_bFinalized );

    for( UInt i = 0; i < RUNE_SET_COUNT; ++i ) {
        if ( m_arrAvailableMainSets[i] )
            m_arrMainSets[i].Destroy();
        if ( m_arrAvailableOffSets[i] )
            m_arrOffSets[i].Destroy();
    }   
}

Void RuneSlotPool::AddMainSetRune( RuneID iRuneID, Float fRating )
{
    Assert( m_iRuneSlot != INVALID_OFFSET );
    Assert( !m_bFinalized );

    const Rune * pRune = CCGOPFn->GetRune( iRuneID );
    Assert( pRune->GetSlot() == m_iRuneSlot );

    RuneSet iSet = pRune->GetSet();
    if ( !(m_arrAvailableMainSets[iSet]) ) {
        m_arrAvailableMainSets[iSet] = true;
        m_arrMainSetsHeaps[iSet].SetComparator( _CompareRunePoolEntries );
        m_arrMainSetsHeaps[iSet].Create();
    }

    RunePoolEntry hEntry;
    hEntry.iRuneID = iRuneID;
    hEntry.fRating = fRating;
    m_arrMainSetsHeaps[iSet].Merge( hEntry );
}
Void RuneSlotPool::AddOffSetRune( RuneID iRuneID, Float fRating )
{
    Assert( m_iRuneSlot != INVALID_OFFSET );
    Assert( !m_bFinalized );

    const Rune * pRune = CCGOPFn->GetRune( iRuneID );
    Assert( pRune->GetSlot() == m_iRuneSlot );

    RuneSet iSet = pRune->GetSet();
    if ( !(m_arrAvailableOffSets[iSet]) ) {
        m_arrAvailableOffSets[iSet] = true;
        m_arrOffSetsHeaps[iSet].SetComparator( _CompareRunePoolEntries );
        m_arrOffSetsHeaps[iSet].Create();
    }

    RunePoolEntry hEntry;
    hEntry.iRuneID = iRuneID;
    hEntry.fRating = fRating;
    m_arrOffSetsHeaps[iSet].Merge( hEntry );
}
Void RuneSlotPool::FinalizeSorting()
{
    Assert( m_iRuneSlot != INVALID_OFFSET );
    Assert( !m_bFinalized );

    for( UInt i = 0; i < RUNE_SET_COUNT; ++i ) {
        if ( m_arrAvailableMainSets[i] ) {
            m_arrMainSets[i].Create();
            UInt iCount = 0;
            while( !(m_arrMainSetsHeaps[i].IsEmpty()) ) {
                RunePoolEntry hEntry;
                m_arrMainSetsHeaps[i].Extract( hEntry );
                m_arrMainSets[i].Push( hEntry );
                ++iCount;
            }
            m_arrMainSetsHeaps[i].Destroy();
            m_iMainSetsTotalCount += iCount;
        }
        if ( m_arrAvailableOffSets[i] ) {
            m_arrOffSets[i].Create();
            UInt iCount = 0;
            while( !(m_arrOffSetsHeaps[i].IsEmpty()) ) {
                RunePoolEntry hEntry;
                m_arrOffSetsHeaps[i].Extract( hEntry );
                m_arrOffSets[i].Push( hEntry );
                ++iCount;
            }
            m_arrOffSetsHeaps[i].Destroy();
            m_iOffSetsTotalCount += iCount;
        }
    }
        
    m_bFinalized = true;
}

Void RuneSlotPool::Reset()
{
    Assert( m_bFinalized );

    UInt i;

    for( i = 0; i < RUNE_SET_COUNT; ++i ) {
        if ( m_arrAvailableMainSets[i] )
            m_arrMainSets[i].Destroy();
        if ( m_arrAvailableOffSets[i] )
            m_arrOffSets[i].Destroy();
    }

    m_bFinalized = false;

    m_iRuneSlot = INVALID_OFFSET;
    m_bIsForced = false;

    m_iMainSetsTotalCount = 0;
    for( i = 0; i < RUNE_SET_COUNT; ++i )
        m_arrAvailableMainSets[i] = false;

    m_iOffSetsTotalCount = 0;
    for( i = 0; i < RUNE_SET_COUNT; ++i )
        m_arrAvailableOffSets[i] = false;
}
