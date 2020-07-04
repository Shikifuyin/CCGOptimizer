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
enum CCGOPRuneTableColumn {
	CCGOP_RUNETABLE_COLUMN_ID, // CheckBoxes
	CCGOP_RUNETABLE_COLUMN_LOCKED,
	CCGOP_RUNETABLE_COLUMN_SLOT,
	CCGOP_RUNETABLE_COLUMN_SET,
	CCGOP_RUNETABLE_COLUMN_RANK,
	CCGOP_RUNETABLE_COLUMN_QUALITY,
	CCGOP_RUNETABLE_COLUMN_LEVEL,
	CCGOP_RUNETABLE_COLUMN_MAINSTAT,
	CCGOP_RUNETABLE_COLUMN_MAINSTAT_VALUE,
	CCGOP_RUNETABLE_COLUMN_INNATESTAT,
	CCGOP_RUNETABLE_COLUMN_INNATESTAT_VALUE,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_HP_PC,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_HP_FLAT,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_ATT_PC,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_ATT_FLAT,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_DEF_PC,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_DEF_FLAT,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_SPD,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_CRITRATE,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_CRITDMG,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_HIT,
	CCGOP_RUNETABLE_COLUMN_RANDOMSTAT_RES,
	CCGOP_RUNETABLE_COLUMN_COUNT
};

// Prototypes
class CCGOPGUI;

class RuneCreationButtonModel;

class RuneOptionsLockModel;
class RuneOptionsDeleteModel;

class RuneSearchClearModel;
class RuneSearchApplyModel;

class CCGOPFileLoadModel;

/////////////////////////////////////////////////////////////////////////////////
// The RuneTableModel class
class RuneTableModel : public WinGUITableModel
{
public:
	RuneTableModel();
	virtual ~RuneTableModel();

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

	GChar m_arrColumnNames[CCGOP_RUNETABLE_COLUMN_COUNT][64];
	UInt m_arrColumnWidths[CCGOP_RUNETABLE_COLUMN_COUNT];

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
// The RuneTableGroupModel class
class RuneTableGroupModel : public WinGUIGroupBoxModel
{
public:
	RuneTableGroupModel();
	virtual ~RuneTableGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneTableSelectAllModel class
class RuneTableSelectAllModel : public WinGUIButtonModel
{
public:
	RuneTableSelectAllModel();
	~RuneTableSelectAllModel();

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
// The RuneTableUnselectAllModel class
class RuneTableUnselectAllModel : public WinGUIButtonModel
{
public:
	RuneTableUnselectAllModel();
	~RuneTableUnselectAllModel();

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
// The RuneTableCheckAllModel class
class RuneTableCheckAllModel : public WinGUIButtonModel
{
public:
	RuneTableCheckAllModel();
	~RuneTableCheckAllModel();

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
// The RuneTableUncheckAllModel class
class RuneTableUncheckAllModel : public WinGUIButtonModel
{
public:
	RuneTableUncheckAllModel();
	~RuneTableUncheckAllModel();

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
// The RuneTableCheckSelectedModel class
class RuneTableCheckSelectedModel : public WinGUIButtonModel
{
public:
	RuneTableCheckSelectedModel();
	~RuneTableCheckSelectedModel();

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
// The RuneTableUncheckSelectedModel class
class RuneTableUncheckSelectedModel : public WinGUIButtonModel
{
public:
	RuneTableUncheckSelectedModel();
	~RuneTableUncheckSelectedModel();

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
// The RuneTable class
class RuneTable
{
public:
	RuneTable( CCGOPGUI * pGUI );
	~RuneTable();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

private:
	friend class RuneTableSelectAllModel;
	friend class RuneTableUnselectAllModel;
	friend class RuneTableCheckAllModel;
	friend class RuneTableUncheckAllModel;
	friend class RuneTableCheckSelectedModel;
	friend class RuneTableUncheckSelectedModel;

	friend class RuneCreationButtonModel;

	friend class RuneOptionsLockModel;
	friend class RuneOptionsDeleteModel;

	friend class RuneSearchClearModel;
	friend class RuneSearchApplyModel;

	friend class CCGOPFileLoadModel;

	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Rune Table UI
	RuneTableModel m_hRuneTableModel;
	WinGUITable * m_pRuneTable;

	RuneTableGroupModel m_hGroup;
	WinGUIGroupBox * m_pGroup;
	RuneTableSelectAllModel m_hSelectAll;
	WinGUIButton * m_pSelectAll;
	RuneTableUnselectAllModel m_hUnselectAll;
	WinGUIButton * m_pUnselectAll;
	RuneTableCheckAllModel m_hCheckAll;
	WinGUIButton * m_pCheckAll;
	RuneTableUncheckAllModel m_hUncheckAll;
	WinGUIButton * m_pUncheckAll;
	RuneTableCheckSelectedModel m_hCheckSelected;
	WinGUIButton * m_pCheckSelected;
	RuneTableUncheckSelectedModel m_hUncheckSelected;
	WinGUIButton * m_pUncheckSelected;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneTable.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RUNEEXPLORER_RUNETABLE_H

