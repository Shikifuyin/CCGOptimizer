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
enum CCGOPGearSetTableColumn {
	CCGOP_GEARSETTABLE_COLUMN_NAME = 0, // CheckBoxes
	CCGOP_GEARSETTABLE_COLUMN_ID,
	CCGOP_GEARSETTABLE_COLUMN_RUNE_1,
	CCGOP_GEARSETTABLE_COLUMN_RUNE_2,
	CCGOP_GEARSETTABLE_COLUMN_RUNE_3,
	CCGOP_GEARSETTABLE_COLUMN_RUNE_4,
	CCGOP_GEARSETTABLE_COLUMN_RUNE_5,
	CCGOP_GEARSETTABLE_COLUMN_RUNE_6,
	CCGOP_GEARSETTABLE_COLUMN_COUNT
};

// Prototypes
class CCGOPGUI;

class CCGOPFileLoadModel;

/////////////////////////////////////////////////////////////////////////////////
// The GearSetTableModel class
class GearSetTableModel : public WinGUITableModel
{
public:
	GearSetTableModel();
	virtual ~GearSetTableModel();

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

	GChar m_arrColumnNames[CCGOP_GEARSETTABLE_COLUMN_COUNT][64];
	UInt m_arrColumnWidths[CCGOP_GEARSETTABLE_COLUMN_COUNT];

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
// The GearSetTableGroupModel class
class GearSetTableGroupModel : public WinGUIGroupBoxModel
{
public:
	GearSetTableGroupModel();
	virtual ~GearSetTableGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The GearSetTableSelectAllModel class
class GearSetTableSelectAllModel : public WinGUIButtonModel
{
public:
	GearSetTableSelectAllModel();
	~GearSetTableSelectAllModel();

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
// The GearSetTableUnselectAllModel class
class GearSetTableUnselectAllModel : public WinGUIButtonModel
{
public:
	GearSetTableUnselectAllModel();
	~GearSetTableUnselectAllModel();

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
// The GearSetTableCheckAllModel class
class GearSetTableCheckAllModel : public WinGUIButtonModel
{
public:
	GearSetTableCheckAllModel();
	~GearSetTableCheckAllModel();

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
// The GearSetTableUncheckAllModel class
class GearSetTableUncheckAllModel : public WinGUIButtonModel
{
public:
	GearSetTableUncheckAllModel();
	~GearSetTableUncheckAllModel();

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
// The GearSetTableCheckSelectedModel class
class GearSetTableCheckSelectedModel : public WinGUIButtonModel
{
public:
	GearSetTableCheckSelectedModel();
	~GearSetTableCheckSelectedModel();

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
// The GearSetTableUncheckSelectedModel class
class GearSetTableUncheckSelectedModel : public WinGUIButtonModel
{
public:
	GearSetTableUncheckSelectedModel();
	~GearSetTableUncheckSelectedModel();

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
// The GearSetTable class
class GearSetTable
{
public:
	GearSetTable( CCGOPGUI * pGUI );
	~GearSetTable();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

private:
	friend class GearSetTableSelectAllModel;
	friend class GearSetTableUnselectAllModel;
	friend class GearSetTableCheckAllModel;
	friend class GearSetTableUncheckAllModel;
	friend class GearSetTableCheckSelectedModel;
	friend class GearSetTableUncheckSelectedModel;

	friend class CCGOPFileLoadModel;

	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// GearSet Table UI
	GearSetTableModel m_hGearSetTableModel;
	WinGUITable * m_pGearSetTable;

	GearSetTableGroupModel m_hGroup;
	WinGUIGroupBox * m_pGroup;

	GearSetTableSelectAllModel m_hSelectAll;
	WinGUIButton * m_pSelectAll;

	GearSetTableUnselectAllModel m_hUnselectAll;
	WinGUIButton * m_pUnselectAll;

	GearSetTableCheckAllModel m_hCheckAll;
	WinGUIButton * m_pCheckAll;

	GearSetTableUncheckAllModel m_hUncheckAll;
	WinGUIButton * m_pUncheckAll;

	GearSetTableCheckSelectedModel m_hCheckSelected;
	WinGUIButton * m_pCheckSelected;

	GearSetTableUncheckSelectedModel m_hUncheckSelected;
	WinGUIButton * m_pUncheckSelected;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetTable.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETTABLE_H

