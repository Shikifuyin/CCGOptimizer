/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetSlot.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Slots Display
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
#ifndef CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETSLOT_H
#define CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETSLOT_H

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
// The UIGearSetSlotGroupModel class
class UIGearSetSlotGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetSlotGroupModel();
	virtual ~UIGearSetSlotGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetSlotHeadLineModel class
class UIGearSetSlotHeadLineModel : public WinGUIStaticModel
{
public:
	UIGearSetSlotHeadLineModel();
	virtual ~UIGearSetSlotHeadLineModel();

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
// The UIGearSetSlotMainStatModel class
class UIGearSetSlotMainStatModel : public WinGUIStaticModel
{
public:
	UIGearSetSlotMainStatModel();
	virtual ~UIGearSetSlotMainStatModel();

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
// The UIGearSetSlotInnateStatModel class
class UIGearSetSlotInnateStatModel : public WinGUIStaticModel
{
public:
	UIGearSetSlotInnateStatModel();
	virtual ~UIGearSetSlotInnateStatModel();

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
// The UIGearSetSlotRandomStatModel class
class UIGearSetSlotRandomStatModel : public WinGUIStaticModel
{
public:
	UIGearSetSlotRandomStatModel();
	virtual ~UIGearSetSlotRandomStatModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot, UInt iIndex );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
	UInt m_iIndex;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetSlot class
class UIGearSetSlot
{
public:
	UIGearSetSlot();
	~UIGearSetSlot();

	// Initialization / Cleanup
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );
	Void Cleanup();

	// GearSet Slot
	inline Void GetSlotArea( WinGUIRectangle * outClientArea ) const;

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
	WinGUIContainer * m_pRoot;

	// GearSet Slot UI
	UIGearSetSlotGroupModel m_hGroup;
	WinGUIGroupBox * m_pGroup;

	UIGearSetSlotHeadLineModel m_hHeadLine; // Set, Rank, Quality, Level
	WinGUIStatic * m_pHeadLine;

	UIGearSetSlotMainStatModel m_hMainStat;
	WinGUIStatic * m_pMainStat;

	UIGearSetSlotInnateStatModel m_hInnateStat;
	WinGUIStatic * m_pInnateStat;

	struct _random_stats {
		UIGearSetSlotRandomStatModel hStat;
		WinGUIStatic * pStat;
	} m_arrRandomStats[RUNE_RANDOM_STAT_COUNT];


};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetSlot.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETSLOT_H

