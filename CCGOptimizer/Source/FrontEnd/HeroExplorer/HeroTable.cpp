/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer/HeroTable.cpp
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
// Includes
#include "HeroTable.h"

#include "../CCGOPGUI.h"

/////////////////////////////////////////////////////////////////////////////////
// HeroTableModel implementation
HeroTableModel::HeroTableModel():
	WinGUITableModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE)
{
	m_pGUI = NULL;

	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_CB],         TEXT("") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_ID],         TEXT("ID") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_NAME],       TEXT("Name") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_FACTION],    TEXT("Faction") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_RANK],       TEXT("Rank") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_LEVEL],      TEXT("Level") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_EVOLVED],    TEXT("Evolved") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_SANCTIFIED], TEXT("Sanctified") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_HP],         TEXT("HP") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_ATT],        TEXT("ATT") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_DEF],        TEXT("DEF") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_SPD],        TEXT("SPD") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_CRITRATE],   TEXT("CritRate") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_CRITDMG],    TEXT("CritDmg") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_HIT],        TEXT("HIT") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_RES],        TEXT("RES") );
}
HeroTableModel::~HeroTableModel()
{
	// nothing to do
}

Void HeroTableModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	m_hCreationParameters.bVirtualTable = false;

	m_hCreationParameters.bHasBackBuffer = true;
	m_hCreationParameters.bHasSharedImageLists = false;

	m_hCreationParameters.iItemCallBackMode = ( WINGUI_TABLE_ITEMCALLBACK_LABELS );
	m_hCreationParameters.iStateCallBackMode = 0;

	m_hCreationParameters.iViewMode = WINGUI_TABLE_VIEW_DETAILED;
	m_hCreationParameters.bGroupMode = false;
	m_hCreationParameters.bHasHeadersInAllViews = false;

	m_hCreationParameters.bHasColumnHeaders = true;
	m_hCreationParameters.bHasStaticColumnHeaders = false;
	m_hCreationParameters.bHasDraggableColumnHeaders = false;
	m_hCreationParameters.bHasIconColumnOverflowButton = false;

	m_hCreationParameters.bHasCheckBoxes = true;
	m_hCreationParameters.bHasIconLabels = true;
	m_hCreationParameters.bHasEditableLabels = false;
	m_hCreationParameters.bHasSubItemImages = true;

	m_hCreationParameters.bSingleItemSelection = false;
	m_hCreationParameters.bIconSimpleSelection = false;

	m_hCreationParameters.bAutoSortAscending = false;
	m_hCreationParameters.bAutoSortDescending = false;

	m_hCreationParameters.bHasHotTrackingSingleClick = false;
	m_hCreationParameters.bHasHotTrackingDoubleClick = false;
	m_hCreationParameters.bHasHotTrackingSelection = false;

	m_hCreationParameters.bHasInfoTips = true;
}
Void HeroTableModel::CreateColumns()
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	// Build Columns
	for( UInt i = 0; i < CCGOP_HEROTABLE_COLUMN_COUNT; ++i ) {
		pTable->AddColumn( i, m_arrColumnNames[i], i, i, 100 );
	}
}

const WinGUILayout * HeroTableModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = 100;
	hLayout.FixedPosition.iY = 10;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = 1400;
	hLayout.FixedSize.iY = 600;

	return &hLayout;
}

GChar * HeroTableModel::OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData )
{
	Assert( iItemIndex < CCGOPFn->GetHeroCount() );
	Assert( iSubItemIndex < CCGOP_HEROTABLE_COLUMN_COUNT );

	static GChar strBuffer[64];

	const Hero * pHero = CCGOPFn->GetHero( iItemIndex );
	UInt iStatValue;

	switch( iSubItemIndex ) {
		case CCGOP_HEROTABLE_COLUMN_CB:         StringFn->NCopy( strBuffer, TEXT(""), 63 ); break;
		case CCGOP_HEROTABLE_COLUMN_ID:         StringFn->FromUInt( strBuffer, pHero->GetID() ); break;
		case CCGOP_HEROTABLE_COLUMN_NAME:       StringFn->NCopy( strBuffer, pHero->GetName(), 63 ); break;
		case CCGOP_HEROTABLE_COLUMN_FACTION:    StringFn->FromUInt( strBuffer, pHero->GetFaction() ); break;
		case CCGOP_HEROTABLE_COLUMN_RANK:       StringFn->FromUInt( strBuffer, pHero->GetRank() ); break;
		case CCGOP_HEROTABLE_COLUMN_LEVEL:      StringFn->FromUInt( strBuffer, pHero->GetLevel() ); break;
		case CCGOP_HEROTABLE_COLUMN_EVOLVED:    StringFn->NCopy( strBuffer, pHero->IsEvolved() ? TEXT("Yes") : TEXT("No"), 63 ); break;
		case CCGOP_HEROTABLE_COLUMN_SANCTIFIED: StringFn->FromUInt( strBuffer, pHero->GetSanctification() ); break;
		case CCGOP_HEROTABLE_COLUMN_HP:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_HP, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_ATT:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_ATTACK, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_DEF:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_DEFENSE, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_SPD:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_SPEED, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_CRITRATE:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_CRIT_RATE, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_CRITDMG:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_CRIT_DMG, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_HIT:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_HIT, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_RES:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_RESISTANCE, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		default: Assert(false); break;
	}

	return strBuffer;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroTable implementation
HeroTable::HeroTable( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pHeroTable = NULL;
}
HeroTable::~HeroTable()
{
	// nothing to do
}

Void HeroTable::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_HERO_EXPLORER );

	// Build Hero Table
	m_hHeroTableModel.Initialize( m_pGUI );
	m_pHeroTable = WinGUIFn->CreateTable( m_pRoot, &m_hHeroTableModel );
	m_hHeroTableModel.CreateColumns();
}
Void HeroTable::Cleanup()
{
	// nothing to do
}


