/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer.h
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
// Header prelude
#ifndef CCGOP_FRONTEND_GEARSETEXPLORER_H
#define CCGOP_FRONTEND_GEARSETEXPLORER_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../BackEnd/CCGOPManager.h"

#include "ResourceIDs.h"
#include "Layout.h"

#include "GearSetExplorer/GearSetTable.h"
#include "GearSetExplorer/GearSetDetails.h"
#include "GearSetExplorer/GearSetStats.h"
#include "GearSetExplorer/GearSetCreation.h"
#include "GearSetExplorer/GearSetOptions.h"
#include "GearSetExplorer/GearSetBuild.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The GearSetExplorer class
class GearSetExplorer
{
public:
	GearSetExplorer( CCGOPGUI * pGUI );
	~GearSetExplorer();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Access for delegates
	inline UIGearSetTable * GetGearSetTable();
	inline UIGearSetDetails * GetGearSetDetails();
	inline UIGearSetStats * GetGearSetStats();
	inline UIGearSetCreation * GetGearSetCreation();
	inline UIGearSetOptions * GetGearSetOptions();
	inline UIGearSetBuild * GetGearSetBuild();

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// GearSet Table UI
	UIGearSetTable m_hGearSetTable;

	// GearSet Slots UI
	UIGearSetDetails m_hGearSetDetails;

	// GearSet Stats UI
	UIGearSetStats m_hGearSetStats;

	// GearSet Creation UI
	UIGearSetCreation m_hGearSetCreation;

	// GearSet Options UI
	UIGearSetOptions m_hGearSetOptions;

	// GearSet Build Slots UI
	UIGearSetBuild m_hGearSetBuild;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetExplorer.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_H

