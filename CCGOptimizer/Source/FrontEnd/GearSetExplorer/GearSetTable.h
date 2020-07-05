/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetTable.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Table
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
#ifndef CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETTABLE_H
#define CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETTABLE_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"
#include "../Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// GearSet Table Columns
enum UIGearSetTableColumn {
	UI_GEARSETTABLE_COLUMN_NAME = 0, // CheckBoxes
	UI_GEARSETTABLE_COLUMN_ID,
	UI_GEARSETTABLE_COLUMN_RUNE_1,
	UI_GEARSETTABLE_COLUMN_RUNE_2,
	UI_GEARSETTABLE_COLUMN_RUNE_3,
	UI_GEARSETTABLE_COLUMN_RUNE_4,
	UI_GEARSETTABLE_COLUMN_RUNE_5,
	UI_GEARSETTABLE_COLUMN_RUNE_6,
	UI_GEARSETTABLE_COLUMN_COUNT
};

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetTableModel class
class UIGearSetTableModel : public WinGUITableModel
{
public:
	UIGearSetTableModel();
	virtual ~UIGearSetTableModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );
	Void CreateColumns();

	// Update
	Void UpdateAfterGearSetCreation( GearSetID iGearSetID );
	Void UpdateAfterDataLoad();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnColumnHeaderClick( UInt iIndex );

	// Callback Events
	virtual GChar * OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	GChar m_arrColumnNames[UI_GEARSETTABLE_COLUMN_COUNT][64];
	UInt m_arrColumnWidths[UI_GEARSETTABLE_COLUMN_COUNT];

	// Beware, those have reversed convention ...
	static Int __stdcall _Compare_GearSetName( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_GearSetID( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_GearSetRune1( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_GearSetRune2( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_GearSetRune3( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_GearSetRune4( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_GearSetRune5( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_GearSetRune6( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetTableGroupModel class
class UIGearSetTableGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetTableGroupModel();
	virtual ~UIGearSetTableGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetTableSelectAllModel class
class UIGearSetTableSelectAllModel : public WinGUIButtonModel
{
public:
	UIGearSetTableSelectAllModel();
	virtual ~UIGearSetTableSelectAllModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetTableUnselectAllModel class
class UIGearSetTableUnselectAllModel : public WinGUIButtonModel
{
public:
	UIGearSetTableUnselectAllModel();
	virtual ~UIGearSetTableUnselectAllModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetTableCheckAllModel class
class UIGearSetTableCheckAllModel : public WinGUIButtonModel
{
public:
	UIGearSetTableCheckAllModel();
	virtual ~UIGearSetTableCheckAllModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetTableUncheckAllModel class
class UIGearSetTableUncheckAllModel : public WinGUIButtonModel
{
public:
	UIGearSetTableUncheckAllModel();
	virtual ~UIGearSetTableUncheckAllModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetTableCheckSelectedModel class
class UIGearSetTableCheckSelectedModel : public WinGUIButtonModel
{
public:
	UIGearSetTableCheckSelectedModel();
	virtual ~UIGearSetTableCheckSelectedModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetTableUncheckSelectedModel class
class UIGearSetTableUncheckSelectedModel : public WinGUIButtonModel
{
public:
	UIGearSetTableUncheckSelectedModel();
	virtual ~UIGearSetTableUncheckSelectedModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetTable class
class UIGearSetTable
{
public:
	UIGearSetTable( CCGOPGUI * pGUI );
	~UIGearSetTable();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Table
	inline WinGUITable * GetTable() const;

	// Table Options
	inline Void GetOptionsArea( WinGUIRectangle * outClientArea ) const;

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// GearSet Table UI
	UIGearSetTableModel m_hGearSetTableModel;
	WinGUITable * m_pGearSetTable;

	UIGearSetTableGroupModel m_hGroup;
	WinGUIGroupBox * m_pGroup;

	UIGearSetTableSelectAllModel m_hSelectAll;
	WinGUIButton * m_pSelectAll;

	UIGearSetTableUnselectAllModel m_hUnselectAll;
	WinGUIButton * m_pUnselectAll;

	UIGearSetTableCheckAllModel m_hCheckAll;
	WinGUIButton * m_pCheckAll;

	UIGearSetTableUncheckAllModel m_hUncheckAll;
	WinGUIButton * m_pUncheckAll;

	UIGearSetTableCheckSelectedModel m_hCheckSelected;
	WinGUIButton * m_pCheckSelected;

	UIGearSetTableUncheckSelectedModel m_hUncheckSelected;
	WinGUIButton * m_pUncheckSelected;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetTable.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETTABLE_H

