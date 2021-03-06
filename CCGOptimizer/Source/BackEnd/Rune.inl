/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Rune.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Representation
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Rune implementation
inline RuneID Rune::GetID() const {
    return m_iRuneID;
}
inline UInt Rune::GetSlot() const {
    return m_iSlot;
}
inline RuneSet Rune::GetSet() const {
    return m_iSet;
}
inline RuneRank Rune::GetRank() const {
    return m_iRank;
}
inline RuneQuality Rune::GetQuality() const {
    return m_iQuality;
}
inline UInt Rune::GetLevel() const {
    return m_iLevel;
}

inline Bool Rune::HasMainStat( RuneStat iRuneStat ) const {
    return ( m_iMainStat == iRuneStat );
}
inline RuneStat Rune::GetMainStat() const {
    return m_iMainStat;
}
inline UInt Rune::GetMainStatValue() const {
    return GameDataFn->GetRuneMainStatValue( m_iMainStat, m_iRank, m_iLevel );
}

inline Bool Rune::HasInnateStat( RuneStat iRuneStat ) const {
    return ( m_iInnateStat == iRuneStat );
}
inline RuneStat Rune::GetInnateStat() const {
    return m_iInnateStat;
}
inline UInt Rune::GetInnateStatValue() const {
    return m_iInnateStatValue;
}

inline Bool Rune::HasRandomStat( RuneStat iRuneStat ) const {
    return ( m_arrRandomStatValues[iRuneStat] != 0 );
}
inline UInt Rune::GetRandomStatCount() const {
    return m_iRandomStatCount;
}
inline RuneStat Rune::GetRandomStat( UInt iIndex ) const {
    Assert( iIndex < m_iRandomStatCount );
    return m_arrRandomStats[iIndex];
}
inline UInt Rune::GetRandomStatValue( RuneStat iRuneStat ) const {
    Assert( iRuneStat < RUNE_STAT_COUNT );
    return m_arrRandomStatValues[iRuneStat];
}

inline Bool Rune::HasSubStat( RuneStat iRuneStat ) const {
    if ( m_iInnateStat == iRuneStat )
        return true;
    return ( m_arrRandomStatValues[iRuneStat] != 0 );
}
inline UInt Rune::GetSubStatValue( RuneStat iRuneStat ) const {
    Assert( iRuneStat < RUNE_STAT_COUNT );
    if ( m_iInnateStat == iRuneStat )
        return m_iInnateStatValue;
    return ( m_arrRandomStatValues[iRuneStat] );
}

inline Bool Rune::IsLocked() const {
    return m_bLocked;
}
inline Void Rune::Lock() {
    m_bLocked = true;
}
inline Void Rune::Unlock() {
    m_bLocked = false;
}

inline Bool Rune::IsEquipped() const {
    return ( m_iEquippedGearSetsCount > 0 );
}
inline UInt Rune::GetGearSetCount() const {
    return m_iEquippedGearSetsCount;
}
inline GearSetID Rune::GetGearSet( UInt iIndex ) const {
    Assert( iIndex < m_iEquippedGearSetsCount );
    return m_arrEquippedGearSets[iIndex];
}

inline Float Rune::GetScoreEfficiency() const {
    return m_fScoreEfficiency;
}
inline Float Rune::GetScoreDamage() const {
    return m_fScoreDamage;
}
inline Float Rune::GetScoreTanking() const {
    return m_fScoreTanking;
}

/////////////////////////////////////////////////////////////////////////////////

inline Void Rune::_UnequipFromAllGearSets() {
    m_iEquippedGearSetsCount = 0;
}

