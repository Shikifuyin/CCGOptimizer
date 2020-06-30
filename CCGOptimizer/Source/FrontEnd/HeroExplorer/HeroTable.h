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

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Hero Table Columns
enum CCGOPHeroTableColumn {
	CCGOP_HEROTABLE_COLUMN_NAME = 0, // CheckBoxes
	CCGOP_HEROTABLE_COLUMN_ID,
	CCGOP_HEROTABLE_COLUMN_FACTION,
	CCGOP_HEROTABLE_COLUMN_RANK,
	CCGOP_HEROTABLE_COLUMN_LEVEL,
	CCGOP_HEROTABLE_COLUMN_EVOLVED,
	CCGOP_HEROTABLE_COLUMN_SANCTIFIED,
	CCGOP_HEROTABLE_COLUMN_HP,
	CCGOP_HEROTABLE_COLUMN_ATT,
	CCGOP_HEROTABLE_COLUMN_DEF,
	CCGOP_HEROTABLE_COLUMN_SPD,
	CCGOP_HEROTABLE_COLUMN_CRITRATE,
	CCGOP_HEROTABLE_COLUMN_CRITDMG,
	CCGOP_HEROTABLE_COLUMN_HIT,
	CCGOP_HEROTABLE_COLUMN_RES,
	CCGOP_HEROTABLE_COLUMN_COUNT
};

// Prototypes
class CCGOPGUI;

class HeroCreationButtonModel;

class HeroOptionsMaxRankModel;
class HeroOptionsMaxLevelModel;
class HeroOptionsEvolveModel;
class HeroOptionsSanctifyModel;
class HeroOptionsDeleteModel;

/////////////////////////////////////////////////////////////////////////////////
// The HeroTableModel class
class HeroTableModel : public WinGUITableModel
{
public:
	HeroTableModel();
	virtual ~HeroTableModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );
	Void CreateColumns();

	// Update
	Void UpdateAfterHeroCreation( HeroID iHeroID );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnColumnHeaderClick( UInt iIndex );

	// Callback Events
	virtual GChar * OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	GChar m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_COUNT][64];
	UInt m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_COUNT];

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
// The HeroTable class
class HeroTable
{
public:
	HeroTable( CCGOPGUI * pGUI );
	~HeroTable();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

private:
	friend class HeroCreationButtonModel;

	friend class HeroOptionsMaxRankModel;
	friend class HeroOptionsMaxLevelModel;
	friend class HeroOptionsEvolveModel;
	friend class HeroOptionsSanctifyModel;
	friend class HeroOptionsDeleteModel;

	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Hero Table UI
	HeroTableModel m_hHeroTableModel;
	WinGUITable * m_pHeroTable;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "HeroTable.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_HEROEXPLORER_HEROTABLE_H

