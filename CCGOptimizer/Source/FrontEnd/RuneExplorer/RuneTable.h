/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneTable.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI : Rune Table
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
#ifndef CCGOP_FRONTEND_RUNEEXPLORER_RUNETABLE_H
#define CCGOP_FRONTEND_RUNEEXPLORER_RUNETABLE_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"
#include "../Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Rune Table Columns
enum UIRuneTableColumn {
	UI_RUNETABLE_COLUMN_ID, // CheckBoxes
	UI_RUNETABLE_COLUMN_LOCKED,
	UI_RUNETABLE_COLUMN_SLOT,
	UI_RUNETABLE_COLUMN_SET,
	UI_RUNETABLE_COLUMN_RANK,
	UI_RUNETABLE_COLUMN_QUALITY,
	UI_RUNETABLE_COLUMN_LEVEL,
	UI_RUNETABLE_COLUMN_MAINSTAT,
	UI_RUNETABLE_COLUMN_MAINSTAT_VALUE,
	UI_RUNETABLE_COLUMN_INNATESTAT,
	UI_RUNETABLE_COLUMN_INNATESTAT_VALUE,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_PC,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_FLAT,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_PC,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_FLAT,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_PC,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_FLAT,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_SPD,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITRATE,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITDMG,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_HIT,
	UI_RUNETABLE_COLUMN_RANDOMSTAT_RES,
	UI_RUNETABLE_COLUMN_COUNT
};

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneTableModel class
class UIRuneTableModel : public WinGUITableModel
{
public:
	UIRuneTableModel();
	virtual ~UIRuneTableModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );
	Void CreateColumns();

	// Update
	Void UpdateAfterRuneCreation( RuneID iRuneID );
	Void UpdateAfterDataLoad();
	Void UpdateAfterFiltering( const Array<RuneID> & arrFilteredRunes );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnColumnHeaderClick( UInt iIndex );

	// Callback Events
	virtual GChar * OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	GChar m_arrColumnNames[UI_RUNETABLE_COLUMN_COUNT][64];
	UInt m_arrColumnWidths[UI_RUNETABLE_COLUMN_COUNT];

	// Beware, those have reversed convention ...
	static Int __stdcall _Compare_RuneID( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneLocked( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneSlot( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneSet( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRank( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneQuality( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneLevel( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneMainStat( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneMainStatValue( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneInnateStat( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneInnateStatValue( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatHPPc( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatHPFlat( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatATTPc( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatATTFlat( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatDEFPc( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatDEFFlat( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatSPD( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatCritRate( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatCritDmg( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatHIT( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_RuneRandomStatRES( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneTableGroupModel class
class UIRuneTableGroupModel : public WinGUIGroupBoxModel
{
public:
	UIRuneTableGroupModel();
	virtual ~UIRuneTableGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneTableSelectAllModel class
class UIRuneTableSelectAllModel : public WinGUIButtonModel
{
public:
	UIRuneTableSelectAllModel();
	virtual ~UIRuneTableSelectAllModel();

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
// The UIRuneTableUnselectAllModel class
class UIRuneTableUnselectAllModel : public WinGUIButtonModel
{
public:
	UIRuneTableUnselectAllModel();
	virtual ~UIRuneTableUnselectAllModel();

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
// The UIRuneTableCheckAllModel class
class UIRuneTableCheckAllModel : public WinGUIButtonModel
{
public:
	UIRuneTableCheckAllModel();
	virtual ~UIRuneTableCheckAllModel();

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
// The UIRuneTableUncheckAllModel class
class UIRuneTableUncheckAllModel : public WinGUIButtonModel
{
public:
	UIRuneTableUncheckAllModel();
	virtual ~UIRuneTableUncheckAllModel();

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
// The UIRuneTableCheckSelectedModel class
class UIRuneTableCheckSelectedModel : public WinGUIButtonModel
{
public:
	UIRuneTableCheckSelectedModel();
	virtual ~UIRuneTableCheckSelectedModel();

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
// The UIRuneTableUncheckSelectedModel class
class UIRuneTableUncheckSelectedModel : public WinGUIButtonModel
{
public:
	UIRuneTableUncheckSelectedModel();
	virtual ~UIRuneTableUncheckSelectedModel();

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
// The UIRuneTable class
class UIRuneTable
{
public:
	UIRuneTable( CCGOPGUI * pGUI );
	~UIRuneTable();

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

	// Rune Table UI
	UIRuneTableModel m_hRuneTableModel;
	WinGUITable * m_pRuneTable;

	UIRuneTableGroupModel m_hGroup;
	WinGUIGroupBox * m_pGroup;

	UIRuneTableSelectAllModel m_hSelectAll;
	WinGUIButton * m_pSelectAll;

	UIRuneTableUnselectAllModel m_hUnselectAll;
	WinGUIButton * m_pUnselectAll;

	UIRuneTableCheckAllModel m_hCheckAll;
	WinGUIButton * m_pCheckAll;

	UIRuneTableUncheckAllModel m_hUncheckAll;
	WinGUIButton * m_pUncheckAll;

	UIRuneTableCheckSelectedModel m_hCheckSelected;
	WinGUIButton * m_pCheckSelected;

	UIRuneTableUncheckSelectedModel m_hUncheckSelected;
	WinGUIButton * m_pUncheckSelected;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneTable.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RUNEEXPLORER_RUNETABLE_H

