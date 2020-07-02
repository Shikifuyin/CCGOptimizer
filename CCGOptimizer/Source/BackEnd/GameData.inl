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

inline const GChar * GameData::GetRuneSetName( RuneSet iRuneSet ) const {
    static const GChar * s_arrNames[RUNE_SET_COUNT] = {
        TEXT("Blessing"),
        TEXT("Attack"),
        TEXT("Defense"),
        TEXT("Agile"),
        TEXT("Wild"),
        TEXT("Destruction"),
        TEXT("Focus"),
        TEXT("Stalwart"),
        TEXT("Desperation"),
        TEXT("Drain"),
        TEXT("Frenzy"),
        TEXT("Berserk"),
        TEXT("Counter"),
        TEXT("Guard"),
        TEXT("Immunity"),
        TEXT("Ravage"),
        TEXT("Prayer"),
        TEXT("Conflict"),
        TEXT("Unity"),
        TEXT("Hit"),
        TEXT("Fortitude")
    };
    Assert( iRuneSet < RUNE_SET_COUNT );
    return s_arrNames[iRuneSet];
}
inline const GChar * GameData::GetRuneRankName( RuneRank iRuneRank ) const {
    static const GChar * s_arrNames[RUNE_RANK_COUNT] = {
        TEXT("1-Star"),
        TEXT("2-Stars"),
        TEXT("3-Stars"),
        TEXT("4-Stars"),
        TEXT("5-Stars"),
        TEXT("6-Stars")
    };
    Assert( iRuneRank < RUNE_RANK_COUNT );
    return s_arrNames[iRuneRank];
}
inline const GChar * GameData::GetRuneQualityName( RuneQuality iRuneQuality ) const {
    static const GChar * s_arrNames[RUNE_QUALITY_COUNT] = {
        TEXT("Common"),
        TEXT("Magic"),
        TEXT("Rare"),
        TEXT("Heroic"),
        TEXT("Legendary")
    };
    Assert( iRuneQuality < RUNE_QUALITY_COUNT );
    return s_arrNames[iRuneQuality];
}
inline const GChar * GameData::GetRuneStatName( RuneStat iRuneStat ) const {
    static const GChar * s_arrNames[RUNE_STAT_COUNT] = {
        TEXT("HP"),
        TEXT("HP%"),
        TEXT("Attack"),
        TEXT("Attack%"),
        TEXT("Defense"),
        TEXT("Defense%"),
        TEXT("Speed"),
        TEXT("CritRate"),
        TEXT("CritDmg"),
        TEXT("Hit"),
        TEXT("Resistance")
    };
    Assert( iRuneStat < RUNE_STAT_COUNT );
    return s_arrNames[iRuneStat];
}

inline const GChar * GameData::GetHeroFactionName( HeroFaction iHeroFaction ) const {
    static const GChar * s_arrNames[HERO_FACTION_COUNT] = {
        TEXT("Lawful"),
        TEXT("Chaotic"),
        TEXT("Evil"),
        TEXT("Light"),
        TEXT("Dark")
    };
    Assert( iHeroFaction < HERO_FACTION_COUNT );
    return s_arrNames[iHeroFaction];
}
inline const GChar * GameData::GetHeroRankName( HeroRank iHeroRank ) const {
    static const GChar * s_arrNames[HERO_RANK_COUNT] = {
        TEXT("1-Star"),
        TEXT("2-Stars"),
        TEXT("3-Stars"),
        TEXT("4-Stars"),
        TEXT("5-Stars"),
        TEXT("6-Stars")
    };
    Assert( iHeroRank < HERO_RANK_COUNT );
    return s_arrNames[iHeroRank];
}
inline const GChar * GameData::GetHeroStatName( HeroStat iHeroStat ) const {
    static const GChar * s_arrNames[HERO_STAT_COUNT] = {
        TEXT("HP"),
        TEXT("Attack"),
        TEXT("Defense"),
        TEXT("Speed"),
        TEXT("CritRate"),
        TEXT("CritDmg"),
        TEXT("Hit"),
        TEXT("Resistance")
    };
    Assert( iHeroStat < HERO_STAT_COUNT );
    return s_arrNames[iHeroStat];
}
inline const GChar * GameData::GetHeroSanctifyName( HeroSanctify iHeroSanctify ) const {
    static const GChar * s_arrNames[HERO_SANCTIFY_COUNT] = {
        TEXT("None"),
        TEXT("HP"),
        TEXT("Attack"),
        TEXT("Defense"),
        TEXT("Hit"),
        TEXT("Resistance")
    };
    Assert( iHeroSanctify < HERO_SANCTIFY_COUNT );
    return s_arrNames[iHeroSanctify];
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
    return m_arrRuneMainStatsValues[iRuneStat * (RUNE_RANK_COUNT * (RUNE_MAX_LEVEL+1)) + iRank * (RUNE_MAX_LEVEL+1) + iLevel];
}

inline UInt GameData::GetRuneRandomStatCount( RuneQuality iQuality, UInt iLevel ) const {
    Assert( iQuality < RUNE_QUALITY_COUNT );
    Assert( iLevel <= RUNE_MAX_LEVEL );
    return m_arrRuneRandomStatCount[iLevel * RUNE_QUALITY_COUNT + iQuality];
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
inline UInt GameData::GetHeroRankMinLevel( const GChar * strHeroName, HeroRank iRank ) const {
    Assert( iRank < HERO_RANK_COUNT );
    HeroRank iNaturalRank = GetHeroNaturalRank(strHeroName);
    Assert( iRank >= iNaturalRank );
    if ( iRank == iNaturalRank )
        return 1;
    return GetHeroRankMaxLevel( (HeroRank)(iRank - 1) );
}
inline UInt GameData::GetHeroSanctifyBonus( HeroSanctify iSanctify ) const {
    Assert( iSanctify < HERO_SANCTIFY_COUNT );
    return m_arrHeroSanctifyBonus[iSanctify];
}

inline UInt GameData::GetHeroDataCount() const {
    return m_mapHeroData.Count();
}
inline GameData::HeroDataMap::Iterator GameData::EnumHeroData() const {
    return m_mapHeroData.Begin();
}

inline Bool GameData::IsHeroNameValid( const GChar * strHeroName ) const {
    HeroName hTemp;
    StringFn->NCopy( hTemp.strName, strHeroName, GAMEDATA_NAMES_MAX_LENGTH - 1 );
    return m_mapHeroData.Contains( hTemp );
}
inline HeroFaction GameData::GetHeroFaction( const GChar * strHeroName ) const {
    HeroName hTemp;
    StringFn->NCopy( hTemp.strName, strHeroName, GAMEDATA_NAMES_MAX_LENGTH - 1 );
    return m_mapHeroData[hTemp].iFaction;
}
inline HeroRank GameData::GetHeroNaturalRank( const GChar * strHeroName ) const {
    HeroName hTemp;
    StringFn->NCopy( hTemp.strName, strHeroName, GAMEDATA_NAMES_MAX_LENGTH - 1 );
    return m_mapHeroData[hTemp].iNaturalRank;
}
inline UInt GameData::GetHeroBaseStat( const GChar * strHeroName, HeroStat iHeroStat, HeroRank iRank, UInt iLevel, Bool bEvolved ) const {
    Assert( iHeroStat < HERO_STAT_COUNT );
    Assert( iRank < HERO_RANK_COUNT );
    Assert( iLevel <= m_arrHeroRankMaxLevel[iRank] );
    HeroName hTemp;
    StringFn->NCopy( hTemp.strName, strHeroName, GAMEDATA_NAMES_MAX_LENGTH - 1 );
    if ( bEvolved )
        return m_mapHeroData[hTemp].arrBaseStatsEvolved[ iHeroStat * (HERO_RANK_COUNT * HERO_MAX_LEVEL) + iRank * HERO_MAX_LEVEL + iLevel-1 ];
    else
        return m_mapHeroData[hTemp].arrBaseStats[ iHeroStat * (HERO_RANK_COUNT * HERO_MAX_LEVEL) + iRank * HERO_MAX_LEVEL + iLevel-1 ];
}

/////////////////////////////////////////////////////////////////////////////////

inline const GChar * GameData::_GetRuneStatNameXML( RuneStat iRuneStat ) const {
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
inline const GChar * GameData::_GetHeroStatNameXML( HeroStat iHeroStat ) const {
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

