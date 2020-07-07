/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI
/////////////////////////////////////////////////////////////////////////////////
// Part of Scarab-Engine, licensed under the
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// GearSetExplorer implementation
inline UIGearSetTable * GearSetExplorer::GetGearSetTable() {
	return &m_hGearSetTable;
}
inline UIGearSetSlot * GearSetExplorer::GetGearSetSlot( UInt iSlot ) {
	Assert( iSlot < RUNE_SLOT_COUNT );
	return ( m_arrGearSetSlots + iSlot );
}
inline UIGearSetStats * GearSetExplorer::GetGearSetStats() {
	return &m_hGearSetStats;
}
inline UIGearSetCreation * GearSetExplorer::GetGearSetCreation() {
	return &m_hGearSetCreation;
}
inline UIGearSetOptions * GearSetExplorer::GetGearSetOptions() {
	return &m_hGearSetOptions;
}
inline UIGearSetBuildSlot * GearSetExplorer::GetGearSetBuildSlot( UInt iSlot ) {
	Assert( iSlot < RUNE_SLOT_COUNT );
	return ( m_arrGearSetBuildSlots + iSlot );
}

