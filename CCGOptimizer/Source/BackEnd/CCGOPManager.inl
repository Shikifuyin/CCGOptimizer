/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/CCGOPManager.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOP Main Interface
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// CCGOPManager implementation
inline CCGOPManager * CCGOPManager::GetInstance() {
	static CCGOPManager * s_pInstance = NULL;
    if ( s_pInstance == NULL )
        s_pInstance = New() CCGOPManager();
	return s_pInstance;
}

inline UInt CCGOPManager::GetRuneCount() const {
    return m_hRuneInventory.GetRuneCount();
}
inline const Rune * CCGOPManager::GetRune( RuneID iRuneID ) const {
    return m_hRuneInventory.GetRune( iRuneID );
}
inline Rune * CCGOPManager::GetRune( RuneID iRuneID ) {
    return m_hRuneInventory.GetRune( iRuneID );
}

inline RuneID CCGOPManager::CreateRune( UInt iSlot, RuneSet iSet, RuneRank iRank, RuneQuality iQuality, UInt iLevel,
                            RuneStat iMainStat, RuneStat iInnateStat, UInt iInnateStatValue,
                            UInt iRandomStatCount, const RuneStat * arrRandomStats, const UInt * arrRandomStatValues ) {
    return m_hRuneInventory._CreateRune(
        iSlot, iSet, iRank, iQuality, iLevel, iMainStat,
        iInnateStat, iInnateStatValue,
        iRandomStatCount, arrRandomStats, arrRandomStatValues
    );
}
inline Void CCGOPManager::DestroyRune( RuneID iRuneID ) {
    UnequipRuneFromAllGearSets( iRuneID );
    m_hRuneInventory._DestroyRune( iRuneID );
}
inline Void CCGOPManager::DestroyAllRunes() {
    UnequipAllRunes();
    m_hRuneInventory._DestroyAllRunes();
}

inline Void CCGOPManager::LockAllRunes() {
    m_hRuneInventory.LockAll();
}
inline Void CCGOPManager::UnlockAllRunes() {
    m_hRuneInventory.UnlockAll();
}

inline UInt CCGOPManager::GetHeroCount() const {
    return m_hHeroInventory.GetHeroCount();
}
inline const Hero * CCGOPManager::GetHero( HeroID iHeroID ) const {
    return m_hHeroInventory.GetHero( iHeroID );
}
inline Hero * CCGOPManager::GetHero( HeroID iHeroID ) {
    return m_hHeroInventory.GetHero( iHeroID );
}

inline HeroInventory::HeroMap::Iterator CCGOPManager::EnumHeroes() const {
    return m_hHeroInventory.m_mapHeroInventory.Begin();
}

inline HeroID CCGOPManager::CreateHero( const GChar * strName, HeroRank iRank, UInt iLevel, Bool bEvolved, HeroSanctify iSanctify ) {
    return m_hHeroInventory._CreateHero(
        strName, iRank, iLevel, bEvolved, iSanctify
    );
}
inline Void CCGOPManager::DestroyHero( HeroID iHeroID ) {
    DetachAllGearSetsFromHero( iHeroID );
    m_hHeroInventory._DestroyHero( iHeroID );
}
inline Void CCGOPManager::DestroyAllHeroes() {
    DetachAllGearSets();
    m_hHeroInventory._DestroyAllHeroes();
}

inline Void CCGOPManager::UnselectAllHeroGearSets() {
    m_hHeroInventory.UnselectAllGearSets();
}

inline UInt CCGOPManager::GetGearSetCount() const {
    return m_hGearSetInventory.GetGearSetCount();
}
inline const GearSet * CCGOPManager::GetGearSet( GearSetID iGearSetID ) const {
    return m_hGearSetInventory.GetGearSet( iGearSetID );
}
inline GearSet * CCGOPManager::GetGearSet( GearSetID iGearSetID ) {
    return m_hGearSetInventory.GetGearSet( iGearSetID );
}

inline GearSetID CCGOPManager::CreateGearSet( const GChar * strName ) {
    return m_hGearSetInventory._CreateGearSet( strName );
}
inline Void CCGOPManager::DestroyGearSet( GearSetID iGearSetID ) {
    UnequipAllRunesFromGearSet( iGearSetID );
    DetachGearSetFromAllHeroes( iGearSetID );
    m_hGearSetInventory._DestroyGearSet( iGearSetID );
}
inline Void CCGOPManager::DestroyAllGearSets() {
    UnequipAllRunes();
    DetachAllGearSets();
    m_hGearSetInventory._DestroyAllGearSets();
}

inline Void CCGOPManager::FilterRunes( Array<RuneID> * outResults, const RuneQueryMap & mapQueries, const Array<RuneID> * arrExcluded, Bool bAllowLocked, Bool bAllowEquipped ) const {
    return m_hRuneInventory.FilterSearch( outResults, mapQueries, arrExcluded, bAllowLocked, bAllowEquipped );
}
inline Void CCGOPManager::FilterHeroes( Array<HeroID> * outResults, const HeroQueryMap & mapQueries ) const {
    return m_hHeroInventory.FilterSearch( outResults, mapQueries );
}
inline Void CCGOPManager::FilterGearSets( Array<GearSetID> * outResults, const GearSetQueryMap & mapQueries ) const {
    return m_hGearSetInventory.FilterSearch( outResults, mapQueries );
}

