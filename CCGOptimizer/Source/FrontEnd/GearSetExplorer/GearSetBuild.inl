/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetBuild.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Builder
/////////////////////////////////////////////////////////////////////////////////
// Part of Scarab-Engine, licensed under the
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuild implementation
inline Void UIGearSetBuild::GetArea( WinGUIRectangle * outClientArea ) const {
	m_pGroup->ComputeClientArea( outClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );
}

inline Void UIGearSetBuild::GetSlotArea( WinGUIRectangle * outClientArea, UInt iSlot ) const {
	Assert( iSlot < RUNE_SLOT_COUNT );
	m_arrBuildSlots[iSlot].pSlotGroup->ComputeClientArea( outClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );
}

inline WinGUIComboBox * UIGearSetBuild::GetRunePool( UInt iSlot ) const {
	Assert( iSlot < RUNE_SLOT_COUNT );
	return m_arrBuildSlots[iSlot].pRunePool;
}
