/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer.h
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
// Header prelude
#ifndef CCGOP_FRONTEND_HEROEXPLORER_H
#define CCGOP_FRONTEND_HEROEXPLORER_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../BackEnd/CCGOPManager.h"

#include "ResourceIDs.h"
#include "Layout.h"

#include "HeroExplorer/HeroTable.h"
#include "HeroExplorer/HeroCreation.h"
#include "HeroExplorer/HeroOptions.h"
#include "HeroExplorer/HeroLoadSave.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The HeroExplorer class
class HeroExplorer
{
public:
	HeroExplorer( CCGOPGUI * pGUI );
	~HeroExplorer();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Access for delegates
	inline HeroTable * GetHeroTable();
	inline HeroCreation * GetHeroCreation();
	inline HeroOptions * GetHeroOptions();
	inline HeroLoadSave * GetHeroLoadSave();

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Table UI
	HeroTable m_hHeroTable;

	// Hero Creation UI
	HeroCreation m_hHeroCreation;

	// Hero Options UI
	HeroOptions m_hHeroOptions;

	// Hero Load/Save UI
	HeroLoadSave m_hHeroLoadSave;

	// Search UI

};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "HeroExplorer.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_HEROEXPLORER_H

