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
HeroExplorer::HeroExplorer( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_HERO_EXPLORER );

	m_pSearchUI = NULL;

	m_pHeroTable = NULL;
}
HeroExplorer::~HeroExplorer()
{
	// nothing to do
}

Void HeroExplorer::Initialize()
{
	// Build GUI



}
Void HeroExplorer::Cleanup()
{
	// nothing to do (for now)
}

/////////////////////////////////////////////////////////////////////////////////

