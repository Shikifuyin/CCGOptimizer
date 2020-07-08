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
	m_hGearSetDetails( pGUI ),
	m_hGearSetStats( pGUI ),
	m_hGearSetCreation( pGUI ),
	m_hGearSetOptions( pGUI ),
	m_hGearSetBuild( pGUI )
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

	// GearSet Details UI
	m_hGearSetDetails.Initialize();

	// GearSet Stats UI
	m_hGearSetStats.Initialize();

	// GearSet Creation UI
	m_hGearSetCreation.Initialize();

	// GearSet Options UI
	m_hGearSetOptions.Initialize();

	// GearSet Build UI
	m_hGearSetBuild.Initialize();
}
Void GearSetExplorer::Cleanup()
{
	// GearSet Build UI
	m_hGearSetBuild.Cleanup();

	// GearSet Options UI
	m_hGearSetOptions.Cleanup();

	// GearSet Creation UI
	m_hGearSetCreation.Cleanup();

	// GearSet Stats UI
	m_hGearSetStats.Cleanup();

	// GearSet Details UI
	m_hGearSetDetails.Cleanup();

	// GearSet Table UI
	m_hGearSetTable.Cleanup();
}



