/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetBuildSlot.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Build Slots
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
#ifndef CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETBUILDSLOT_H
#define CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETBUILDSLOT_H

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
// The UIGearSetBuildSlotGroupModel class
class UIGearSetBuildSlotGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetBuildSlotGroupModel();
	virtual ~UIGearSetBuildSlotGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetBuildSlotHeadLineModel class
class UIGearSetBuildSlotHeadLineModel : public WinGUIStaticModel
{
public:
	UIGearSetBuildSlotHeadLineModel();
	virtual ~UIGearSetBuildSlotHeadLineModel();

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
// The UIGearSetBuildSlotMainStatModel class
class UIGearSetBuildSlotMainStatModel : public WinGUIStaticModel
{
public:
	UIGearSetBuildSlotMainStatModel();
	virtual ~UIGearSetBuildSlotMainStatModel();

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
// The UIGearSetBuildSlotInnateStatModel class
class UIGearSetBuildSlotInnateStatModel : public WinGUIStaticModel
{
public:
	UIGearSetBuildSlotInnateStatModel();
	virtual ~UIGearSetBuildSlotInnateStatModel();

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
// The UIGearSetBuildSlotRandomStatModel class
class UIGearSetBuildSlotRandomStatModel : public WinGUIStaticModel
{
public:
	UIGearSetBuildSlotRandomStatModel();
	virtual ~UIGearSetBuildSlotRandomStatModel();

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
// The UIGearSetBuildSlotRuneModel class
class UIGearSetBuildSlotRuneModel : public WinGUIComboBoxModel
{
public:
	UIGearSetBuildSlotRuneModel();
	virtual ~UIGearSetBuildSlotRuneModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetBuildSlotRuneRemoveModel class
class UIGearSetBuildSlotRuneRemoveModel : public WinGUIButtonModel
{
public:
	UIGearSetBuildSlotRuneRemoveModel();
	virtual ~UIGearSetBuildSlotRuneRemoveModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetBuildSlotRuneEquipModel class
class UIGearSetBuildSlotRuneEquipModel : public WinGUIButtonModel
{
public:
	UIGearSetBuildSlotRuneEquipModel();
	virtual ~UIGearSetBuildSlotRuneEquipModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetBuildSlot class
class UIGearSetBuildSlot
{
public:
	UIGearSetBuildSlot();
	~UIGearSetBuildSlot();

	// Initialization / Cleanup
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );
	Void Cleanup();

	// GearSet Build Slot
	inline Void GetSlotArea( WinGUIRectangle * outClientArea ) const;

	inline WinGUIComboBox * GetRune() const;

	// Helpers
	Void UpdateModels();
	Void AddPooledRune( RuneID iRuneID );

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
	WinGUIContainer * m_pRoot;

	// GearSet Build Slot UI
	UIGearSetBuildSlotGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	UIGearSetBuildSlotHeadLineModel m_hHeadLineModel; // Set, Rank, Quality, Level
	WinGUIStatic * m_pHeadLine;

	UIGearSetBuildSlotMainStatModel m_hMainStatModel;
	WinGUIStatic * m_pMainStat;

	UIGearSetBuildSlotInnateStatModel m_hInnateStatModel;
	WinGUIStatic * m_pInnateStat;

	struct _random_stats {
		UIGearSetBuildSlotRandomStatModel hStatModel;
		WinGUIStatic * pStat;
	} m_arrRandomStats[RUNE_RANDOM_STAT_COUNT];

	UIGearSetBuildSlotRuneModel m_hRuneModel;
	WinGUIComboBox * m_pRune;

	UIGearSetBuildSlotRuneRemoveModel m_hRuneRemoveModel;
	WinGUIButton * m_pRuneRemove;

	UIGearSetBuildSlotRuneEquipModel m_hRuneEquipModel;
	WinGUIButton * m_pRuneEquip;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetBuildSlot.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETBUILDSLOT_H

