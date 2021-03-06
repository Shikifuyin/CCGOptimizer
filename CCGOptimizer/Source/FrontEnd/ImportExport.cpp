/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/ImportExport.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Import / Export GUI
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
#include "ImportExport.h"

#include "CCGOPGUI.h"

/////////////////////////////////////////////////////////////////////////////////
// ImportExport implementation
ImportExport::ImportExport( CCGOPGUI * pGUI ):
	m_hLoadSave( pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;
}
ImportExport::~ImportExport()
{
	// nothing to do
}

Void ImportExport::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_IMPORTEXPORT );

	// Load / Save UI
	m_hLoadSave.Initialize();
}
Void ImportExport::Cleanup()
{
	// Load / Save UI
	m_hLoadSave.Cleanup();
}
