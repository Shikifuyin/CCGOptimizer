/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI
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
#include "RuneExplorer.h"

#include "CCGOPGUI.h"

/////////////////////////////////////////////////////////////////////////////////
// RuneExplorer implementation
RuneExplorer::RuneExplorer( CCGOPGUI * pGUI ):
	m_hRuneTable( pGUI )
	//m_hRuneCreation( pGUI ),
	//m_hRuneOptions( pGUI ),
	//m_hRuneLoadSave( pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;
}
RuneExplorer::~RuneExplorer()
{
	// nothing to do
}

Void RuneExplorer::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_RUNE_EXPLORER );

	// Build Rune Table UI
	m_hRuneTable.Initialize();

	// Build Rune Creation UI
	//m_hRuneCreation.Initialize();

	// Build Rune Options UI
	//m_hRuneOptions.Initialize();

	// Build Rune Load/Save UI
	//m_hRuneLoadSave.Initialize();
}
Void RuneExplorer::Cleanup()
{
	// Cleanup Rune Load/Save UI
	//m_hRuneLoadSave.Cleanup();

	// Cleanup Rune Options UI
	//m_hRuneOptions.Cleanup();

	// Cleanup Rune Creation UI
	//m_hRuneCreation.Cleanup();

	// Cleanup Rune Table UI
	m_hRuneTable.Cleanup();
}


