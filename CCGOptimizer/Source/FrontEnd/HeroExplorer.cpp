/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : HeroExplorer GUI
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
#include "HeroExplorer.h"

#include "CCGOPGUI.h"

/////////////////////////////////////////////////////////////////////////////////
// HeroExplorer implementation
HeroExplorer::HeroExplorer( CCGOPGUI * pGUI ):
	m_hHeroTable( pGUI ),
	m_hHeroCreation( pGUI ),
	m_hHeroOptions( pGUI ),
	m_hHeroLoadSave( pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;
}
HeroExplorer::~HeroExplorer()
{
	// nothing to do
}

Void HeroExplorer::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_HERO_EXPLORER );

	// Build Hero Table UI
	m_hHeroTable.Initialize();

	// Build Hero Creation UI
	m_hHeroCreation.Initialize();

	// Build Hero Options UI
	m_hHeroOptions.Initialize();

	// Build Hero Load/Save UI
	m_hHeroLoadSave.Initialize();
}
Void HeroExplorer::Cleanup()
{
	// Cleanup Hero Load/Save UI
	m_hHeroLoadSave.Cleanup();

	// Cleanup Hero Options UI
	m_hHeroOptions.Cleanup();

	// Cleanup Hero Creation UI
	m_hHeroCreation.Cleanup();

	// Cleanup Hero Table UI
	m_hHeroTable.Cleanup();
}


