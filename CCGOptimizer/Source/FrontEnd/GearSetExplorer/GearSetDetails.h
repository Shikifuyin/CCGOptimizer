/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetDetails.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Runes Display
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
#ifndef CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETDETAILS_H
#define CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETDETAILS_H

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
// The UIGearSetDetailsGroupModel class
class UIGearSetDetailsGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetDetailsGroupModel();
	virtual ~UIGearSetDetailsGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;

};
/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetDetailsSlotGroupModel class
class UIGearSetDetailsSlotGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetDetailsSlotGroupModel();
	virtual ~UIGearSetDetailsSlotGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetDetailsHeadLineModel class
class UIGearSetDetailsHeadLineModel : public WinGUIStaticModel
{
public:
	UIGearSetDetailsHeadLineModel();
	virtual ~UIGearSetDetailsHeadLineModel();

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
// The UIGearSetDetailsMainStatModel class
class UIGearSetDetailsMainStatModel : public WinGUIStaticModel
{
public:
	UIGearSetDetailsMainStatModel();
	virtual ~UIGearSetDetailsMainStatModel();

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
// The UIGearSetDetailsInnateStatModel class
class UIGearSetDetailsInnateStatModel : public WinGUIStaticModel
{
public:
	UIGearSetDetailsInnateStatModel();
	virtual ~UIGearSetDetailsInnateStatModel();

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
// The UIGearSetDetailsRandomStatModel class
class UIGearSetDetailsRandomStatModel : public WinGUIStaticModel
{
public:
	UIGearSetDetailsRandomStatModel();
	virtual ~UIGearSetDetailsRandomStatModel();

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
// The UIGearSetDetailsLockModel class
class UIGearSetDetailsLockModel : public WinGUICheckBoxModel
{
public:
	UIGearSetDetailsLockModel();
	virtual ~UIGearSetDetailsLockModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UInt iSlot );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
	UInt m_iSlot;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetDetails class
class UIGearSetDetails
{
public:
	UIGearSetDetails( CCGOPGUI * pGUI );
	~UIGearSetDetails();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// GearSet Details
	inline Void GetArea( WinGUIRectangle * outClientArea ) const;

	// GearSet Details Slot
	inline Void GetSlotArea( WinGUIRectangle * outClientArea, UInt iSlot ) const;

	// Helpers
	Void UpdateModels( UInt iSlot );

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// GearSet Slot UI
	UIGearSetDetailsGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	struct _details_slot {
		UIGearSetDetailsSlotGroupModel hSlotGroupModel;
		WinGUIGroupBox * pSlotGroup;

		UIGearSetDetailsHeadLineModel hHeadLineModel; // Set, Rank, Quality, Level
		WinGUIStatic * pHeadLine;

		UIGearSetDetailsMainStatModel hMainStatModel;
		WinGUIStatic * pMainStat;

		UIGearSetDetailsInnateStatModel hInnateStatModel;
		WinGUIStatic * pInnateStat;

		struct _random_stats {
			UIGearSetDetailsRandomStatModel hStatModel;
			WinGUIStatic * pStat;
		} arrRandomStats[RUNE_RANDOM_STAT_COUNT];

		UIGearSetDetailsLockModel hLockModel;
		WinGUICheckBox * pLock;
	} m_arrDetailsSlots[RUNE_SLOT_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetDetails.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETDETAILS_H

