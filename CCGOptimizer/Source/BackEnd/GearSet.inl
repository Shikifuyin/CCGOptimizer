/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/GearSet.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Gear Sets
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// GearSet implementation
inline GearSetID GearSet::GetID() const {
    return m_iGearSetID;
}

inline const GChar * GearSet::GetName() const {
	return m_strName;
}

inline RuneID GearSet::GetEquippedRune( UInt iSlot ) const {
    Assert( iSlot < RUNE_SLOT_COUNT );
    return m_arrEquippedRunes[iSlot];
}
inline UInt GearSet::HasEquippedRune( RuneID iRuneID ) const {
    for ( UInt iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
        if ( m_arrEquippedRunes[iSlot] == iRuneID )
            return iSlot;
    }
    return INVALID_OFFSET;
}

inline UInt GearSet::GetAttachedHeroCount() const {
    return m_iAttachedHeroesCount;
}
inline HeroID GearSet::GetAttachedHero( UInt iIndex ) const {
    Assert( iIndex < m_iAttachedHeroesCount );
    return m_arrAttachedHeroes[iIndex];
}

inline Float GearSet::GetScoreEfficiency() const {
    return m_fScoreEfficiency;
}
inline Float GearSet::GetScoreDamage() const {
    return m_fScoreDamage;
}
inline Float GearSet::GetScoreTanking() const {
    return m_fScoreTanking;
}

/////////////////////////////////////////////////////////////////////////////////

inline Void GearSet::_EquipRune( RuneID iRuneID, UInt iSlot ) {
    Assert( iSlot < RUNE_SLOT_COUNT );
    m_arrEquippedRunes[iSlot] = iRuneID;
    _ComputeScores();
}
inline Void GearSet::_UnequipRune( UInt iSlot ) {
    Assert( iSlot < RUNE_SLOT_COUNT );
    m_arrEquippedRunes[iSlot] = INVALID_OFFSET;
    _ComputeScores();
}
inline Void GearSet::_UnequipAllRunes() {
    for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
        m_arrEquippedRunes[i] = INVALID_OFFSET;
    _ComputeScores();
}

inline Void GearSet::_DetachFromAllHeroes() {
    m_iAttachedHeroesCount = 0;
}
