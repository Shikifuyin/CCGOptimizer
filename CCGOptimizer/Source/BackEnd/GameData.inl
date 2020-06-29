/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/GameData.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Game-Specific Data
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : Requires more investigation ...
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// GameData implementation
inline GameData * GameData::GetInstance() {
	static GameData * s_pInstance = NULL;
    if ( s_pInstance == NULL )
        s_pInstance = New() GameData();
	return s_pInstance;
}

inline const GChar * GameData::GetRuneStatName( RuneStat iRuneStat ) const {
    static const GChar * s_arrNames[RUNE_STAT_COUNT] = {
        TEXT("HP_Flat"),
        TEXT("HP_Percent"),
        TEXT("ATT_Flat"),
        TEXT("ATT_Percent"),
        TEXT("DEF_Flat"),
        TEXT("DEF_Percent"),
        TEXT("SPD"),
        TEXT("CRITRATE"),
        TEXT("CRITDMG"),
        TEXT("HIT"),
        TEXT("RES")
    };
    Assert( iRuneStat < RUNE_STAT_COUNT );
    return s_arrNames[iRuneStat];
}
inline const GChar * GameData::GetHeroStatName( HeroStat iHeroStat ) const {
    static const GChar * s_arrNames[HERO_STAT_COUNT] = {
        TEXT("HP"),
        TEXT("ATT"),
        TEXT("DEF"),
        TEXT("SPD"),
        TEXT("CRITRATE"),
        TEXT("CRITDMG"),
        TEXT("HIT"),
        TEXT("RES")
    };
    Assert( iHeroStat < HERO_STAT_COUNT );
    return s_arrNames[iHeroStat];
}

inline UInt GameData::GetRuneSetSize( RuneSet iRuneSet ) const {
    Assert( iRuneSet < RUNE_SET_COUNT );
    return m_arrRuneSetSizes[iRuneSet];
}

inline Bool GameData::IsRuneMainStatAllowed( RuneStat iRuneStat, UInt iSlot ) const {
    Assert( iRuneStat < RUNE_STAT_COUNT );
    Assert( iSlot < RUNE_SLOT_COUNT );
    return m_arrRuneMainStatsAllowed[iRuneStat * RUNE_SLOT_COUNT + iSlot];
}
inline UInt GameData::GetRuneMainStatValue( RuneStat iRuneStat, RuneRank iRank, UInt iLevel ) const {
    Assert( iRuneStat < RUNE_STAT_COUNT );
    Assert( iRank < RUNE_RANK_COUNT );
    Assert( iLevel <= RUNE_MAX_LEVEL );
    return m_arrRuneMainStatsValues[iRuneStat * (RUNE_RANK_COUNT * RUNE_MAX_LEVEL) + iRank * (RUNE_MAX_LEVEL+1) + iLevel];
}

inline UInt GameData::GetRuneStatMinRoll( RuneStat iRuneStat, RuneRank iRank ) const {
    Assert( iRuneStat < RUNE_STAT_COUNT );
    Assert( iRank < RUNE_RANK_COUNT );
    return m_arrRuneSubStatsMinRoll[iRuneStat * RUNE_RANK_COUNT + iRank];
}
inline UInt GameData::GetRuneStatMaxRoll( RuneStat iRuneStat, RuneRank iRank ) const {
    Assert( iRuneStat < RUNE_STAT_COUNT );
    Assert( iRank < RUNE_RANK_COUNT );
    return m_arrRuneSubStatsMaxRoll[iRuneStat * RUNE_RANK_COUNT + iRank];
}
    
inline UInt GameData::GetHeroRankMaxLevel( HeroRank iRank ) const {
    Assert( iRank < HERO_RANK_COUNT );
    return m_arrHeroRankMaxLevel[iRank];
}
inline UInt GameData::GetHeroSanctifyBonus( HeroSanctify iSanctify ) const {
    Assert( iSanctify < HERO_SANCTIFY_COUNT );
    return m_arrHeroSanctifyBonus[iSanctify];
}

inline Bool GameData::IsHeroNameValid( const GChar * strHeroName ) const {
    return m_mapHeroData.Contains( strHeroName );
}
inline HeroFaction GameData::GetHeroFaction( const GChar * strHeroName ) const {
    Assert( m_mapHeroData.Contains(strHeroName) );
    return m_mapHeroData[strHeroName].iFaction;
}
inline HeroRank GameData::GetHeroNaturalRank( const GChar * strHeroName ) const {
    Assert( m_mapHeroData.Contains(strHeroName) );
    return m_mapHeroData[strHeroName].iNaturalRank;
}
inline UInt GameData::GetHeroBaseStat( const GChar * strHeroName, HeroStat iHeroStat, HeroRank iRank, UInt iLevel, Bool bEvolved ) const {
    Assert( m_mapHeroData.Contains(strHeroName) );
    Assert( iHeroStat < HERO_STAT_COUNT );
    Assert( iRank < HERO_RANK_COUNT );
    Assert( iLevel <= m_arrHeroRankMaxLevel[iRank] );
    if ( bEvolved )
        return m_mapHeroData[strHeroName].arrBaseStatsEvolved[ iHeroStat * (HERO_RANK_COUNT * HERO_MAX_LEVEL) + iRank * HERO_MAX_LEVEL + iLevel-1 ];
    else
        return m_mapHeroData[strHeroName].arrBaseStats[ iHeroStat * (HERO_RANK_COUNT * HERO_MAX_LEVEL) + iRank * HERO_MAX_LEVEL + iLevel-1 ];
}
