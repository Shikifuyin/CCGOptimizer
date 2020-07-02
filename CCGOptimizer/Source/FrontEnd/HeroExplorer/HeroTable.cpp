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
// HeroTableModel implementation
HeroTableModel::HeroTableModel():
	WinGUITableModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_TABLE)
{
	m_pGUI = NULL;

	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_NAME],       TEXT("Name") );
	StringFn->Copy( m_arrColumnNames[CCGOP_HEROTABLE_COLUMN_ID],         TEXT("ID") );
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

	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_NAME]       = 100;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_ID]         = 60;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_FACTION]    = 100;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_RANK]       = 60;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_LEVEL]      = 60;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_EVOLVED]    = 80;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_SANCTIFIED] = 80;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_HP]         = 60;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_ATT]        = 60;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_DEF]        = 60;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_SPD]        = 60;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_CRITRATE]   = 80;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_CRITDMG]    = 80;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_HIT]        = 60;
	m_arrColumnWidths[CCGOP_HEROTABLE_COLUMN_RES]        = 60;
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

	// Settings
	pTable->SetBackgroundColor( 0x00d0d0d0 );
	pTable->SetTextBackgroundColor( 0x00d0d0d0 );
	pTable->ShowGridLines( true );
	pTable->ToggleFullRowSelection( true );
	pTable->ToggleAlwaysShowSelection( true );

	// Build Columns
	for( UInt i = 0; i < CCGOP_HEROTABLE_COLUMN_COUNT; ++i ) {
		pTable->AddColumn( i, m_arrColumnNames[i], i, i, m_arrColumnWidths[i] );
		pTable->SetColumnRowTextAlign( i, WINGUI_TABLE_TEXT_ALIGN_CENTER );
	}
}

Void HeroTableModel::UpdateAfterHeroCreation( HeroID iHeroID )
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	UInt iIndex = pTable->GetItemCount();

	pTable->AddItem( iIndex ); // Append
	pTable->SetItemData( iIndex, (Void*)iHeroID );
}
Void HeroTableModel::UpdateAfterDataLoad()
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

const WinGUILayout * HeroTableModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_SPACING_BORDER;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TABLE_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TABLE_HEIGHT;

	return &hLayout;
}

Bool HeroTableModel::OnColumnHeaderClick( UInt iIndex )
{
	static Bool arrToggles[CCGOP_HEROTABLE_COLUMN_COUNT] = {
		true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true
	};

	WinGUITable * pTable = (WinGUITable*)m_pController;

	switch( iIndex ) {
		case CCGOP_HEROTABLE_COLUMN_NAME:       pTable->SortItemsByData( _Compare_HeroName,       arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_ID:         pTable->SortItemsByData( _Compare_HeroID,         arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_FACTION:    pTable->SortItemsByData( _Compare_HeroFaction,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_RANK:       pTable->SortItemsByData( _Compare_HeroRank,       arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_LEVEL:      pTable->SortItemsByData( _Compare_HeroLevel,      arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_EVOLVED:    pTable->SortItemsByData( _Compare_HeroEvolved,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_SANCTIFIED: pTable->SortItemsByData( _Compare_HeroSanctified, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_HP:         pTable->SortItemsByData( _Compare_HeroHP,         arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_ATT:        pTable->SortItemsByData( _Compare_HeroATT,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_DEF:        pTable->SortItemsByData( _Compare_HeroDEF,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_SPD:        pTable->SortItemsByData( _Compare_HeroSPD,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_CRITRATE:   pTable->SortItemsByData( _Compare_HeroCritRate,   arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_CRITDMG:    pTable->SortItemsByData( _Compare_HeroCritDmg,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_HIT:        pTable->SortItemsByData( _Compare_HeroHIT,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_HEROTABLE_COLUMN_RES:        pTable->SortItemsByData( _Compare_HeroRES,        arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		default: Assert(false); break;
	}

	return true;
}

GChar * HeroTableModel::OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData )
{
	Assert( iItemIndex < CCGOPFn->GetHeroCount() );
	Assert( iSubItemIndex < CCGOP_HEROTABLE_COLUMN_COUNT );

	WinGUITable * pTable = (WinGUITable*)m_pController;

	static GChar strBuffer[64];

	HeroID iHeroID = (HeroID)(UIntPtr)( pTable->GetItemData(iItemIndex) );
	const Hero * pHero = CCGOPFn->GetHero( iHeroID );
	UInt iStatValue;

	switch( iSubItemIndex ) {
		case CCGOP_HEROTABLE_COLUMN_NAME:
			StringFn->NCopy( strBuffer, pHero->GetName(), 63 );
			break;
		case CCGOP_HEROTABLE_COLUMN_ID:
			StringFn->FromUInt( strBuffer, pHero->GetID() );
			break;
		case CCGOP_HEROTABLE_COLUMN_FACTION:
			StringFn->NCopy( strBuffer, GameDataFn->GetHeroFactionName(pHero->GetFaction()), 63 );
			break;
		case CCGOP_HEROTABLE_COLUMN_RANK:
			StringFn->NCopy( strBuffer, GameDataFn->GetHeroRankName(pHero->GetRank()), 63 );
			break;
		case CCGOP_HEROTABLE_COLUMN_LEVEL:
			StringFn->FromUInt( strBuffer, pHero->GetLevel() );
			break;
		case CCGOP_HEROTABLE_COLUMN_EVOLVED:
			StringFn->NCopy( strBuffer, pHero->IsEvolved() ? TEXT("Yes") : TEXT("No"), 63 );
			break;
		case CCGOP_HEROTABLE_COLUMN_SANCTIFIED:
			StringFn->NCopy( strBuffer, GameDataFn->GetHeroSanctifyName(pHero->GetSanctification()), 63 );
			break;
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
			StringFn->Format( strBuffer, TEXT("%d%%"), iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_CRITDMG:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_CRIT_DMG, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->Format( strBuffer, TEXT("%d%%"), iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_HIT:
			iStatValue = GameDataFn->GetHeroBaseStat(
				pHero->GetName(), HERO_STAT_HIT, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved()
			);
			StringFn->Format( strBuffer, TEXT("%d%%"), iStatValue );
			break;
		case CCGOP_HEROTABLE_COLUMN_RES:
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

Int __stdcall HeroTableModel::_Compare_HeroName( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	const GChar * strNameA = CCGOPFn->GetHero(iHeroA)->GetName();
	const GChar * strNameB = CCGOPFn->GetHero(iHeroB)->GetName();
	Int iRes = StringFn->NCmp(strNameA, strNameB, GAMEDATA_NAMES_MAX_LENGTH - 1);
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall HeroTableModel::_Compare_HeroID( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	HeroID iHeroA = (HeroID)(IntPtr)pItemDataA;
	HeroID iHeroB = (HeroID)(IntPtr)pItemDataB;
	Int iRes = 0;
	if ( iHeroA < iHeroB )      iRes = +1;
	else if ( iHeroA > iHeroB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall HeroTableModel::_Compare_HeroFaction( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroRank( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroLevel( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroEvolved( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroSanctified( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroHP( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroATT( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroDEF( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroSPD( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroCritRate( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroCritDmg( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroHIT( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall HeroTableModel::_Compare_HeroRES( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
// HeroTableGroupModel implementation
HeroTableGroupModel::HeroTableGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_GROUP)
{
	m_pGUI = NULL;
}
HeroTableGroupModel::~HeroTableGroupModel()
{
	// nothing to do
}

Void HeroTableGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Table Options :") );
}

const WinGUILayout * HeroTableGroupModel::GetLayout() const
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
// HeroTableSelectAllModel implementation
HeroTableSelectAllModel::HeroTableSelectAllModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_SELECTALL)
{
	m_pGUI = NULL;
}
HeroTableSelectAllModel::~HeroTableSelectAllModel()
{
	// nothing to do
}

Void HeroTableSelectAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Select All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroTableSelectAllModel::GetLayout() const
{
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();
	WinGUIGroupBox * pGroupBox = pHeroTable->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroTableSelectAllModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pHeroTable->SelectItem( i, true );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroTableUnselectAllModel implementation
HeroTableUnselectAllModel::HeroTableUnselectAllModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_UNSELECTALL)
{
	m_pGUI = NULL;
}
HeroTableUnselectAllModel::~HeroTableUnselectAllModel()
{
	// nothing to do
}

Void HeroTableUnselectAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Unselect All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroTableUnselectAllModel::GetLayout() const
{
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();
	WinGUIGroupBox * pGroupBox = pHeroTable->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroTableUnselectAllModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pHeroTable->SelectItem( i, false );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroTableCheckAllModel implementation
HeroTableCheckAllModel::HeroTableCheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_CHECKALL)
{
	m_pGUI = NULL;
}
HeroTableCheckAllModel::~HeroTableCheckAllModel()
{
	// nothing to do
}

Void HeroTableCheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Check All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroTableCheckAllModel::GetLayout() const
{
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();
	WinGUIGroupBox * pGroupBox = pHeroTable->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,1);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroTableCheckAllModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pHeroTable->CheckItem( i, true );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroTableUncheckAllModel implementation
HeroTableUncheckAllModel::HeroTableUncheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_UNCHECKALL)
{
	m_pGUI = NULL;
}
HeroTableUncheckAllModel::~HeroTableUncheckAllModel()
{
	// nothing to do
}

Void HeroTableUncheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Uncheck All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroTableUncheckAllModel::GetLayout() const
{
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();
	WinGUIGroupBox * pGroupBox = pHeroTable->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(3,0,0,1);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroTableUncheckAllModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pHeroTable->CheckItem( i, false );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroTableCheckSelectedModel implementation
HeroTableCheckSelectedModel::HeroTableCheckSelectedModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_CHECKSELECTED)
{
	m_pGUI = NULL;
}
HeroTableCheckSelectedModel::~HeroTableCheckSelectedModel()
{
	// nothing to do
}

Void HeroTableCheckSelectedModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Check Selected") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroTableCheckSelectedModel::GetLayout() const
{
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();
	WinGUIGroupBox * pGroupBox = pHeroTable->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(4,0,0,2);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroTableCheckSelectedModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemSelected(i) )
			pHeroTable->CheckItem( i, true );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroTableUncheckSelectedModel implementation
HeroTableUncheckSelectedModel::HeroTableUncheckSelectedModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROTABLE_UNCHECKSELECTED)
{
	m_pGUI = NULL;
}
HeroTableUncheckSelectedModel::~HeroTableUncheckSelectedModel()
{
	// nothing to do
}

Void HeroTableUncheckSelectedModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Uncheck Selected") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroTableUncheckSelectedModel::GetLayout() const
{
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();
	WinGUIGroupBox * pGroupBox = pHeroTable->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(5,0,0,2);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroTableUncheckSelectedModel::OnClick()
{
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	UInt iItemCount = pHeroTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemSelected(i) )
			pHeroTable->CheckItem( i, false );
	}

	pHeroTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroTable implementation
HeroTable::HeroTable( CCGOPGUI * pGUI )
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
HeroTable::~HeroTable()
{
	// nothing to do
}

Void HeroTable::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_HERO_EXPLORER );

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
Void HeroTable::Cleanup()
{
	// nothing to do
}


