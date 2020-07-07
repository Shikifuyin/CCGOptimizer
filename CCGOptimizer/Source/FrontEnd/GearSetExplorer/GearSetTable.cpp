/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetTable.cpp
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
// Includes
#include "GearSetTable.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetTableModel implementation
UIGearSetTableModel::UIGearSetTableModel():
	WinGUITableModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE)
{
	m_pGUI = NULL;

	StringFn->Copy( m_arrColumnNames[UI_GEARSETTABLE_COLUMN_NAME],   TEXT("Name") );
	StringFn->Copy( m_arrColumnNames[UI_GEARSETTABLE_COLUMN_ID],     TEXT("ID") );
	StringFn->Copy( m_arrColumnNames[UI_GEARSETTABLE_COLUMN_RUNE_1], TEXT("Rune 1") );
	StringFn->Copy( m_arrColumnNames[UI_GEARSETTABLE_COLUMN_RUNE_2], TEXT("Rune 2") );
	StringFn->Copy( m_arrColumnNames[UI_GEARSETTABLE_COLUMN_RUNE_3], TEXT("Rune 3") );
	StringFn->Copy( m_arrColumnNames[UI_GEARSETTABLE_COLUMN_RUNE_4], TEXT("Rune 4") );
	StringFn->Copy( m_arrColumnNames[UI_GEARSETTABLE_COLUMN_RUNE_5], TEXT("Rune 5") );
	StringFn->Copy( m_arrColumnNames[UI_GEARSETTABLE_COLUMN_RUNE_6], TEXT("Rune 6") );

	UInt iTableWidth = (CCGOP_LAYOUT_TABLE_WIDTH >> 1);
	UInt iNameWidth = (2 * iTableWidth) / UI_GEARSETTABLE_COLUMN_COUNT;
	UInt iAvgWidth = (iTableWidth - iNameWidth) / (UI_GEARSETTABLE_COLUMN_COUNT - 1);
	iNameWidth = ( iTableWidth - iAvgWidth * (UI_GEARSETTABLE_COLUMN_COUNT - 1) );

	m_arrColumnWidths[UI_GEARSETTABLE_COLUMN_NAME]   = iNameWidth;
	m_arrColumnWidths[UI_GEARSETTABLE_COLUMN_ID]     = iAvgWidth;
	m_arrColumnWidths[UI_GEARSETTABLE_COLUMN_RUNE_1] = iAvgWidth;
	m_arrColumnWidths[UI_GEARSETTABLE_COLUMN_RUNE_2] = iAvgWidth;
	m_arrColumnWidths[UI_GEARSETTABLE_COLUMN_RUNE_3] = iAvgWidth;
	m_arrColumnWidths[UI_GEARSETTABLE_COLUMN_RUNE_4] = iAvgWidth;
	m_arrColumnWidths[UI_GEARSETTABLE_COLUMN_RUNE_5] = iAvgWidth;
	m_arrColumnWidths[UI_GEARSETTABLE_COLUMN_RUNE_6] = iAvgWidth;
}
UIGearSetTableModel::~UIGearSetTableModel()
{
	// nothing to do
}

Void UIGearSetTableModel::Initialize( CCGOPGUI * pGUI )
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
Void UIGearSetTableModel::CreateColumns()
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	// Settings
	pTable->SetBackgroundColor( 0x00d0d0d0 );
	pTable->SetTextBackgroundColor( 0x00d0d0d0 );
	pTable->ShowGridLines( true );

	pTable->ToggleSingleItemSelection( true );
	pTable->ToggleAlwaysShowSelection( true );
	pTable->ToggleFullRowSelection( true );

	// Build Columns
	for( UInt i = 0; i < UI_GEARSETTABLE_COLUMN_COUNT; ++i ) {
		pTable->AddColumn( i, m_arrColumnNames[i], i, i, m_arrColumnWidths[i] );
		pTable->SetColumnRowTextAlign( i, WINGUI_TABLE_TEXT_ALIGN_CENTER );
	}
}

Void UIGearSetTableModel::UpdateAfterGearSetCreation( GearSetID iGearSetID )
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	UInt iIndex = pTable->GetItemCount();

	pTable->AddItem( iIndex ); // Append
	pTable->SetItemData( iIndex, (Void*)iGearSetID );
}
Void UIGearSetTableModel::UpdateAfterDataLoad()
{
	WinGUITable * pTable = (WinGUITable*)m_pController;
	Assert( pTable->GetItemCount() == 0 );

	UInt iIndex = 0;
	GearSetInventory::GearSetMap::Iterator itGearSet = CCGOPFn->EnumGearSets();
	while( !(itGearSet.IsNull()) ) {

		pTable->AddItem( iIndex );
		pTable->SetItemData( iIndex, (Void*)(itGearSet.GetKey()) );

		++iIndex;
		++itGearSet;
	}
}

const WinGUILayout * UIGearSetTableModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = ( CCGOP_LAYOUT_TABLE_WIDTH >> 1 );
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TABLE_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_SPACING_BORDER;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	return &hLayout;
}

Bool UIGearSetTableModel::OnColumnHeaderClick( UInt iIndex )
{
	static Bool arrToggles[UI_GEARSETTABLE_COLUMN_COUNT] = {
		true, true, true, true, true, true, true, true
	};

	WinGUITable * pTable = (WinGUITable*)m_pController;

	switch( iIndex ) {
		case UI_GEARSETTABLE_COLUMN_NAME:   pTable->SortItemsByData( _Compare_GearSetName,  arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_GEARSETTABLE_COLUMN_ID:     pTable->SortItemsByData( _Compare_GearSetID,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_GEARSETTABLE_COLUMN_RUNE_1: pTable->SortItemsByData( _Compare_GearSetRune1, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_GEARSETTABLE_COLUMN_RUNE_2: pTable->SortItemsByData( _Compare_GearSetRune2, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_GEARSETTABLE_COLUMN_RUNE_3: pTable->SortItemsByData( _Compare_GearSetRune3, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_GEARSETTABLE_COLUMN_RUNE_4: pTable->SortItemsByData( _Compare_GearSetRune4, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_GEARSETTABLE_COLUMN_RUNE_5: pTable->SortItemsByData( _Compare_GearSetRune5, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case UI_GEARSETTABLE_COLUMN_RUNE_6: pTable->SortItemsByData( _Compare_GearSetRune6, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		default: Assert(false); break;
	}

	return true;
}

Bool UIGearSetTableModel::OnItemChanged( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData,
										 const WinGUITableItemState & hOldState, const WinGUITableItemState & hNewState,
										 const WinGUIPoint & hHotPoint )
{
	// Item Selection case
	if ( iItemIndex != INVALID_OFFSET && iSubItemIndex == 0 && (hOldState.bSelected != hNewState.bSelected) ) {
		// Update GearSet Slots Models
		for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
			m_pGUI->GetGearSetExplorer()->GetGearSetSlot(i)->UpdateModels();

		// Update GearSet Stats Model
		m_pGUI->GetGearSetExplorer()->GetGearSetStats()->UpdateModels();
	}

	// Done
	return true;
}

GChar * UIGearSetTableModel::OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData )
{
	Assert( iItemIndex < CCGOPFn->GetGearSetCount() );
	Assert( iSubItemIndex < UI_GEARSETTABLE_COLUMN_COUNT );

	WinGUITable * pTable = (WinGUITable*)m_pController;

	static GChar strBuffer[64];

	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pTable->GetItemData(iItemIndex) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	switch( iSubItemIndex ) {
		case UI_GEARSETTABLE_COLUMN_NAME:
			StringFn->NCopy( strBuffer, pGearSet->GetName(), 63 );
			break;
		case UI_GEARSETTABLE_COLUMN_ID:
			StringFn->FromUInt( strBuffer, pGearSet->GetID() );
			break;
		case UI_GEARSETTABLE_COLUMN_RUNE_1:
			if ( pGearSet->GetEquippedRune(0) == INVALID_OFFSET )
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			else
				StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(0) );
			break;
		case UI_GEARSETTABLE_COLUMN_RUNE_2:
			if ( pGearSet->GetEquippedRune(1) == INVALID_OFFSET )
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			else
				StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(1) );
			break;
		case UI_GEARSETTABLE_COLUMN_RUNE_3:
			if ( pGearSet->GetEquippedRune(2) == INVALID_OFFSET )
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			else
				StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(2) );
			break;
		case UI_GEARSETTABLE_COLUMN_RUNE_4:
			if ( pGearSet->GetEquippedRune(3) == INVALID_OFFSET )
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			else
				StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(3) );
			break;
		case UI_GEARSETTABLE_COLUMN_RUNE_5:
			if ( pGearSet->GetEquippedRune(4) == INVALID_OFFSET )
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			else
				StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(4) );
			break;
		case UI_GEARSETTABLE_COLUMN_RUNE_6:
			if ( pGearSet->GetEquippedRune(5) == INVALID_OFFSET )
				StringFn->NCopy( strBuffer, TEXT("---"), 63 );
			else
				StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(5) );
			break;
		default: Assert(false); break;
	}

	return strBuffer;
}

/////////////////////////////////////////////////////////////////////////////////

Int __stdcall UIGearSetTableModel::_Compare_GearSetName( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	const GChar * strNameA = CCGOPFn->GetGearSet(iGearSetA)->GetName();
	const GChar * strNameB = CCGOPFn->GetGearSet(iGearSetB)->GetName();
	Int iRes = StringFn->NCmp(strNameA, strNameB, GAMEDATA_NAMES_MAX_LENGTH - 1);
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIGearSetTableModel::_Compare_GearSetID( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	Int iRes = 0;
	if ( iGearSetA < iGearSetB )      iRes = +1;
	else if ( iGearSetA > iGearSetB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIGearSetTableModel::_Compare_GearSetRune1( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	RuneID iRuneA = CCGOPFn->GetGearSet(iGearSetA)->GetEquippedRune( 0 );
	RuneID iRuneB = CCGOPFn->GetGearSet(iGearSetB)->GetEquippedRune( 0 );
	Int iRes = 0;
	if ( iRuneA < iRuneB )      iRes = +1;
	else if ( iRuneA > iRuneB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIGearSetTableModel::_Compare_GearSetRune2( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	RuneID iRuneA = CCGOPFn->GetGearSet(iGearSetA)->GetEquippedRune( 1 );
	RuneID iRuneB = CCGOPFn->GetGearSet(iGearSetB)->GetEquippedRune( 1 );
	Int iRes = 0;
	if ( iRuneA < iRuneB )      iRes = +1;
	else if ( iRuneA > iRuneB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIGearSetTableModel::_Compare_GearSetRune3( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	RuneID iRuneA = CCGOPFn->GetGearSet(iGearSetA)->GetEquippedRune( 2 );
	RuneID iRuneB = CCGOPFn->GetGearSet(iGearSetB)->GetEquippedRune( 2 );
	Int iRes = 0;
	if ( iRuneA < iRuneB )      iRes = +1;
	else if ( iRuneA > iRuneB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIGearSetTableModel::_Compare_GearSetRune4( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	RuneID iRuneA = CCGOPFn->GetGearSet(iGearSetA)->GetEquippedRune( 3 );
	RuneID iRuneB = CCGOPFn->GetGearSet(iGearSetB)->GetEquippedRune( 3 );
	Int iRes = 0;
	if ( iRuneA < iRuneB )      iRes = +1;
	else if ( iRuneA > iRuneB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIGearSetTableModel::_Compare_GearSetRune5( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	RuneID iRuneA = CCGOPFn->GetGearSet(iGearSetA)->GetEquippedRune( 4 );
	RuneID iRuneB = CCGOPFn->GetGearSet(iGearSetB)->GetEquippedRune( 4 );
	Int iRes = 0;
	if ( iRuneA < iRuneB )      iRes = +1;
	else if ( iRuneA > iRuneB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall UIGearSetTableModel::_Compare_GearSetRune6( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	RuneID iRuneA = CCGOPFn->GetGearSet(iGearSetA)->GetEquippedRune( 5 );
	RuneID iRuneB = CCGOPFn->GetGearSet(iGearSetB)->GetEquippedRune( 5 );
	Int iRes = 0;
	if ( iRuneA < iRuneB )      iRes = +1;
	else if ( iRuneA > iRuneB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetTableGroupModel implementation
UIGearSetTableGroupModel::UIGearSetTableGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_GROUP)
{
	m_pGUI = NULL;
}
UIGearSetTableGroupModel::~UIGearSetTableGroupModel()
{
	// nothing to do
}

Void UIGearSetTableGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Table Options :") );
}

const WinGUILayout * UIGearSetTableGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ROOM_LEFT + 400;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ROOM_TOP;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetTableCheckAllModel implementation
UIGearSetTableCheckAllModel::UIGearSetTableCheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_CHECKALL)
{
	m_pGUI = NULL;
}
UIGearSetTableCheckAllModel::~UIGearSetTableCheckAllModel()
{
	// nothing to do
}

Void UIGearSetTableCheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Check All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetTableCheckAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIGearSetTableCheckAllModel::OnClick()
{
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();

	UInt iItemCount = pGearSetTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pGearSetTable->CheckItem( i, true );
	}

	pGearSetTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetTableUncheckAllModel implementation
UIGearSetTableUncheckAllModel::UIGearSetTableUncheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_UNCHECKALL)
{
	m_pGUI = NULL;
}
UIGearSetTableUncheckAllModel::~UIGearSetTableUncheckAllModel()
{
	// nothing to do
}

Void UIGearSetTableUncheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Uncheck All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetTableUncheckAllModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIGearSetTableUncheckAllModel::OnClick()
{
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();

	UInt iItemCount = pGearSetTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pGearSetTable->CheckItem( i, false );
	}

	pGearSetTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetTable implementation
UIGearSetTable::UIGearSetTable( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGearSetTable = NULL;

	m_pGroup = NULL;
	m_pCheckAll = NULL;
	m_pUncheckAll = NULL;
}
UIGearSetTable::~UIGearSetTable()
{
	// nothing to do
}

Void UIGearSetTable::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_GEARSET_EXPLORER );

	// Build GearSet Table UI
	m_hGearSetTableModel.Initialize( m_pGUI );
	m_pGearSetTable = WinGUIFn->CreateTable( m_pRoot, &m_hGearSetTableModel );
	m_hGearSetTableModel.CreateColumns();

	m_hGroup.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroup );

	m_hCheckAll.Initialize( m_pGUI );
	m_pCheckAll = WinGUIFn->CreateButton( m_pRoot, &m_hCheckAll );

	m_hUncheckAll.Initialize( m_pGUI );
	m_pUncheckAll = WinGUIFn->CreateButton( m_pRoot, &m_hUncheckAll );
}
Void UIGearSetTable::Cleanup()
{
	// nothing to do
}

