/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Optimizer/RuneSlotPool.inl
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
// RuneSlotPool implementation
inline UInt RuneSlotPool::GetSlot() const {
    Assert( m_bFinalized );
    return m_iRuneSlot;
}
inline Bool RuneSlotPool::IsForced() const {
    Assert( m_bFinalized );
    return m_bIsForced;
}

inline Bool RuneSlotPool::IsEmpty() const {
    Assert( m_bFinalized );
    return ( (m_iMainSetsTotalCount + m_iOffSetsTotalCount) == 0 );
}
inline UInt RuneSlotPool::GetTotalCount() const {
    Assert( m_bFinalized );
    return ( m_iMainSetsTotalCount + m_iOffSetsTotalCount );
}

inline Bool RuneSlotPool::IsSetAvailable( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    return ( m_arrAvailableMainSets[iRuneSet] || m_arrAvailableOffSets[iRuneSet] );
}

inline UInt RuneSlotPool::GetMainSetsTotalCount() const {
    Assert( m_bFinalized );
    return m_iMainSetsTotalCount;
}

inline Bool RuneSlotPool::IsMainSetAvailable( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    return m_arrAvailableMainSets[iRuneSet];
}
inline Float RuneSlotPool::GetMainSetBestRating( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    Assert( m_arrAvailableMainSets[iRuneSet] );
    return (m_arrMainSets[iRuneSet])[0].fRating;
}

inline UInt RuneSlotPool::GetMainSetCount( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    Assert( m_arrAvailableMainSets[iRuneSet] );
    return m_arrMainSets[iRuneSet].Count();
}
inline RuneID RuneSlotPool::GetMainSetRune( RuneSet iRuneSet, UInt iIndex, Float * outRating ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    Assert( m_arrAvailableMainSets[iRuneSet] );
    Assert( iIndex < m_arrMainSets[iRuneSet].Count() );
    if ( outRating != NULL )
        *outRating = (m_arrMainSets[iRuneSet])[iIndex].fRating;
    return (m_arrMainSets[iRuneSet])[iIndex].iRuneID;
}

inline UInt RuneSlotPool::GetOffSetsTotalCount() const {
    Assert( m_bFinalized );
    return m_iOffSetsTotalCount;
}

inline Bool RuneSlotPool::IsOffSetAvailable( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    return m_arrAvailableOffSets[iRuneSet];
}
inline Float RuneSlotPool::GetOffSetBestRating( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    Assert( m_arrAvailableOffSets[iRuneSet] );
    return (m_arrOffSets[iRuneSet])[0].fRating;
}

inline UInt RuneSlotPool::GetOffSetCount( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    Assert( m_arrAvailableOffSets[iRuneSet] );
    return m_arrOffSets[iRuneSet].Count();
}
inline RuneID RuneSlotPool::GetOffSetRune( RuneSet iRuneSet, UInt iIndex, Float * outRating ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    Assert( m_arrAvailableOffSets[iRuneSet] );
    Assert( iIndex < m_arrOffSets[iRuneSet].Count() );
    if ( outRating != NULL )
        *outRating = (m_arrOffSets[iRuneSet])[iIndex].fRating;
    return (m_arrOffSets[iRuneSet])[iIndex].iRuneID;
}

inline Void RuneSlotPool::SetSlot( UInt iSlot ) {
    Assert( !m_bFinalized );
    m_iRuneSlot = iSlot;
}
inline Void RuneSlotPool::SetForced() {
    Assert( !m_bFinalized );
    m_bIsForced = true;
}

/////////////////////////////////////////////////////////////////////////////////

inline Int RuneSlotPool::_CompareRunePoolEntries( const RunePoolEntry & hLeft, const RunePoolEntry & hRight ) {
    if ( hLeft.fRating > hRight.fRating )
        return +1;
    if ( hLeft.fRating < hRight.fRating )
        return -1;
    return 0;
}
