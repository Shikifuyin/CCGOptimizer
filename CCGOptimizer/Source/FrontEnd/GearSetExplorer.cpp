/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer.cpp
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
// Includes
#include "GearSetExplorer.h"

#include "CCGOPGUI.h"

/////////////////////////////////////////////////////////////////////////////////
// GearSetExplorer implementation
GearSetExplorer::GearSetExplorer( CCGOPGUI * pGUI ):
	m_hGearSetTable( pGUI ),
	m_hGearSetStats( pGUI ),
	m_hGearSetCreation( pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;
}
GearSetExplorer::~GearSetExplorer()
{
	// nothing to do
}

Void GearSetExplorer::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_GEARSET_EXPLORER );

	// GearSet Table UI
	m_hGearSetTable.Initialize();

	// GearSet Slots UI
	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
		m_arrGearSetSlots[i].Initialize( m_pGUI, i );

	// GearSet Stats UI
	m_hGearSetStats.Initialize();

	// GearSet Creation UI
	m_hGearSetCreation.Initialize();

	// GearSet Build Slots UI
	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
		m_arrGearSetBuildSlots[i].Initialize( m_pGUI, i );
}
Void GearSetExplorer::Cleanup()
{
	// GearSet Build Slots UI
	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
		m_arrGearSetBuildSlots[i].Cleanup();

	// GearSet Creation UI
	m_hGearSetCreation.Cleanup();

	// GearSet Stats UI
	m_hGearSetStats.Cleanup();

	// GearSet Slots UI
	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
		m_arrGearSetSlots[i].Cleanup();

	// GearSet Table UI
	m_hGearSetTable.Cleanup();
}



