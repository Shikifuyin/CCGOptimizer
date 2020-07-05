/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneCreation.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI : Rune Creation
/////////////////////////////////////////////////////////////////////////////////
// Part of Scarab-Engine, licensed under the
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreation implementation
inline Void UIRuneCreation::GetCreationArea( WinGUIRectangle * outClientArea ) const {
	m_pGroup->ComputeClientArea( outClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );
}

inline WinGUIComboBox * UIRuneCreation::GetSlot() const {
	return m_pSlot;
}
inline WinGUIComboBox * UIRuneCreation::GetSet() const {
	return m_pSet;
}
inline WinGUIComboBox * UIRuneCreation::GetRank() const {
	return m_pRank;
}
inline WinGUIComboBox * UIRuneCreation::GetQuality() const {
	return m_pQuality;
}
inline WinGUIComboBox * UIRuneCreation::GetLevel() const {
	return m_pLevel;
}
inline WinGUIComboBox * UIRuneCreation::GetMainStat() const {
	return m_pMainStat;
}
inline WinGUIComboBox * UIRuneCreation::GetInnateStat() const {
	return m_pInnateStat;
}
inline WinGUITextEdit * UIRuneCreation::GetInnateStatValue() const {
	return m_pInnateStatValue;
}
inline WinGUIComboBox * UIRuneCreation::GetRandomStat( UInt iIndex ) const {
	Assert( iIndex < RUNE_RANDOM_STAT_COUNT );
	return m_arrRandomStats[iIndex].pStat;
}
inline WinGUITextEdit * UIRuneCreation::GetRandomStatValue( UInt iIndex ) const {
	Assert( iIndex < RUNE_RANDOM_STAT_COUNT );
	return m_arrRandomStats[iIndex].pValue;
}


