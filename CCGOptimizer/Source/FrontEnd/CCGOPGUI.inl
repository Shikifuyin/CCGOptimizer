/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/CCGOPGUI.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOP GUI
/////////////////////////////////////////////////////////////////////////////////
// Part of Scarab-Engine, licensed under the
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// CCGOPGUI implementation
inline WinGUITabs * CCGOPGUI::GetTabs() const {
	return m_pTabs;
}
inline WinGUIContainer * CCGOPGUI::GetTabPane( UIMainMenuTabs iTabIndex ) const {
	Assert( iTabIndex < UI_MAINMENU_COUNT );
	return m_arrTabPanes[iTabIndex].pTabPane;
}

inline WinGUIStatusBar * CCGOPGUI::GetStatusBar() const {
	return m_pStatusBar;
}

inline ImportExport * CCGOPGUI::GetImportExport() {
	return &m_hImportExport;
}
inline HeroExplorer * CCGOPGUI::GetHeroExplorer() {
	return &m_hHeroExplorer;
}
inline RuneExplorer * CCGOPGUI::GetRuneExplorer() {
	return &m_hRuneExplorer;
}
inline GearSetExplorer * CCGOPGUI::GetGearSetExplorer() {
	return &m_hGearSetExplorer;
}
inline Optimizer * CCGOPGUI::GetOptimizer() {
	return &m_hOptimizer;
}

