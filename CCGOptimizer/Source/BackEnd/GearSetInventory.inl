/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/GearSetInventory.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSet Inventory Manager
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// GearSetInventory implementation
inline UInt GearSetInventory::GetGearSetCount() const {
    return m_mapGearSetInventory.Count();
}
inline const GearSet * GearSetInventory::GetGearSet( GearSetID iGearSetID ) const {
    Assert( m_mapGearSetInventory.Contains(iGearSetID) );
    return &( m_mapGearSetInventory[iGearSetID] );
}
inline GearSet * GearSetInventory::GetGearSet( GearSetID iGearSetID ) {
    Assert( m_mapGearSetInventory.Contains(iGearSetID) );
    return &( m_mapGearSetInventory[iGearSetID] );
}

/////////////////////////////////////////////////////////////////////////////////

inline GearSetID GearSetInventory::_CreateGearSet( const GChar * strName ) {
    GearSetID iGearSetID = _AllocateGearSetID();
    m_mapGearSetInventory.Insert( iGearSetID, GearSet(
        iGearSetID, strName
    ) );
    return iGearSetID;
}
inline Void GearSetInventory::_DestroyGearSet( GearSetID iGearSetID ) {
    Assert( m_mapGearSetInventory.Contains(iGearSetID) );
    m_mapGearSetInventory.Remove( iGearSetID );
}
inline Void GearSetInventory::_DestroyAllGearSets() {
    m_iNextFreeGearSetID = 0;
    m_mapGearSetInventory.Clear();
}

inline Void GearSetInventory::_UnequipAll() {
    GearSetMap::Iterator it = m_mapGearSetInventory.Begin();
    while( !(it.IsNull()) ) {
        it.GetItemPtr()->_UnequipAllRunes();
        ++it;
    }
}
inline Void GearSetInventory::_DetachAll() {
    GearSetMap::Iterator it = m_mapGearSetInventory.Begin();
    while( !(it.IsNull()) ) {
        it.GetItemPtr()->_DetachFromAllHeroes();
        ++it;
    }
}

inline GearSetID GearSetInventory::_AllocateGearSetID() {
    Assert( m_iNextFreeGearSetID < INVALID_OFFSET );
    GearSetID iGearSetID = m_iNextFreeGearSetID;
    ++m_iNextFreeGearSetID;
    return iGearSetID;
}

