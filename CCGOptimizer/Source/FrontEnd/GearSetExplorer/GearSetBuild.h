/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetBuild.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Builder
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
#ifndef CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETBUILD_H
#define CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETBUILD_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"
#include "Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetBuildGroupModel class
class UIGearSetBuildGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetBuildGroupModel();
	virtual ~UIGearSetBuildGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

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
// The UIGearSetBuildHeadLineModel class
class UIGearSetBuildHeadLineModel : public WinGUIStaticModel
{
public:
	UIGearSetBuildHeadLineModel();
	virtual ~UIGearSetBuildHeadLineModel();

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
// The UIGearSetBuildMainStatModel class
class UIGearSetBuildMainStatModel : public WinGUIStaticModel
{
public:
	UIGearSetBuildMainStatModel();
	virtual ~UIGearSetBuildMainStatModel();

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
// The UIGearSetBuildInnateStatModel class
class UIGearSetBuildInnateStatModel : public WinGUIStaticModel
{
public:
	UIGearSetBuildInnateStatModel();
	virtual ~UIGearSetBuildInnateStatModel();

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
// The UIGearSetBuildRandomStatModel class
class UIGearSetBuildRandomStatModel : public WinGUIStaticModel
{
public:
	UIGearSetBuildRandomStatModel();
	virtual ~UIGearSetBuildRandomStatModel();

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
// The UIGearSetBuildRunePoolModel class
class UIGearSetBuildRunePoolModel : public WinGUIComboBoxModel
{
public:
	UIGearSetBuildRunePoolModel();
	virtual ~UIGearSetBuildRunePoolModel();

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
// The UIGearSetBuildRuneRemoveModel class
class UIGearSetBuildRuneRemoveModel : public WinGUIButtonModel
{
public:
	UIGearSetBuildRuneRemoveModel();
	virtual ~UIGearSetBuildRuneRemoveModel();

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
// The UIGearSetBuildRuneEquipModel class
class UIGearSetBuildRuneEquipModel : public WinGUIButtonModel
{
public:
	UIGearSetBuildRuneEquipModel();
	virtual ~UIGearSetBuildRuneEquipModel();

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
// The UIGearSetBuild class
class UIGearSetBuild
{
public:
	UIGearSetBuild( CCGOPGUI * pGUI );
	~UIGearSetBuild();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// GearSet Build
	inline Void GetArea( WinGUIRectangle * outClientArea ) const;

	// GearSet Build Slots
	inline Void GetSlotArea( WinGUIRectangle * outClientArea, UInt iSlot ) const;

	inline WinGUIComboBox * GetRunePool( UInt iSlot ) const;

	// Helpers
	Void UpdateModels( UInt iSlot );
	Void AddPooledRune( RuneID iRuneID );
	Void RemovePooledRune( RuneID iRuneID );

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// GearSet Build UI
	UIGearSetBuildGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	struct _build_slot {
		UIGearSetBuildSlotGroupModel hSlotGroupModel;
		WinGUIGroupBox * pSlotGroup;

		UIGearSetBuildHeadLineModel hHeadLineModel; // Set, Rank, Quality, Level
		WinGUIStatic * pHeadLine;

		UIGearSetBuildMainStatModel hMainStatModel;
		WinGUIStatic * pMainStat;

		UIGearSetBuildInnateStatModel hInnateStatModel;
		WinGUIStatic * pInnateStat;

		struct _random_stats {
			UIGearSetBuildRandomStatModel hStatModel;
			WinGUIStatic * pStat;
		} arrRandomStats[RUNE_RANDOM_STAT_COUNT];

		UIGearSetBuildRunePoolModel hRunePoolModel;
		WinGUIComboBox * pRunePool;

		UIGearSetBuildRuneRemoveModel hRuneRemoveModel;
		WinGUIButton * pRuneRemove;

		UIGearSetBuildRuneEquipModel hRuneEquipModel;
		WinGUIButton * pRuneEquip;
	} m_arrBuildSlots[RUNE_SLOT_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetBuild.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETBUILD_H

