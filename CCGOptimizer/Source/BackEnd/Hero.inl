/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Hero.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Hero Representation
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Hero implementation
inline HeroID Hero::GetID() const {
	return m_iHeroID;
}
inline const GChar * Hero::GetName() const {
	return m_strName;
}
inline HeroFaction Hero::GetFaction() const {
	return m_iFaction;
}
inline HeroRank Hero::GetRank() const {
    return m_iRank;
}
inline UInt Hero::GetLevel() const {
    return m_iLevel;
}
inline Bool Hero::IsEvolved() const {
    return m_bEvolved;
}
inline Bool Hero::IsSanctified() const {
    return ( m_iSanctify != HERO_SANCTIFY_NONE );
}
inline HeroSanctify Hero::GetSanctification() const {
	return m_iSanctify;
}
inline Void Hero::SetSanctification( HeroSanctify iSanctify ) {
	Assert( iSanctify < HERO_SANCTIFY_COUNT );
	m_iSanctify = iSanctify;
}

inline UInt Hero::GetGearSetCount() const {
	return m_arrAttachedGearSets.Count();
}
inline GearSetID Hero::GetGearSet( UInt iIndex ) const {
	Assert( iIndex < m_arrAttachedGearSets.Count() );
	return m_arrAttachedGearSets[iIndex];
}
inline Bool Hero::HasGearSet( GearSetID iGearSetID ) const {
	return ( m_arrAttachedGearSets.Search(iGearSetID) != INVALID_OFFSET );
}

inline GearSetID Hero::GetSelectedGearSet() const {
	return m_iSelectedGearSet;
}
inline Void Hero::SelectGearSet( GearSetID iGearSetID ) {
	Assert( m_arrAttachedGearSets.Search(iGearSetID) != INVALID_OFFSET );
	m_iSelectedGearSet = iGearSetID;
}
inline Void Hero::UnselectGearSet() {
	m_iSelectedGearSet = INVALID_OFFSET;
}

/////////////////////////////////////////////////////////////////////////////////

inline UInt Hero::_AttachGearSet( GearSetID iGearSetID ) {
	UInt iIndex = m_arrAttachedGearSets.Search( iGearSetID );
	if ( iIndex != INVALID_OFFSET )
		return iIndex;
	iIndex = m_arrAttachedGearSets.Count();
	m_arrAttachedGearSets.Push( iGearSetID );
	return iIndex;
}
inline Void Hero::_DetachGearSet( GearSetID iGearSetID ) {
	UInt iIndex = m_arrAttachedGearSets.Search( iGearSetID );
	if ( iIndex == INVALID_OFFSET )
		return;
	if ( m_iSelectedGearSet == iGearSetID )
		m_iSelectedGearSet = INVALID_OFFSET;
	m_arrAttachedGearSets.Remove( iIndex, NULL, 1 );
}
inline Void Hero::_DetachAllGearSets() {
	m_iSelectedGearSet = INVALID_OFFSET;
	m_arrAttachedGearSets.Clear();
}
