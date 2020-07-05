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

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIHeroTableModel implementation
UIHeroTableModel::UIHeroTableModel():
	WinGUITableModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_TABLE)
{
	m_pGUI = NULL;

	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_NAME],       TEXT("Name") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_ID],         TEXT("ID") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_FACTION],    TEXT("Faction") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_RANK],       TEXT("Rank") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_LEVEL],      TEXT("Level") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_EVOLVED],    TEXT("Evolved") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_SANCTIFIED], TEXT("Sanctified") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_HP],         TEXT("HP") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_ATT],        TEXT("ATT") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_DEF],        TEXT("DEF") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_SPD],        TEXT("SPD") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_CRITRATE],   TEXT("CritRate") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_CRITDMG],    TEXT("CritDmg") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_HIT],        TEXT("HIT") );
	StringFn->Copy( m_arrColumnNames[UI_HEROTABLE_COLUMN_RES],        TEXT("RES") );

	UInt iWidthWithScrollBar = ( CCGOP_LAYOUT_TABLE_WIDTH - 18 );
	UInt iNameWidth = (2 * iWidthWithScrollBar) / UI_HEROTABLE_COLUMN_COUNT;
	UInt iAvgWidth = (iWidthWithScrollBar - iNameWidth) / (UI_HEROTABLE_COLUMN_COUNT - 1);
	iNameWidth = ( iWidthWithScrollBar - iAvgWidth * (UI_HEROTABLE_COLUMN_COUNT - 1) );

	m_arrColumnWidths[UI_HEROTABLE_COLUMN_NAME]       = iNameWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_ID]         = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_FACTION]    = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_RANK]       = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_LEVEL]      = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_EVOLVED]    = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_SANCTIFIED] = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_HP]         = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_ATT]        = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_DEF]        = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_SPD]        = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_CRITRATE]   = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_CRITDMG]    = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_HIT]        = iAvgWidth;
	m_arrColumnWidths[UI_HEROTABLE_COLUMN_RES]        = iAvgWidth;
}
UIHeroTableModel::~UIHeroTableModel()
{
	// nothing to do
}

Void UIHeroTableModel::Initialize( CCGOPGUI * pGUI )
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
Void UIHeroTableModel::CreateColumns()
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	// Settings
	pTable->SetBackgroundColor( 0x00d0d0d0 );
	pTable->SetTextBackgroundColor( 0x00d0d0d0 );
	pTable->ShowGridLines( true );

	pTable->ToggleAlwaysShowSelection( true );
	pTable->ToggleFullRowSelection( true );

	// Build Columns
	for( UInt i = 0; i < UI_HEROTABLE_COLUMN_COUNT; ++i ) {
		pTable->AddColumn( i, m_arrColumnNames[i], i, i, m_arrColumnWidths[i] );
		pTable->SetColumnRowTextAlign( i, WINGUI_TABLE_TEXT_ALIGN_CENTER );
	}
}

Void UIHeroTableModel::UpdateAfterHeroCreation( HeroID iHeroID )
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	UInt iIndex = pTable->GetItemCount();

	pTable->AddItem( iIndex ); // Append
	pTable->SetItemData( iIndex, (Void*)iHeroID );
}
Void UIHeroTableModel::UpdateAfterDataLoad()
{
	WinGUITable * pTable = (WinGUITable*)m_pController;
	Assert( pTable->GetItemCount() == 0 );

	UInt iIndex = 0;
	HeroInventory::HeroMap::Iterator itHero = CCGOPFn->EnumHeroes();
	while( !(itHero.IsNull()) ) {

		pTable->AddItem( iIndex );
		pTable->SetItemData( iIndex, (Void*)(itHero.GetKey()) );

		++iIndex;
		++itHero;
	}
}

const WinGUILayout * UIHeroTableModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TABLE_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TABLE_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_SPACING_BORDER;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	return &hLayout;
}

Bool UIHeroTableModel::OnColumnHeaderClick( UInt iIndex )
{
	static Bool arrToggles[UI_HEROTABLE_COLUMN_COUNT] = {
		true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true
	};

	WinGUITable * pTable = (WinGUITable*)m_pController;

	switch( iIndex ) {
		case UI_HEROTABLE_COLUMN_NAME:       pTable->SortItemsByData( _Compare_HeroName,       arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_ID:         pTable->SortItemsByData( _Compare_HeroID,         arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_FACTION:    pTable->SortItemsByData( _Compare_HeroFaction,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_RANK:       pTable->SortItemsByData( _Compare_HeroRank,       arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_LEVEL:      pTable->SortItemsByData( _Compare_HeroLevel,      arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_EVOLVED:    pTable->SortItemsByData( _Compare_HeroEvolved,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_SANCTIFIED: pTable->SortItemsByData( _Compare_HeroSanctified, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_HP:         pTable->SortItemsByData( _Compare_HeroHP,         arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_ATT:        pTable->SortItemsByData( _Compare_HeroATT,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_DEF:        pTable->SortItemsByData( _Compare_HeroDEF,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_SPD:        pTable->SortItemsByData( _Compare_HeroSPD,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_CRITRATE:   pTable->SortItemsByData( _Compare_HeroCritRate,   arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_CRITDMG:    pTable->SortItemsByData( _Compare_HeroCritDmg,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_HIT:        pTable->SortItemsByData( _Compare_HeroHIT,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_HEROTABLE_COLUMN_RES:        pTable->SortItemsByData( _Compare_HeroRES,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		default: Assert(false); break;
	}

	return true;
}

GChar * UIHeroTableModel::OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData )
{
	Assert( iItemIndex < CCGOPFn->GetHeroCount() );
	Assert( iSubItemIndex < UI_HEROTABLE_COLUMN_COUNT );

	WinGUITable * pTable = (WinGUITable*)m_pController;

	static GChar strBuffer[64];

	HeroID iHeroID = (HeroID)(UIntPtr)( pTable->GetItemData(iItemIndex) );
	const Hero * pHero = CCGOPFn->GetHero( iHeroID );
	UInt iStatValue;

	switch( iSubItemIndex ) {
		case UI_HEROTABLE_COLUMN_NAME:
			StringFn->NCopy( strBuffer, pHero->GetName(), 63 );
			break;
		case UI_HEROTABLE_COLUMN_ID:
			StringFn->FromUInt( strBuffer, pHero->GetID() );
			break;
		case UI_HEROTABLE_COLUMN_FACTION:
			StringFn->NCopy( strBuffer, GameDataFn->GetHeroFactionName(pHero->GetFaction()), 63 );
			break;
		case UI_HEROTABLE_COLUMN_RANK:
			StringFn->NCopy( strBuffer, GameDataFn->GetHeroRankName(pHero->GetRank()), 63 );
			break;
		case UI_HEROTABLE_COLUMN_LEVEL:
			StringFn->FromUInt( strBuffer, pHero->GetLevel() );
			break;
		case UI_HEROTABLE_COLUMN_EVOLVED:
			StringFn->NCopy( strBuffer, pHero->IsEvolved() ? TEXT("Yes") : TEXT("No"), 63 );
			break;
		case UI_HEROTABLE_COLUMN_SANCTIFIED:
			StringFn->NCopy( strBuffer, GameDataFn->GetHeroSanctifyName(pHero->GetSanctification()), 63 );
			break;
		case UI_HEROTABLE_COLUMN_HP:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_HP, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case UI_HEROTABLE_COLUMN_ATT:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_ATTACK, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case UI_HEROTABLE_COLUMN_DEF:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_DEFENSE, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case UI_HEROTABLE_COLUMN_SPD:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_SPEED, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->FromUInt( strBuffer, iStatValue );
			break;
		case UI_HEROTABLE_COLUMN_CRITRATE:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_CRIT_RATE, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->Format( strBuffer, TEXT("%d%%"), iStatValue );
			break;
		case UI_HEROTABLE_COLUMN_CRITDMG:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_CRIT_DMG, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->Format( strBuffer, TEXT("%d%%"), iStatValue );
			break;
		case UI_HEROTABLE_COLUMN_HIT:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_HIT, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->Format( strBuffer, TEXT("%d%%"), iStatValue );
			break;
		case UI_HEROTABLE_COLUMN_RES:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_RESISTANCE, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->Format( strBuffer, TEXT("%d%%"), iStatValue );
			break;
		default: Assert(false); break;
	}

	return strBuffer;
}

/////////////////////////////////////////////////////////////////////////////////

Int __stdcall UIHeroTableModel::_Compare_HeroName( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const GChar * strNameA = CCGOPFn->GetHero(iHeroA)->GetName();
	const GChar * strNameB = CCGOPFn->GetHero(iHeroB)->GetName();
	Int iRes = StringFn->NCmp(strNameA, strNameB, GAMEDATA_NAMES_MAX_LENGTH - 1);
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroID( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	Int iRes = 0;
	if ( iHeroA < iHeroB )      iRes = +1;
	else if ( iHeroA > iHeroB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroFaction( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	HeroFaction iFactionA = CCGOPFn->GetHero(iHeroA)->GetFaction();
	HeroFaction iFactionB = CCGOPFn->GetHero(iHeroB)->GetFaction();
	Int iRes = 0;
	if ( iFactionA < iFactionB )      iRes = +1;
	else if ( iFactionA > iFactionB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroRank( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	HeroRank iRankA = CCGOPFn->GetHero(iHeroA)->GetRank();
	HeroRank iRankB = CCGOPFn->GetHero(iHeroB)->GetRank();
	Int iRes = 0;
	if ( iRankA < iRankB )      iRes = +1;
	else if ( iRankA > iRankB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroLevel( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	UInt iLevelA = CCGOPFn->GetHero(iHeroA)->GetLevel();
	UInt iLevelB = CCGOPFn->GetHero(iHeroB)->GetLevel();
	Int iRes = 0;
	if ( iLevelA < iLevelB )      iRes = +1;
	else if ( iLevelA > iLevelB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroEvolved( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	Bool bEvolvedA = CCGOPFn->GetHero(iHeroA)->IsEvolved();
	Bool bEvolvedB = CCGOPFn->GetHero(iHeroB)->IsEvolved();
	Int iRes = 0;
	if ( bEvolvedA && !bEvolvedB )      iRes = +1;
	else if ( !bEvolvedA && bEvolvedB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroSanctified( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	HeroSanctify iSanctifyA = CCGOPFn->GetHero(iHeroA)->GetSanctification();
	HeroSanctify iSanctifyB = CCGOPFn->GetHero(iHeroB)->GetSanctification();
	Int iRes = 0;
	if ( iSanctifyA < iSanctifyB )      iRes = +1;
	else if ( iSanctifyA > iSanctifyB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroHP( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const Hero * pHeroA = CCGOPFn->GetHero( iHeroA );
	const Hero * pHeroB = CCGOPFn->GetHero( iHeroB );
	UInt iStatA = GameDataFn->GetHeroBaseStat( pHeroA->GetName(), HERO_STAT_HP, pHeroA->GetRank(), pHeroA->GetLevel(), pHeroA->IsEvolved() );
	UInt iStatB = GameDataFn->GetHeroBaseStat( pHeroB->GetName(), HERO_STAT_HP, pHeroB->GetRank(), pHeroB->GetLevel(), pHeroB->IsEvolved() );
	Int iRes = 0;
	if ( iStatA < iStatB )      iRes = +1;
	else if ( iStatA > iStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroATT( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const Hero * pHeroA = CCGOPFn->GetHero( iHeroA );
	const Hero * pHeroB = CCGOPFn->GetHero( iHeroB );
	UInt iStatA = GameDataFn->GetHeroBaseStat( pHeroA->GetName(), HERO_STAT_ATTACK, pHeroA->GetRank(), pHeroA->GetLevel(), pHeroA->IsEvolved() );
	UInt iStatB = GameDataFn->GetHeroBaseStat( pHeroB->GetName(), HERO_STAT_ATTACK, pHeroB->GetRank(), pHeroB->GetLevel(), pHeroB->IsEvolved() );
	Int iRes = 0;
	if ( iStatA < iStatB )      iRes = +1;
	else if ( iStatA > iStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroDEF( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const Hero * pHeroA = CCGOPFn->GetHero( iHeroA );
	const Hero * pHeroB = CCGOPFn->GetHero( iHeroB );
	UInt iStatA = GameDataFn->GetHeroBaseStat( pHeroA->GetName(), HERO_STAT_DEFENSE, pHeroA->GetRank(), pHeroA->GetLevel(), pHeroA->IsEvolved() );
	UInt iStatB = GameDataFn->GetHeroBaseStat( pHeroB->GetName(), HERO_STAT_DEFENSE, pHeroB->GetRank(), pHeroB->GetLevel(), pHeroB->IsEvolved() );
	Int iRes = 0;
	if ( iStatA < iStatB )      iRes = +1;
	else if ( iStatA > iStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroSPD( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const Hero * pHeroA = CCGOPFn->GetHero( iHeroA );
	const Hero * pHeroB = CCGOPFn->GetHero( iHeroB );
	UInt iStatA = GameDataFn->GetHeroBaseStat( pHeroA->GetName(), HERO_STAT_SPEED, pHeroA->GetRank(), pHeroA->GetLevel(), pHeroA->IsEvolved() );
	UInt iStatB = GameDataFn->GetHeroBaseStat( pHeroB->GetName(), HERO_STAT_SPEED, pHeroB->GetRank(), pHeroB->GetLevel(), pHeroB->IsEvolved() );
	Int iRes = 0;
	if ( iStatA < iStatB )      iRes = +1;
	else if ( iStatA > iStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroCritRate( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const Hero * pHeroA = CCGOPFn->GetHero( iHeroA );
	const Hero * pHeroB = CCGOPFn->GetHero( iHeroB );
	UInt iStatA = GameDataFn->GetHeroBaseStat( pHeroA->GetName(), HERO_STAT_CRIT_RATE, pHeroA->GetRank(), pHeroA->GetLevel(), pHeroA->IsEvolved() );
	UInt iStatB = GameDataFn->GetHeroBaseStat( pHeroB->GetName(), HERO_STAT_CRIT_RATE, pHeroB->GetRank(), pHeroB->GetLevel(), pHeroB->IsEvolved() );
	Int iRes = 0;
	if ( iStatA < iStatB )      iRes = +1;
	else if ( iStatA > iStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroCritDmg( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const Hero * pHeroA = CCGOPFn->GetHero( iHeroA );
	const Hero * pHeroB = CCGOPFn->GetHero( iHeroB );
	UInt iStatA = GameDataFn->GetHeroBaseStat( pHeroA->GetName(), HERO_STAT_CRIT_DMG, pHeroA->GetRank(), pHeroA->GetLevel(), pHeroA->IsEvolved() );
	UInt iStatB = GameDataFn->GetHeroBaseStat( pHeroB->GetName(), HERO_STAT_CRIT_DMG, pHeroB->GetRank(), pHeroB->GetLevel(), pHeroB->IsEvolved() );
	Int iRes = 0;
	if ( iStatA < iStatB )      iRes = +1;
	else if ( iStatA > iStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroHIT( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const Hero * pHeroA = CCGOPFn->GetHero( iHeroA );
	const Hero * pHeroB = CCGOPFn->GetHero( iHeroB );
	UInt iStatA = GameDataFn->GetHeroBaseStat( pHeroA->GetName(), HERO_STAT_HIT, pHeroA->GetRank(), pHeroA->GetLevel(), pHeroA->IsEvolved() );
	UInt iStatB = GameDataFn->GetHeroBaseStat( pHeroB->GetName(), HERO_STAT_HIT, pHeroB->GetRank(), pHeroB->GetLevel(), pHeroB->IsEvolved() );
	Int iRes = 0;
	if ( iStatA < iStatB )      iRes = +1;
	else if ( iStatA > iStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIHeroTableModel::_Compare_HeroRES( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const Hero * pHeroA = CCGOPFn->GetHero( iHeroA );
	const Hero * pHeroB = CCGOPFn->GetHero( iHeroB );
	UInt iStatA = GameDataFn->GetHeroBaseStat( pHeroA->GetName(), HERO_STAT_RESISTANCE, pHeroA->GetRank(), pHeroA->GetLevel(), pHeroA->IsEvolved() );
	UInt iStatB = GameDataFn->GetHeroBaseStat( pHeroB->GetName(), HERO_STAT_RESISTANCE, pHeroB->GetRank(), pHeroB->GetLevel(), pHeroB->IsEvolved() );
	Int iRes = 0;
	if ( iStatA < iStatB )      iRes = +1;
	else if ( iStatA > iStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroTableGroupModel implementation
UIHeroTableGroupModel::UIHeroTableGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_GROUP)
{
	m_pGUI = NULL;
}
UIHeroTableGroupModel::~UIHeroTableGroupModel()
{
	// nothing to do
}

Void UIHeroTableGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Table Options :") );
}

const WinGUILayout * UIHeroTableGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(6,0,0,2) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_ROOM_WIDTH );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ROOM_TOP;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroTableSelectAllModel implementation
UIHeroTableSelectAllModel::UIHeroTableSelectAllModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_SELECTALL)
{
	m_pGUI = NULL;
}
UIHeroTableSelectAllModel::~UIHeroTableSelectAllModel()
{
	// nothing to do
}

Void UIHeroTableSelectAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Select All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroTableSelectAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIHeroTableSelectAllModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pHeroTable->SelectItem( i, true );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroTableUnselectAllModel implementation
UIHeroTableUnselectAllModel::UIHeroTableUnselectAllModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_UNSELECTALL)
{
	m_pGUI = NULL;
}
UIHeroTableUnselectAllModel::~UIHeroTableUnselectAllModel()
{
	// nothing to do
}

Void UIHeroTableUnselectAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Unselect All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroTableUnselectAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIHeroTableUnselectAllModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pHeroTable->SelectItem( i, false );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroTableCheckAllModel implementation
UIHeroTableCheckAllModel::UIHeroTableCheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_CHECKALL)
{
	m_pGUI = NULL;
}
UIHeroTableCheckAllModel::~UIHeroTableCheckAllModel()
{
	// nothing to do
}

Void UIHeroTableCheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Check All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroTableCheckAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,1);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIHeroTableCheckAllModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pHeroTable->CheckItem( i, true );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroTableUncheckAllModel implementation
UIHeroTableUncheckAllModel::UIHeroTableUncheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_UNCHECKALL)
{
	m_pGUI = NULL;
}
UIHeroTableUncheckAllModel::~UIHeroTableUncheckAllModel()
{
	// nothing to do
}

Void UIHeroTableUncheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Uncheck All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroTableUncheckAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(3,0,0,1);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIHeroTableUncheckAllModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pHeroTable->CheckItem( i, false );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroTableCheckSelectedModel implementation
UIHeroTableCheckSelectedModel::UIHeroTableCheckSelectedModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_CHECKSELECTED)
{
	m_pGUI = NULL;
}
UIHeroTableCheckSelectedModel::~UIHeroTableCheckSelectedModel()
{
	// nothing to do
}

Void UIHeroTableCheckSelectedModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Check Selected") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroTableCheckSelectedModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(4,0,0,2);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIHeroTableCheckSelectedModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemSelected(i) )
			pHeroTable->CheckItem( i, true );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroTableUncheckSelectedModel implementation
UIHeroTableUncheckSelectedModel::UIHeroTableUncheckSelectedModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_UNCHECKSELECTED)
{
	m_pGUI = NULL;
}
UIHeroTableUncheckSelectedModel::~UIHeroTableUncheckSelectedModel()
{
	// nothing to do
}

Void UIHeroTableUncheckSelectedModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Uncheck Selected") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroTableUncheckSelectedModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(5,0,0,2);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIHeroTableUncheckSelectedModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemSelected(i) )
			pHeroTable->CheckItem( i, false );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroTable implementation
UIHeroTable::UIHeroTable( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pHeroTable = NULL;

	m_pGroup = NULL;
	m_pSelectAll = NULL;
	m_pUnselectAll = NULL;
	m_pCheckAll = NULL;
	m_pUncheckAll = NULL;
	m_pCheckSelected = NULL;
	m_pUncheckSelected = NULL;
}
UIHeroTable::~UIHeroTable()
{
	// nothing to do
}

Void UIHeroTable::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_HERO_EXPLORER );

	// Build Hero Table UI
	m_hHeroTableModel.Initialize( m_pGUI );
	m_pHeroTable = WinGUIFn->CreateTable( m_pRoot, &m_hHeroTableModel );
	m_hHeroTableModel.CreateColumns();

	m_hGroup.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroup );

	m_hSelectAll.Initialize( m_pGUI );
	m_pSelectAll = WinGUIFn->CreateButton( m_pRoot, &m_hSelectAll );

	m_hUnselectAll.Initialize( m_pGUI );
	m_pUnselectAll = WinGUIFn->CreateButton( m_pRoot, &m_hUnselectAll );

	m_hCheckAll.Initialize( m_pGUI );
	m_pCheckAll = WinGUIFn->CreateButton( m_pRoot, &m_hCheckAll );

	m_hUncheckAll.Initialize( m_pGUI );
	m_pUncheckAll = WinGUIFn->CreateButton( m_pRoot, &m_hUncheckAll );

	m_hCheckSelected.Initialize( m_pGUI );
	m_pCheckSelected = WinGUIFn->CreateButton( m_pRoot, &m_hCheckSelected );

	m_hUncheckSelected.Initialize( m_pGUI );
	m_pUncheckSelected = WinGUIFn->CreateButton( m_pRoot, &m_hUncheckSelected );
}
Void UIHeroTable::Cleanup()
{
	// nothing to do
}


