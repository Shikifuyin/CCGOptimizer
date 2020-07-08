/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneSearch.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI : Rune Search
/////////////////////////////////////////////////////////////////////////////////
// Part of Scarab-Engine, licensed under the
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearch implementation
inline Void UIRuneSearch::GetArea( WinGUIRectangle * outClientArea ) const {
	m_pGroup->ComputeClientArea( outClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );
}

inline WinGUIComboBox * UIRuneSearch::GetSlot() const {
	return m_pSlot;
}
inline WinGUIComboBox * UIRuneSearch::GetSet() const {
	return m_pSet;
}
inline WinGUIComboBox * UIRuneSearch::GetRank() const {
	return m_pRank;
}
inline WinGUIComboBox * UIRuneSearch::GetQuality() const {
	return m_pQuality;
}
inline WinGUIComboBox * UIRuneSearch::GetLevel() const {
	return m_pLevel;
}
inline WinGUIComboBox * UIRuneSearch::GetMainStat() const {
	return m_pMainStat;
}
inline WinGUICheckBox * UIRuneSearch::GetSubStatsMode() const {
	return m_pSubStatsMode;
}
inline WinGUIComboBox * UIRuneSearch::GetSubStat( UInt iIndex ) const {
	Assert( iIndex < RUNE_RANDOM_STAT_COUNT );
	return m_arrSubStats[iIndex].pStat;
}
inline WinGUITextEdit * UIRuneSearch::GetSubStatValue( UInt iIndex ) const {
	Assert( iIndex < RUNE_RANDOM_STAT_COUNT );
	return m_arrSubStats[iIndex].pValue;
}
inline WinGUIStatic * UIRuneSearch::GetIndicator() const {
	return m_pIndicator;
}
