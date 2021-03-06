/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetOptions.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Options
/////////////////////////////////////////////////////////////////////////////////
// Part of Scarab-Engine, licensed under the
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetOptions implementation
inline Void UIGearSetOptions::GetArea( WinGUIRectangle * outClientArea ) const {
	m_pGroup->ComputeClientArea( outClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );
}

inline WinGUITextEdit * UIGearSetOptions::GetName() const {
	return m_pName;
}
