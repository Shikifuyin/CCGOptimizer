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
// The UIGearSetStatsRuneGroupModel class
class UIGearSetStatsRuneGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetStatsRuneGroupModel();
	virtual ~UIGearSetStatsRuneGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetStatsRuneHeadLineModel class
class UIGearSetStatsRuneHeadLineModel : public WinGUIStaticModel
{
public:
	UIGearSetStatsRuneHeadLineModel();
	virtual ~UIGearSetStatsRuneHeadLineModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetStatsRuneMainStatModel class
class UIGearSetStatsRuneMainStatModel : public WinGUIStaticModel
{
public:
	UIGearSetStatsRuneMainStatModel();
	virtual ~UIGearSetStatsRuneMainStatModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
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
	inline Void GetGearSetArea( WinGUIRectangle * outClientArea ) const;

	// Rune Stats
	inline Void GetRuneArea( WinGUIRectangle * outClientArea, UInt iSlot ) const;

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// GearSet Stats UI
	UIGearSetStatsGroupModel m_hGroup;
	WinGUIGroupBox * m_pGroup;

	struct _rune_stats {
		UIGearSetStatsRuneGroupModel hGroup;
		WinGUIGroupBox * pGroup;

		UIGearSetStatsRuneHeadLineModel hHeadLine; // Set, Rank, Quality, Level
		WinGUIStatic * pHeadLine;

		UIGearSetStatsRuneMainStatModel hMainStat;
		WinGUIStatic * pMainStat;

		//UIGearSetStatsRuneInnateStatModel hInnateStat;
		WinGUIStatic * pInnateStat;

		struct _random_stats {
			//UIGearSetStatsRuneRandomStatModel hStat;
			WinGUIStatic * pStat;

		} arrRandomStats[RUNE_RANDOM_STAT_COUNT];

	} m_arrRuneStats[RUNE_SLOT_COUNT];

	//UIGearSetStatsSetBonusModel m_hSetBonus;
	WinGUIStatic * m_pSetBonus;

};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetStats.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETSTATS_H

