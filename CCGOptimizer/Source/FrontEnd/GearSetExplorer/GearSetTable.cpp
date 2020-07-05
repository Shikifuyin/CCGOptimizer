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
// GearSetTableModel implementation
GearSetTableModel::GearSetTableModel():
	WinGUITableModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE)
{
	m_pGUI = NULL;

	StringFn->Copy( m_arrColumnNames[CCGOP_GEARSETTABLE_COLUMN_NAME],   TEXT("Name") );
	StringFn->Copy( m_arrColumnNames[CCGOP_GEARSETTABLE_COLUMN_ID],     TEXT("ID") );
	StringFn->Copy( m_arrColumnNames[CCGOP_GEARSETTABLE_COLUMN_RUNE_1], TEXT("Rune 1") );
	StringFn->Copy( m_arrColumnNames[CCGOP_GEARSETTABLE_COLUMN_RUNE_2], TEXT("Rune 2") );
	StringFn->Copy( m_arrColumnNames[CCGOP_GEARSETTABLE_COLUMN_RUNE_3], TEXT("Rune 3") );
	StringFn->Copy( m_arrColumnNames[CCGOP_GEARSETTABLE_COLUMN_RUNE_4], TEXT("Rune 4") );
	StringFn->Copy( m_arrColumnNames[CCGOP_GEARSETTABLE_COLUMN_RUNE_5], TEXT("Rune 5") );
	StringFn->Copy( m_arrColumnNames[CCGOP_GEARSETTABLE_COLUMN_RUNE_6], TEXT("Rune 6") );

	UInt iNameWidth = (2 * CCGOP_LAYOUT_TABLE_WIDTH_SMALL) / CCGOP_GEARSETTABLE_COLUMN_COUNT;
	UInt iAvgWidth = (CCGOP_LAYOUT_TABLE_WIDTH_SMALL - iNameWidth) / (CCGOP_GEARSETTABLE_COLUMN_COUNT - 1);
	iNameWidth = ( CCGOP_LAYOUT_TABLE_WIDTH_SMALL - iAvgWidth * (CCGOP_GEARSETTABLE_COLUMN_COUNT - 1) );

	m_arrColumnWidths[CCGOP_GEARSETTABLE_COLUMN_NAME]   = iNameWidth;
	m_arrColumnWidths[CCGOP_GEARSETTABLE_COLUMN_ID]     = iAvgWidth;
	m_arrColumnWidths[CCGOP_GEARSETTABLE_COLUMN_RUNE_1] = iAvgWidth;
	m_arrColumnWidths[CCGOP_GEARSETTABLE_COLUMN_RUNE_2] = iAvgWidth;
	m_arrColumnWidths[CCGOP_GEARSETTABLE_COLUMN_RUNE_3] = iAvgWidth;
	m_arrColumnWidths[CCGOP_GEARSETTABLE_COLUMN_RUNE_4] = iAvgWidth;
	m_arrColumnWidths[CCGOP_GEARSETTABLE_COLUMN_RUNE_5] = iAvgWidth;
	m_arrColumnWidths[CCGOP_GEARSETTABLE_COLUMN_RUNE_6] = iAvgWidth;
}
GearSetTableModel::~GearSetTableModel()
{
	// nothing to do
}

Void GearSetTableModel::Initialize( CCGOPGUI * pGUI )
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
Void GearSetTableModel::CreateColumns()
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	// Settings
	pTable->SetBackgroundColor( 0x00d0d0d0 );
	pTable->SetTextBackgroundColor( 0x00d0d0d0 );
	pTable->ShowGridLines( true );

	pTable->ToggleAlwaysShowSelection( true );
	pTable->ToggleFullRowSelection( true );

	// Build Columns
	for( UInt i = 0; i < CCGOP_GEARSETTABLE_COLUMN_COUNT; ++i ) {
		pTable->AddColumn( i, m_arrColumnNames[i], i, i, m_arrColumnWidths[i] );
		pTable->SetColumnRowTextAlign( i, WINGUI_TABLE_TEXT_ALIGN_CENTER );
	}
}

Void GearSetTableModel::UpdateAfterGearSetCreation( GearSetID iGearSetID )
{
	WinGUITable * pTable = (WinGUITable*)m_pController;

	UInt iIndex = pTable->GetItemCount();

	pTable->AddItem( iIndex ); // Append
	pTable->SetItemData( iIndex, (Void*)iGearSetID );
}
Void GearSetTableModel::UpdateAfterDataLoad()
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

const WinGUILayout * GearSetTableModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_SPACING_BORDER;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TABLE_WIDTH_SMALL;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TABLE_HEIGHT_SMALL;

	return &hLayout;
}

Bool GearSetTableModel::OnColumnHeaderClick( UInt iIndex )
{
	static Bool arrToggles[CCGOP_GEARSETTABLE_COLUMN_COUNT] = {
		true, true, true, true, true, true, true, true
	};

	WinGUITable * pTable = (WinGUITable*)m_pController;

	switch( iIndex ) {
		case CCGOP_GEARSETTABLE_COLUMN_NAME:   pTable->SortItemsByData( _Compare_GearSetName,  arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_GEARSETTABLE_COLUMN_ID:     pTable->SortItemsByData( _Compare_GearSetID,    arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_1: pTable->SortItemsByData( _Compare_GearSetRune1, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_2: pTable->SortItemsByData( _Compare_GearSetRune2, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_3: pTable->SortItemsByData( _Compare_GearSetRune3, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_4: pTable->SortItemsByData( _Compare_GearSetRune4, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_5: pTable->SortItemsByData( _Compare_GearSetRune5, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_6: pTable->SortItemsByData( _Compare_GearSetRune6, arrToggles + iIndex ); arrToggles[iIndex] = !(arrToggles[iIndex]); break;
		default: Assert(false); break;
	}

	return true;
}

GChar * GearSetTableModel::OnRequestItemLabel( UInt iItemIndex, UInt iSubItemIndex, Void * pItemData )
{
	Assert( iItemIndex < CCGOPFn->GetGearSetCount() );
	Assert( iSubItemIndex < CCGOP_GEARSETTABLE_COLUMN_COUNT );

	WinGUITable * pTable = (WinGUITable*)m_pController;

	static GChar strBuffer[64];

	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pTable->GetItemData(iItemIndex) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	switch( iSubItemIndex ) {
		case CCGOP_GEARSETTABLE_COLUMN_NAME:
			StringFn->NCopy( strBuffer, pGearSet->GetName(), 63 );
			break;
		case CCGOP_GEARSETTABLE_COLUMN_ID:
			StringFn->FromUInt( strBuffer, pGearSet->GetID() );
			break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_1:
			StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(0) );
			break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_2:
			StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(1) );
			break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_3:
			StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(2) );
			break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_4:
			StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(3) );
			break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_5:
			StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(4) );
			break;
		case CCGOP_GEARSETTABLE_COLUMN_RUNE_6:
			StringFn->FromUInt( strBuffer, pGearSet->GetEquippedRune(5) );
			break;
		default: Assert(false); break;
	}

	return strBuffer;
}

/////////////////////////////////////////////////////////////////////////////////

Int __stdcall GearSetTableModel::_Compare_GearSetName( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	const GChar * strNameA = CCGOPFn->GetGearSet(iGearSetA)->GetName();
	const GChar * strNameB = CCGOPFn->GetGearSet(iGearSetB)->GetName();
	Int iRes = StringFn->NCmp(strNameA, strNameB, GAMEDATA_NAMES_MAX_LENGTH - 1);
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall GearSetTableModel::_Compare_GearSetID( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
	Bool bToggle = *((Bool *)pUserData);
	GearSetID iGearSetA = (GearSetID)(IntPtr)pItemDataA;
	GearSetID iGearSetB = (GearSetID)(IntPtr)pItemDataB;
	Int iRes = 0;
	if ( iGearSetA < iGearSetB )      iRes = +1;
	else if ( iGearSetA > iGearSetB ) iRes = -1;
	return ( bToggle ? iRes : -iRes );
}
Int __stdcall GearSetTableModel::_Compare_GearSetRune1( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall GearSetTableModel::_Compare_GearSetRune2( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall GearSetTableModel::_Compare_GearSetRune3( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall GearSetTableModel::_Compare_GearSetRune4( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall GearSetTableModel::_Compare_GearSetRune5( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
Int __stdcall GearSetTableModel::_Compare_GearSetRune6( Void * pItemDataA, Void * pItemDataB, Void * pUserData ) {
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
// GearSetTableGroupModel implementation
GearSetTableGroupModel::GearSetTableGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_GROUP)
{
	m_pGUI = NULL;
}
GearSetTableGroupModel::~GearSetTableGroupModel()
{
	// nothing to do
}

Void GearSetTableGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Table Options :") );
}

const WinGUILayout * GearSetTableGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(6,0,0,2) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ROOM_LEFT;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ROOM_TOP;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// GearSetTableSelectAllModel implementation
GearSetTableSelectAllModel::GearSetTableSelectAllModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_SELECTALL)
{
	m_pGUI = NULL;
}
GearSetTableSelectAllModel::~GearSetTableSelectAllModel()
{
	// nothing to do
}

Void GearSetTableSelectAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Select All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * GearSetTableSelectAllModel::GetLayout() const
{
	GearSetTable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable();
	WinGUIGroupBox * pGroupBox = pGearSetTable->m_pGroup;

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

Bool GearSetTableSelectAllModel::OnClick()
{
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->m_pGearSetTable;

	UInt iItemCount = pGearSetTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pGearSetTable->SelectItem( i, true );
	}

	pGearSetTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// GearSetTableUnselectAllModel implementation
GearSetTableUnselectAllModel::GearSetTableUnselectAllModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_UNSELECTALL)
{
	m_pGUI = NULL;
}
GearSetTableUnselectAllModel::~GearSetTableUnselectAllModel()
{
	// nothing to do
}

Void GearSetTableUnselectAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Unselect All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * GearSetTableUnselectAllModel::GetLayout() const
{
	GearSetTable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable();
	WinGUIGroupBox * pGroupBox = pGearSetTable->m_pGroup;

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

Bool GearSetTableUnselectAllModel::OnClick()
{
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->m_pGearSetTable;

	UInt iItemCount = pGearSetTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pGearSetTable->SelectItem( i, false );
	}

	pGearSetTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// GearSetTableCheckAllModel implementation
GearSetTableCheckAllModel::GearSetTableCheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_CHECKALL)
{
	m_pGUI = NULL;
}
GearSetTableCheckAllModel::~GearSetTableCheckAllModel()
{
	// nothing to do
}

Void GearSetTableCheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Check All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * GearSetTableCheckAllModel::GetLayout() const
{
	GearSetTable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable();
	WinGUIGroupBox * pGroupBox = pGearSetTable->m_pGroup;

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

Bool GearSetTableCheckAllModel::OnClick()
{
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->m_pGearSetTable;

	UInt iItemCount = pGearSetTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pGearSetTable->CheckItem( i, true );
	}

	pGearSetTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// GearSetTableUncheckAllModel implementation
GearSetTableUncheckAllModel::GearSetTableUncheckAllModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_UNCHECKALL)
{
	m_pGUI = NULL;
}
GearSetTableUncheckAllModel::~GearSetTableUncheckAllModel()
{
	// nothing to do
}

Void GearSetTableUncheckAllModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Uncheck All") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * GearSetTableUncheckAllModel::GetLayout() const
{
	GearSetTable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable();
	WinGUIGroupBox * pGroupBox = pGearSetTable->m_pGroup;

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

Bool GearSetTableUncheckAllModel::OnClick()
{
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->m_pGearSetTable;

	UInt iItemCount = pGearSetTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		pGearSetTable->CheckItem( i, false );
	}

	pGearSetTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// GearSetTableCheckSelectedModel implementation
GearSetTableCheckSelectedModel::GearSetTableCheckSelectedModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_CHECKSELECTED)
{
	m_pGUI = NULL;
}
GearSetTableCheckSelectedModel::~GearSetTableCheckSelectedModel()
{
	// nothing to do
}

Void GearSetTableCheckSelectedModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Check Selected") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * GearSetTableCheckSelectedModel::GetLayout() const
{
	GearSetTable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable();
	WinGUIGroupBox * pGroupBox = pGearSetTable->m_pGroup;

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

Bool GearSetTableCheckSelectedModel::OnClick()
{
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->m_pGearSetTable;

	UInt iItemCount = pGearSetTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		if ( pGearSetTable->IsItemSelected(i) )
			pGearSetTable->CheckItem( i, true );
	}

	pGearSetTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// GearSetTableUncheckSelectedModel implementation
GearSetTableUncheckSelectedModel::GearSetTableUncheckSelectedModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETTABLE_UNCHECKSELECTED)
{
	m_pGUI = NULL;
}
GearSetTableUncheckSelectedModel::~GearSetTableUncheckSelectedModel()
{
	// nothing to do
}

Void GearSetTableUncheckSelectedModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Uncheck Selected") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * GearSetTableUncheckSelectedModel::GetLayout() const
{
	GearSetTable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable();
	WinGUIGroupBox * pGroupBox = pGearSetTable->m_pGroup;

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

Bool GearSetTableUncheckSelectedModel::OnClick()
{
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->m_pGearSetTable;

	UInt iItemCount = pGearSetTable->GetItemCount();
	for( UInt i = 0; i < iItemCount; ++i ) {
		if ( pGearSetTable->IsItemSelected(i) )
			pGearSetTable->CheckItem( i, false );
	}

	pGearSetTable->GiveFocus();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// GearSetTable implementation
GearSetTable::GearSetTable( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGearSetTable = NULL;

	m_pGroup = NULL;
	m_pSelectAll = NULL;
	m_pUnselectAll = NULL;
	m_pCheckAll = NULL;
	m_pUncheckAll = NULL;
	m_pCheckSelected = NULL;
	m_pUncheckSelected = NULL;
}
GearSetTable::~GearSetTable()
{
	// nothing to do
}

Void GearSetTable::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_GEARSET_EXPLORER );

	// Build GearSet Table UI
	m_hGearSetTableModel.Initialize( m_pGUI );
	m_pGearSetTable = WinGUIFn->CreateTable( m_pRoot, &m_hGearSetTableModel );
	m_hGearSetTableModel.CreateColumns();

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
Void GearSetTable::Cleanup()
{
	// nothing to do
}

