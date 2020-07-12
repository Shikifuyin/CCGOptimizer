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
    return ( (m_arrMainSets.Count() + m_arrOffSets.Count()) == 0 );
}
inline UInt RuneSlotPool::GetTotalCount() const {
    Assert( m_bFinalized );
    return ( m_arrMainSets.Count() + m_arrOffSets.Count() );
}

inline UInt RuneSlotPool::GetMainSetsCount() const {
    Assert( m_bFinalized );
    return m_arrMainSets.Count();
}
inline UInt RuneSlotPool::GetOffSetsCount() const {
    Assert( m_bFinalized );
    return m_arrOffSets.Count();
}

inline Bool RuneSlotPool::IsSetAvailable( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    return ( m_arrAvailableMainSets[iRuneSet] || m_arrAvailableOffSets[iRuneSet] );
}
inline Bool RuneSlotPool::IsMainSetAvailable( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    return m_arrAvailableMainSets[iRuneSet];
}
inline Bool RuneSlotPool::IsOffSetAvailable( RuneSet iRuneSet ) const {
    Assert( m_bFinalized );
    Assert( iRuneSet < RUNE_SET_COUNT );
    return m_arrAvailableOffSets[iRuneSet];
}

inline Float RuneSlotPool::GetMainSetBestRating() const {
    Assert( m_bFinalized );
    return m_arrMainSets[0].fRating;
}
inline Float RuneSlotPool::GetOffSetBestRating() const {
    Assert( m_bFinalized );
    return m_arrOffSets[0].fRating;
}

inline RuneID RuneSlotPool::GetMainSetRune( UInt iIndex, Float * outRating ) const {
    Assert( m_bFinalized );
    Assert( iIndex < m_arrMainSets.Count() );
    if ( outRating != NULL )
        *outRating = m_arrMainSets[iIndex].fRating;
    return m_arrMainSets[iIndex].iRuneID;
}
inline RuneID RuneSlotPool::GetOffSetRune( UInt iIndex, Float * outRating ) const {
    Assert( m_bFinalized );
    Assert( iIndex < m_arrOffSets.Count() );
    if ( outRating != NULL )
        *outRating = m_arrOffSets[iIndex].fRating;
    return m_arrOffSets[iIndex].iRuneID;
}

inline Void RuneSlotPool::SetSlot( UInt iSlot ) {
    Assert( !m_bFinalized );
    m_iRuneSlot = iSlot;
}
inline Void RuneSlotPool::SetForced() {
    Assert( !m_bFinalized );
    m_bIsForced = true;
}

inline Bool RuneSlotPool::IsEnumerating() const {
    Assert( m_bFinalized );
    return m_bEnumerating;
}

/////////////////////////////////////////////////////////////////////////////////

inline Int RuneSlotPool::_CompareRunePoolEntries( const RunePoolEntry & hLeft, const RunePoolEntry & hRight ) {
    if ( hLeft.fRating > hRight.fRating )
        return +1;
    if ( hLeft.fRating < hRight.fRating )
        return -1;
    return 0;
}
