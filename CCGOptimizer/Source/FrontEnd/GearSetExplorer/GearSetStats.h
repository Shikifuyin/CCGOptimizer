/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetStats.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Stats Display
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
#ifndef CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETSTATS_H
#define CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETSTATS_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"
#include "../Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetStatsGroupModel class
class UIGearSetStatsGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetStatsGroupModel();
	virtual ~UIGearSetStatsGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetStatsDisplayModel class
class UIGearSetStatsDisplayModel : public WinGUIStaticModel
{
public:
	UIGearSetStatsDisplayModel();
	virtual ~UIGearSetStatsDisplayModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, HeroStat iHeroStat );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	HeroStat m_iHeroStat;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetStatsSetBonusModel class
class UIGearSetStatsSetBonusModel : public WinGUIStaticModel
{
public:
	UIGearSetStatsSetBonusModel();
	virtual ~UIGearSetStatsSetBonusModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetStats class
class UIGearSetStats
{
public:
	UIGearSetStats( CCGOPGUI * pGUI );
	~UIGearSetStats();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// GearSet Stats
	inline Void GetStatsArea( WinGUIRectangle * outClientArea ) const;

	// Helpers
	Void UpdateModels();

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// GearSet Stats UI
	UIGearSetStatsGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	struct _hero_stats {
		UIGearSetStatsDisplayModel hStatModel;
		WinGUIStatic * pStat;
	} m_arrHeroStats[HERO_STAT_COUNT];

	UIGearSetStatsSetBonusModel m_hSetBonusModel;
	WinGUIStatic * m_pSetBonus;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetStats.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETSTATS_H

