/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneTable.cpp
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
// Includes
#include "RuneTable.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIRuneTableModel implementation
UIRuneTableModel::UIRuneTableModel():
	WinGUITableModel(CCGOP_RESID_RUNEEXPLORER_RUNETABLE_TABLE)
{
	m_pGUI = NULL;

	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_ID],                  TEXT("ID") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_LOCKED],              TEXT("Locked") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_SLOT],                TEXT("Slot") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_SET],                 TEXT("Set") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANK],                TEXT("Rank") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_QUALITY],             TEXT("Quality") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_LEVEL],               TEXT("Level") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_MAINSTAT],            TEXT("MainStat") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_MAINSTAT_VALUE],      TEXT("MainStat Val") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_INNATESTAT],          TEXT("InnateStat") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_INNATESTAT_VALUE],    TEXT("InnateStat Val") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_PC],    TEXT("HP%") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_FLAT],  TEXT("HP") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_PC],   TEXT("ATT%") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_FLAT], TEXT("ATT") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_PC],   TEXT("DEF%") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_FLAT], TEXT("DEF") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_SPD],      TEXT("SPD") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITRATE], TEXT("CritRate") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITDMG],  TEXT("CritDmg") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_HIT],      TEXT("HIT") );
	StringFn->Copy( m_arrColumnNames[UI_RUNETABLE_COLUMN_RANDOMSTAT_RES],      TEXT("RES") );

	UInt iTableWidth = ( CCGOP_LAYOUT_RUNEEXPLORER_TABLE_WIDTH - CCGOP_LAYOUT_SCROLLBAR_WIDTH );
	UInt iAvgWidth = ( iTableWidth / UI_RUNETABLE_COLUMN_COUNT );

	m_arrColumnWidths[UI_RUNETABLE_COLUMN_ID]                  = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_LOCKED]              = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_SLOT]                = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_SET]                 = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANK]                = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_QUALITY]             = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_LEVEL]               = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_MAINSTAT]            = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_MAINSTAT_VALUE]      = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_INNATESTAT]          = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_INNATESTAT_VALUE]    = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_PC]    = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_FLAT]  = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_PC]   = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_FLAT] = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_PC]   = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_FLAT] = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_SPD]      = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITRATE] = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITDMG]  = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_HIT]      = iAvgWidth;
	m_arrColumnWidths[UI_RUNETABLE_COLUMN_RANDOMSTAT_RES]      = iAvgWidth;
}
UIRuneTableModel::~UIRuneTableModel()
{
	// nothing to do
}

Void UIRuneTableModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneTableModel::CreateColumns()
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	// Settings
	pTable->SetBackgroundColor( 0x00d0d0d0 );
	pTable->SetTextBackgroundColor( 0x00d0d0d0 );
	pTable->ShowGridLines( true );
	pTable->ToggleFullRowSelection( true );
	pTable->ToggleAlwaysShowSelection( true );

	// Build Columns
	for( UInt i = 0; i < UI_RUNETABLE_COLUMN_COUNT; ++i ) {
		pTable->AddColumn( i, m_arrColumnNames[i], i, i, m_arrColumnWidths[i] );
		pTable->SetColumnRowTextAlign( i, WINGUI_TABLE_TEXT_ALIGN_CENTER );
	}
}

Void UIRuneTableModel::UpdateAfterRuneCreation( RuneID iRuneID )
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	UInt iIndex = pTable->GetItemCount();

	pTable->AddItem( iIndex ); // Append
	pTable->SetItemData( iIndex, (Void*)iRuneID );
}
Void UIRuneTableModel::UpdateAfterDataLoad()
{
	WinGUITable * pTable = (WinGUITable*)m_pController;
	Assert( pTable->GetItemCount() == 0 );

	UInt iIndex = 0;
	RuneInventory::RuneMap::Iterator itRune = CCGOPFn->EnumRunes();
	while( !(itRune.IsNull()) ) {

		pTable->AddItem( iIndex );
		pTable->SetItemData( iIndex, (Void*)(itRune.GetKey()) );

		++iIndex;
		++itRune;
	}
}
Void UIRuneTableModel::UpdateAfterFiltering( const Array<RuneID> & arrFilteredRunes )
{
	WinGUITable * pTable = (WinGUITable*)m_pController;
	Assert( pTable->GetItemCount() == 0 );

	UInt iRuneCount = arrFilteredRunes.Count();
	for( UInt i = 0; i < iRuneCount; ++i ) {
		pTable->AddItem( i );
		pTable->SetItemData( i, (Void*)(arrFilteredRunes[i]) );
	}
}

const WinGUILayout * UIRuneTableModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_SPACING_BORDER;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_RUNEEXPLORER_TABLE_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_RUNEEXPLORER_TABLE_HEIGHT;

	return &hLayout;
}

Bool UIRuneTableModel::OnColumnHeaderClick( UInt iIndex )
{
	static Bool arrToggles[UI_RUNETABLE_COLUMN_COUNT] = {
		true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,
		true, true, true, true, true, true
	};

	WinGUITable * pTable = (WinGUITable*)m_pController;

	switch( iIndex ) {
		case UI_RUNETABLE_COLUMN_ID:                  pTable->SortItemsByData( _Compare_RuneID,                 arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_LOCKED:              pTable->SortItemsByData( _Compare_RuneLocked,             arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_SLOT:                pTable->SortItemsByData( _Compare_RuneSlot,               arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_SET:                 pTable->SortItemsByData( _Compare_RuneSet,                arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANK:                pTable->SortItemsByData( _Compare_RuneRank,               arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_QUALITY:             pTable->SortItemsByData( _Compare_RuneQuality,            arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_LEVEL:               pTable->SortItemsByData( _Compare_RuneLevel,              arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_MAINSTAT:            pTable->SortItemsByData( _Compare_RuneMainStat,           arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_MAINSTAT_VALUE:      pTable->SortItemsByData( _Compare_RuneMainStatValue,      arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_INNATESTAT:          pTable->SortItemsByData( _Compare_RuneInnateStat,         arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_INNATESTAT_VALUE:    pTable->SortItemsByData( _Compare_RuneInnateStatValue,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_PC:    pTable->SortItemsByData( _Compare_RuneRandomStatHPPc,     arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_FLAT:  pTable->SortItemsByData( _Compare_RuneRandomStatHPFlat,   arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_PC:   pTable->SortItemsByData( _Compare_RuneRandomStatATTPc,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_FLAT: pTable->SortItemsByData( _Compare_RuneRandomStatATTFlat,  arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_PC:   pTable->SortItemsByData( _Compare_RuneRandomStatDEFPc,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_FLAT: pTable->SortItemsByData( _Compare_RuneRandomStatDEFFlat,  arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_SPD:      pTable->SortItemsByData( _Compare_RuneRandomStatSPD,      arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITRATE: pTable->SortItemsByData( _Compare_RuneRandomStatCritRate, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITDMG:  pTable->SortItemsByData( _Compare_RuneRandomStatCritDmg,  arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_HIT:      pTable->SortItemsByData( _Compare_RuneRandomStatHIT,      arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_RES:      pTable->SortItemsByData( _Compare_RuneRandomStatRES,      arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		default: Assert(false); break;
	}

	return true;
}

GChar * UIRuneTableModel::OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData )
{
	Assert( iItemIndex < CCGOPFn->GetRuneCount() );
	Assert( iSubItemIndex < UI_RUNETABLE_COLUMN_COUNT );

	WinGUITable * pTable = (WinGUITable*)m_pController;

	static GChar strBuffer[64];

	RuneID iRuneID = (RuneID)(UIntPtr)( pTable->GetItemData(iItemIndex) );
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	switch( iSubItemIndex ) {
		case UI_RUNETABLE_COLUMN_ID:
			StringFn->FromUInt( strBuffer, pRune->GetID() );
			break;
		case UI_RUNETABLE_COLUMN_LOCKED:
			StringFn->NCopy( strBuffer, (pRune->IsLocked() ? TEXT("Yes") : TEXT("No")), 63 );
			break;
		case UI_RUNETABLE_COLUMN_SLOT:
			StringFn->FromUInt( strBuffer, pRune->GetSlot() + 1 );
			break;
		case UI_RUNETABLE_COLUMN_SET:
			StringFn->NCopy( strBuffer, GameDataFn->GetRuneSetName(pRune->GetSet()), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANK:
			StringFn->NCopy( strBuffer, GameDataFn->GetRuneRankName(pRune->GetRank()), 63 );
			break;
		case UI_RUNETABLE_COLUMN_QUALITY:
			StringFn->NCopy( strBuffer, GameDataFn->GetRuneQualityName(pRune->GetQuality()), 63 );
			break;
		case UI_RUNETABLE_COLUMN_LEVEL:
			StringFn->FromUInt( strBuffer, pRune->GetLevel() );
			break;
		case UI_RUNETABLE_COLUMN_MAINSTAT:
			StringFn->NCopy( strBuffer, GameDataFn->GetRuneStatName(pRune->GetMainStat()), 63 );
			break;
		case UI_RUNETABLE_COLUMN_MAINSTAT_VALUE:
			StringFn->FromUInt( strBuffer, pRune->GetMainStatValue() );
			break;
		case UI_RUNETABLE_COLUMN_INNATESTAT:
			if ( pRune->GetInnateStat() != RUNE_STAT_COUNT )
				StringFn->NCopy( strBuffer, GameDataFn->GetRuneStatName(pRune->GetInnateStat()), 63 );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_INNATESTAT_VALUE:
			if ( pRune->GetInnateStat() != RUNE_STAT_COUNT )
				StringFn->FromUInt( strBuffer, pRune->GetInnateStatValue() );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_PC:
			if ( pRune->HasRandomStat(RUNE_STAT_HP_PERCENT) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_HP_PERCENT) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_HP_FLAT:
			if ( pRune->HasRandomStat(RUNE_STAT_HP_FLAT) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_HP_FLAT) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_PC:
			if ( pRune->HasRandomStat(RUNE_STAT_ATTACK_PERCENT) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_ATTACK_PERCENT) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_ATT_FLAT:
			if ( pRune->HasRandomStat(RUNE_STAT_ATTACK_FLAT) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_ATTACK_FLAT) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_PC:
			if ( pRune->HasRandomStat(RUNE_STAT_DEFENSE_PERCENT) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_DEFENSE_PERCENT) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_DEF_FLAT:
			if ( pRune->HasRandomStat(RUNE_STAT_DEFENSE_FLAT) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_DEFENSE_FLAT) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_SPD:
			if ( pRune->HasRandomStat(RUNE_STAT_SPEED) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_SPEED) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITRATE:
			if ( pRune->HasRandomStat(RUNE_STAT_CRIT_RATE) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_CRIT_RATE) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_CRITDMG:
			if ( pRune->HasRandomStat(RUNE_STAT_CRIT_DMG) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_CRIT_DMG) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_HIT:
			if ( pRune->HasRandomStat(RUNE_STAT_HIT) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_HIT) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		case UI_RUNETABLE_COLUMN_RANDOMSTAT_RES:
			if ( pRune->HasRandomStat(RUNE_STAT_RESISTANCE) )
				StringFn->FromUInt( strBuffer, pRune->GetRandomStatValue(RUNE_STAT_RESISTANCE) );
			else
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			break;
		default: Assert(false); break;
	}

	return strBuffer;
}

/////////////////////////////////////////////////////////////////////////////////

Int __stdcall UIRuneTableModel::_Compare_RuneID( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	Int iRes = 0;
	if ( iRuneA < iRuneB )      iRes = +1;
	else if ( iRuneA > iRuneB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneLocked( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	Bool bLockedA = CCGOPFn->GetRune(iRuneA)->IsLocked();
	Bool bLockedB = CCGOPFn->GetRune(iRuneB)->IsLocked();
	Int iRes = 0;
	if ( bLockedA && !bLockedB )      iRes = +1;
	else if ( !bLockedA && bLockedB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneSlot( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iSlotA = CCGOPFn->GetRune(iRuneA)->GetSlot();
	UInt iSlotB = CCGOPFn->GetRune(iRuneB)->GetSlot();
	Int iRes = 0;
	if ( iSlotA < iSlotB )      iRes = +1;
	else if ( iSlotA > iSlotB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneSet( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	RuneSet iSetA = CCGOPFn->GetRune(iRuneA)->GetSet();
	RuneSet iSetB = CCGOPFn->GetRune(iRuneB)->GetSet();
	Int iRes = 0;
	if ( iSetA < iSetB )      iRes = +1;
	else if ( iSetA > iSetB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRank( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	RuneRank iRankA = CCGOPFn->GetRune(iRuneA)->GetRank();
	RuneRank iRankB = CCGOPFn->GetRune(iRuneB)->GetRank();
	Int iRes = 0;
	if ( iRankA < iRankB )      iRes = +1;
	else if ( iRankA > iRankB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneQuality( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	RuneQuality iQualityA = CCGOPFn->GetRune(iRuneA)->GetQuality();
	RuneQuality iQualityB = CCGOPFn->GetRune(iRuneB)->GetQuality();
	Int iRes = 0;
	if ( iQualityA < iQualityB )      iRes = +1;
	else if ( iQualityA > iQualityB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneLevel( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iLevelA = CCGOPFn->GetRune(iRuneA)->GetLevel();
	UInt iLevelB = CCGOPFn->GetRune(iRuneB)->GetLevel();
	Int iRes = 0;
	if ( iLevelA < iLevelB )      iRes = +1;
	else if ( iLevelA > iLevelB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneMainStat( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	RuneStat iMainStatA = CCGOPFn->GetRune(iRuneA)->GetMainStat();
	RuneStat iMainStatB = CCGOPFn->GetRune(iRuneB)->GetMainStat();
	Int iRes = 0;
	if ( iMainStatA < iMainStatB )      iRes = +1;
	else if ( iMainStatA > iMainStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneMainStatValue( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iMainStatValueA = CCGOPFn->GetRune(iRuneA)->GetMainStatValue();
	UInt iMainStatValueB = CCGOPFn->GetRune(iRuneB)->GetMainStatValue();
	Int iRes = 0;
	if ( iMainStatValueA < iMainStatValueB )      iRes = +1;
	else if ( iMainStatValueA > iMainStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneInnateStat( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	RuneStat iInnateStatA = CCGOPFn->GetRune(iRuneA)->GetInnateStat();
	RuneStat iInnateStatB = CCGOPFn->GetRune(iRuneB)->GetInnateStat();
	Int iRes = 0;
	if ( iInnateStatA < iInnateStatB )      iRes = +1;
	else if ( iInnateStatA > iInnateStatB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneInnateStatValue( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iInnateStatValueA = CCGOPFn->GetRune(iRuneA)->GetInnateStatValue();
	UInt iInnateStatValueB = CCGOPFn->GetRune(iRuneB)->GetInnateStatValue();
	Int iRes = 0;
	if ( iInnateStatValueA < iInnateStatValueB )      iRes = +1;
	else if ( iInnateStatValueA > iInnateStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatHPPc( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_HP_PERCENT );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_HP_PERCENT );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatHPFlat( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_HP_FLAT );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_HP_FLAT );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatATTPc( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_ATTACK_PERCENT );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_ATTACK_PERCENT );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatATTFlat( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_ATTACK_FLAT );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_ATTACK_FLAT );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatDEFPc( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_DEFENSE_PERCENT );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_DEFENSE_PERCENT );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatDEFFlat( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_DEFENSE_FLAT );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_DEFENSE_FLAT );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatSPD( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_SPEED );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_SPEED );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatCritRate( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_CRIT_RATE );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_CRIT_RATE );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatCritDmg( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_CRIT_DMG );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_CRIT_DMG );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatHIT( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_HIT );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_HIT );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIRuneTableModel::_Compare_RuneRandomStatRES( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	RuneID iRuneA = (RuneID)(IntPtr)pItemDataA;
	RuneID iRuneB = (RuneID)(IntPtr)pItemDataB;
	UInt iRandomStatValueA = CCGOPFn->GetRune(iRuneA)->GetRandomStatValue( RUNE_STAT_RESISTANCE );
	UInt iRandomStatValueB = CCGOPFn->GetRune(iRuneB)->GetRandomStatValue( RUNE_STAT_RESISTANCE );
	Int iRes = 0;
	if ( iRandomStatValueA < iRandomStatValueB )      iRes = +1;
	else if ( iRandomStatValueA > iRandomStatValueB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneTableGroupModel implementation
UIRuneTableGroupModel::UIRuneTableGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNETABLE_GROUP)
{
	m_pGUI = NULL;
}
UIRuneTableGroupModel::~UIRuneTableGroupModel()
{
	// nothing to do
}

Void UIRuneTableGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Table Options :") );
}

const WinGUILayout * UIRuneTableGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(6,0,0,2) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_RUNEEXPLORER_ROOM_LEFT + CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_RUNEEXPLORER_ROOM_WIDTH );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_RUNEEXPLORER_ROOM_TOP;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneTableSelectAllModel implementation
UIRuneTableSelectAllModel::UIRuneTableSelectAllModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNETABLE_SELECTALL)
{
	m_pGUI = NULL;
}
UIRuneTableSelectAllModel::~UIRuneTableSelectAllModel()
{
	// nothing to do
}

Void UIRuneTableSelectAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Select All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneTableSelectAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIRuneTableSelectAllModel::OnClick()
{
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();

	UInt iItemCount = pRuneTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pRuneTable->SelectItem( i, true );
	}

	pRuneTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneTableUnselectAllModel implementation
UIRuneTableUnselectAllModel::UIRuneTableUnselectAllModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNETABLE_UNSELECTALL)
{
	m_pGUI = NULL;
}
UIRuneTableUnselectAllModel::~UIRuneTableUnselectAllModel()
{
	// nothing to do
}

Void UIRuneTableUnselectAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Unselect All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneTableUnselectAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIRuneTableUnselectAllModel::OnClick()
{
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();

	UInt iItemCount = pRuneTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pRuneTable->SelectItem( i, false );
	}

	pRuneTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneTableCheckAllModel implementation
UIRuneTableCheckAllModel::UIRuneTableCheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNETABLE_CHECKALL)
{
	m_pGUI = NULL;
}
UIRuneTableCheckAllModel::~UIRuneTableCheckAllModel()
{
	// nothing to do
}

Void UIRuneTableCheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Check All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneTableCheckAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,1);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIRuneTableCheckAllModel::OnClick()
{
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();

	UInt iItemCount = pRuneTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pRuneTable->CheckItem( i, true );
	}

	pRuneTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneTableUncheckAllModel implementation
UIRuneTableUncheckAllModel::UIRuneTableUncheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNETABLE_UNCHECKALL)
{
	m_pGUI = NULL;
}
UIRuneTableUncheckAllModel::~UIRuneTableUncheckAllModel()
{
	// nothing to do
}

Void UIRuneTableUncheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Uncheck All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneTableUncheckAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(3,0,0,1);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIRuneTableUncheckAllModel::OnClick()
{
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();

	UInt iItemCount = pRuneTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pRuneTable->CheckItem( i, false );
	}

	pRuneTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneTableCheckSelectedModel implementation
UIRuneTableCheckSelectedModel::UIRuneTableCheckSelectedModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNETABLE_CHECKSELECTED)
{
	m_pGUI = NULL;
}
UIRuneTableCheckSelectedModel::~UIRuneTableCheckSelectedModel()
{
	// nothing to do
}

Void UIRuneTableCheckSelectedModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Check Selected") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneTableCheckSelectedModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(4,0,0,2);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIRuneTableCheckSelectedModel::OnClick()
{
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();

	UInt iItemCount = pRuneTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		if ( pRuneTable->IsItemSelected(i) )
			pRuneTable->CheckItem( i, true );
	}

	pRuneTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneTableUncheckSelectedModel implementation
UIRuneTableUncheckSelectedModel::UIRuneTableUncheckSelectedModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNETABLE_UNCHECKSELECTED)
{
	m_pGUI = NULL;
}
UIRuneTableUncheckSelectedModel::~UIRuneTableUncheckSelectedModel()
{
	// nothing to do
}

Void UIRuneTableUncheckSelectedModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Uncheck Selected") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneTableUncheckSelectedModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(5,0,0,2);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIRuneTableUncheckSelectedModel::OnClick()
{
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();

	UInt iItemCount = pRuneTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		if ( pRuneTable->IsItemSelected(i) )
			pRuneTable->CheckItem( i, false );
	}

	pRuneTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneTable implementation
UIRuneTable::UIRuneTable( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pRuneTable = NULL;

	m_pGroup = NULL;
	m_pSelectAll = NULL;
	m_pUnselectAll = NULL;
	m_pCheckAll = NULL;
	m_pUncheckAll = NULL;
	m_pCheckSelected = NULL;
	m_pUncheckSelected = NULL;
}
UIRuneTable::~UIRuneTable()
{
	// nothing to do
}

Void UIRuneTable::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_RUNE_EXPLORER );

	// Build Rune Table UI
	m_hRuneTableModel.Initialize( m_pGUI );
	m_pRuneTable = WinGUIFn->CreateTable( m_pRoot, &m_hRuneTableModel );
	m_hRuneTableModel.CreateColumns();

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
Void UIRuneTable::Cleanup()
{
	// nothing to do
}

