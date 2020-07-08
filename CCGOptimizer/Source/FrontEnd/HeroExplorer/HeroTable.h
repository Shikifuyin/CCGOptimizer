/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer/HeroTable.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : HeroExplorer GUI : Hero Table
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
#ifndef CCGOP_FRONTEND_HEROEXPLORER_HEROTABLE_H
#define CCGOP_FRONTEND_HEROEXPLORER_HEROTABLE_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"
#include "Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Hero Table Columns
enum UIHeroTableColumn {
	UI_HEROTABLE_COLUMN_NAME = 0, // CheckBoxes
	UI_HEROTABLE_COLUMN_ID,
	UI_HEROTABLE_COLUMN_FACTION,
	UI_HEROTABLE_COLUMN_RANK,
	UI_HEROTABLE_COLUMN_LEVEL,
	UI_HEROTABLE_COLUMN_EVOLVED,
	UI_HEROTABLE_COLUMN_SANCTIFIED,
	UI_HEROTABLE_COLUMN_HP,
	UI_HEROTABLE_COLUMN_ATT,
	UI_HEROTABLE_COLUMN_DEF,
	UI_HEROTABLE_COLUMN_SPD,
	UI_HEROTABLE_COLUMN_CRITRATE,
	UI_HEROTABLE_COLUMN_CRITDMG,
	UI_HEROTABLE_COLUMN_HIT,
	UI_HEROTABLE_COLUMN_RES,
	UI_HEROTABLE_COLUMN_COUNT
};

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroTableModel class
class UIHeroTableModel : public WinGUITableModel
{
public:
	UIHeroTableModel();
	virtual ~UIHeroTableModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );
	Void CreateColumns();

	// Update
	Void UpdateAfterHeroCreation( HeroID iHeroID );
	Void UpdateAfterDataLoad();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnColumnHeaderClick( UInt iIndex );

	// Callback Events
	virtual GChar * OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	GChar m_arrColumnNames[UI_HEROTABLE_COLUMN_COUNT][64];
	UInt m_arrColumnWidths[UI_HEROTABLE_COLUMN_COUNT];

	// Beware, those have reversed convention ...
	static Int __stdcall _Compare_HeroName( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroID( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroFaction( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroRank( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroLevel( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroEvolved( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroSanctified( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroHP( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroATT( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroDEF( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroSPD( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroCritRate( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroCritDmg( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroHIT( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
	static Int __stdcall _Compare_HeroRES( Void * pItemDataA, Void * pItemDataB, Void * pUserData );
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroTableGroupModel class
class UIHeroTableGroupModel : public WinGUIGroupBoxModel
{
public:
	UIHeroTableGroupModel();
	virtual ~UIHeroTableGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroTableSelectAllModel class
class UIHeroTableSelectAllModel : public WinGUIButtonModel
{
public:
	UIHeroTableSelectAllModel();
	virtual ~UIHeroTableSelectAllModel();

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
// The UIHeroTableUnselectAllModel class
class UIHeroTableUnselectAllModel : public WinGUIButtonModel
{
public:
	UIHeroTableUnselectAllModel();
	virtual ~UIHeroTableUnselectAllModel();

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
// The UIHeroTableCheckAllModel class
class UIHeroTableCheckAllModel : public WinGUIButtonModel
{
public:
	UIHeroTableCheckAllModel();
	virtual ~UIHeroTableCheckAllModel();

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
// The UIHeroTableUncheckAllModel class
class UIHeroTableUncheckAllModel : public WinGUIButtonModel
{
public:
	UIHeroTableUncheckAllModel();
	virtual ~UIHeroTableUncheckAllModel();

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
// The UIHeroTableCheckSelectedModel class
class UIHeroTableCheckSelectedModel : public WinGUIButtonModel
{
public:
	UIHeroTableCheckSelectedModel();
	virtual ~UIHeroTableCheckSelectedModel();

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
// The UIHeroTableUncheckSelectedModel class
class UIHeroTableUncheckSelectedModel : public WinGUIButtonModel
{
public:
	UIHeroTableUncheckSelectedModel();
	virtual ~UIHeroTableUncheckSelectedModel();

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
// The UIHeroTable class
class UIHeroTable
{
public:
	UIHeroTable( CCGOPGUI * pGUI );
	~UIHeroTable();

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

	// Hero Table UI
	UIHeroTableModel m_hHeroTableModel;
	WinGUITable * m_pHeroTable;

	UIHeroTableGroupModel m_hGroup;
	WinGUIGroupBox * m_pGroup;

	UIHeroTableSelectAllModel m_hSelectAll;
	WinGUIButton * m_pSelectAll;

	UIHeroTableUnselectAllModel m_hUnselectAll;
	WinGUIButton * m_pUnselectAll;

	UIHeroTableCheckAllModel m_hCheckAll;
	WinGUIButton * m_pCheckAll;

	UIHeroTableUncheckAllModel m_hUncheckAll;
	WinGUIButton * m_pUncheckAll;

	UIHeroTableCheckSelectedModel m_hCheckSelected;
	WinGUIButton * m_pCheckSelected;

	UIHeroTableUncheckSelectedModel m_hUncheckSelected;
	WinGUIButton * m_pUncheckSelected;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "HeroTable.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_HEROEXPLORER_HEROTABLE_H

