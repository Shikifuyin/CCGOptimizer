/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/HeroInventory.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Hero Inventory Manager
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// HeroInventory implementation
inline UInt HeroInventory::GetHeroCount() const {
    return m_mapHeroInventory.Count();
}
inline const Hero * HeroInventory::GetHero( HeroID iHeroID ) const {
    Assert( m_mapHeroInventory.Contains(iHeroID) );
    return &( m_mapHeroInventory[iHeroID] );
}
inline Hero * HeroInventory::GetHero( HeroID iHeroID ) {
    Assert( m_mapHeroInventory.Contains(iHeroID) );
    return &( m_mapHeroInventory[iHeroID] );
}

inline Void HeroInventory::UnselectAllGearSets() {
    HeroMap::Iterator it = m_mapHeroInventory.Begin();
    while( !(it.IsNull()) ) {
        it.GetItemPtr()->UnselectGearSet();
        ++it;
    }
}

/////////////////////////////////////////////////////////////////////////////////

inline HeroID HeroInventory::_CreateHero( const GChar * strName, HeroRank iRank, UInt iLevel, Bool bEvolved, HeroSanctify iSanctify ) {
    HeroID iHeroID = _AllocateHeroID();
    m_mapHeroInventory.Insert( iHeroID, Hero(
        iHeroID, strName, iRank, iLevel, bEvolved, iSanctify
    ) );
    return iHeroID;
}
inline Void HeroInventory::_DestroyHero( HeroID iHeroID ) {
    Assert( m_mapHeroInventory.Contains(iHeroID) );
    m_mapHeroInventory.Remove( iHeroID );
}
inline Void HeroInventory::_DestroyAllHeroes() {
    m_iNextFreeHeroID = 0;
    m_mapHeroInventory.Clear();
}

inline Void HeroInventory::_DetachAll() {
    HeroMap::Iterator it = m_mapHeroInventory.Begin();
    while( !(it.IsNull()) ) {
        it.GetItemPtr()->_DetachAllGearSets();
        ++it;
    }
}

inline HeroID HeroInventory::_AllocateHeroID() {
    Assert( m_iNextFreeHeroID < INVALID_OFFSET );
    HeroID iHeroID = m_iNextFreeHeroID;
    ++m_iNextFreeHeroID;
    return iHeroID;
}

