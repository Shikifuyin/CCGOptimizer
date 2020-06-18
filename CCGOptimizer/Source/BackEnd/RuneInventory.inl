/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/RuneInventory.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Inventory Manager
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// RuneInventory implementation
inline UInt RuneInventory::GetRuneCount() const {
    return m_mapRuneInventory.Count();
}
inline const Rune * RuneInventory::GetRune( RuneID iRuneID ) const {
    Assert( m_mapRuneInventory.Contains(iRuneID) );
    return &( m_mapRuneInventory[iRuneID] );
}
inline Rune * RuneInventory::GetRune( RuneID iRuneID ) {
    Assert( m_mapRuneInventory.Contains(iRuneID) );
    return &( m_mapRuneInventory[iRuneID] );
}

// Rune Locks
inline Void RuneInventory::LockAll() {
    RuneMap::Iterator it = m_mapRuneInventory.Begin();
    while( !(it.IsNull()) ) {
        it.GetItemPtr()->Lock();
        ++it;
    }
}
inline Void RuneInventory::UnlockAll() {
    RuneMap::Iterator it = m_mapRuneInventory.Begin();
    while( !(it.IsNull()) ) {
        it.GetItemPtr()->Unlock();
        ++it;
    }
}

/////////////////////////////////////////////////////////////////////////////////

inline RuneID RuneInventory::_CreateRune( UInt iSlot, RuneSet iSet, RuneRank iRank, RuneQuality iQuality, UInt iLevel,
                            RuneStat iMainStat, RuneStat iInnateStat, UInt iInnateStatValue,
                            UInt iRandomStatCount, const RuneStat * arrRandomStats, const UInt * arrRandomStatValues ) {
    RuneID iRuneID = _AllocateRuneID();
    m_mapRuneInventory.Insert( iRuneID, Rune(
        iRuneID, iSlot, iSet, iRank, iQuality, iLevel, iMainStat, iInnateStat, iInnateStatValue,
        iRandomStatCount, arrRandomStats, arrRandomStatValues
    ) );
    return iRuneID;
}
inline Void RuneInventory::_DestroyRune( RuneID iRuneID ) {
    Assert( m_mapRuneInventory.Contains(iRuneID) );
    m_mapRuneInventory.Remove( iRuneID );
}
inline Void RuneInventory::_DestroyAllRunes() {
    m_iNextFreeRuneID = 0;
    m_mapRuneInventory.Clear();
}

inline Void RuneInventory::_UnequipAll() {
    RuneMap::Iterator it = m_mapRuneInventory.Begin();
    while( !(it.IsNull()) ) {
        it.GetItemPtr()->_UnequipFromAllGearSets();
        ++it;
    }
}

inline RuneID RuneInventory::_AllocateRuneID() {
    Assert( m_iNextFreeRuneID < INVALID_OFFSET );
    RuneID iRuneID = m_iNextFreeRuneID;
    ++m_iNextFreeRuneID;
    return iRuneID;
}

