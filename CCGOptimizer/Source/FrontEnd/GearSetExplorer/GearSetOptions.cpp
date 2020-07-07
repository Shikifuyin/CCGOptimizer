/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetOptions.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Options
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
#include "GearSetOptions.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetOptionsGroupModel implementation
UIGearSetOptionsGroupModel::UIGearSetOptionsGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETOPTIONS_GROUP)
{
	m_pGUI = NULL;
}
UIGearSetOptionsGroupModel::~UIGearSetOptionsGroupModel()
{
	// nothing to do
}

Void UIGearSetOptionsGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("GearSet Options :") );
}

const WinGUILayout * UIGearSetOptionsGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(3,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(2,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ROOM_LEFT;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ROOM_TOP;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetOptionsNameModel implementation
UIGearSetOptionsNameModel::UIGearSetOptionsNameModel():
	WinGUITextEditModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETOPTIONS_NAME)
{
	m_pGUI = NULL;
}
UIGearSetOptionsNameModel::~UIGearSetOptionsNameModel()
{
	// nothing to do
}

Void UIGearSetOptionsNameModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strInitialText, TEXT("") );
	m_hCreationParameters.iAlign = WINGUI_TEXTEDIT_ALIGN_LEFT;
	m_hCreationParameters.iCase = WINGUI_TEXTEDIT_CASE_BOTH;
	m_hCreationParameters.iMode = WINGUI_TEXTEDIT_MODE_TEXT;
	m_hCreationParameters.bAllowHorizontalScroll = true;
	m_hCreationParameters.bDontHideSelection = false;
	m_hCreationParameters.bReadOnly = false;
	m_hCreationParameters.bEnableTabStop = true;
}
Void UIGearSetOptionsNameModel::Update()
{
	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;
	pController->SetText( TEXT("") );

	pController->SetCueText( TEXT("GearSet Name ..."), false );
}

const WinGUILayout * UIGearSetOptionsNameModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Void UIGearSetOptionsNameModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUITextEdit * pController = ((WinGUITextEdit*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SetText( TEXT("") );
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetOptionsReNameModel implementation
UIGearSetOptionsReNameModel::UIGearSetOptionsReNameModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETOPTIONS_RENAME)
{
	m_pGUI = NULL;
}
UIGearSetOptionsReNameModel::~UIGearSetOptionsReNameModel()
{
	// nothing to do
}

Void UIGearSetOptionsReNameModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Rename") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetOptionsReNameModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIGearSetOptionsReNameModel::OnClick()
{
	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	if ( iSelected == INVALID_OFFSET )
		return true;

	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// Retrieve new Name
	WinGUITextEdit * pName = m_pGUI->GetGearSetExplorer()->GetGearSetOptions()->GetName();
	GChar strNameBuffer[64];
	pName->GetText( strNameBuffer, 63 );
	if ( strNameBuffer[0] == NULLBYTE )
		return true;

	// Update Name
	pGearSet->SetName( strNameBuffer );

	// Update Table
	pGearSetTable->UpdateItem( iSelected );

	// Set Unsaved Changes Mark
	m_pGUI->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetOptionsCloneModel implementation
UIGearSetOptionsCloneModel::UIGearSetOptionsCloneModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETOPTIONS_CLONE)
{
	m_pGUI = NULL;
}
UIGearSetOptionsCloneModel::~UIGearSetOptionsCloneModel()
{
	// nothing to do
}

Void UIGearSetOptionsCloneModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Clone") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetOptionsCloneModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIGearSetOptionsCloneModel::OnClick()
{
	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	if ( iSelected == INVALID_OFFSET )
		return true;

	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// Retrieve clone Name
	WinGUITextEdit * pName = m_pGUI->GetGearSetExplorer()->GetGearSetOptions()->GetName();
	GChar strNameBuffer[64];
	pName->GetText( strNameBuffer, 63 );
	if ( strNameBuffer[0] == NULLBYTE )
		return true;

	// Clone
	GearSetID iCloneID = CCGOPFn->CreateGearSet( strNameBuffer );
	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		RuneID iRuneID = pGearSet->GetEquippedRune( i );
		if ( iRuneID != INVALID_OFFSET )
			CCGOPFn->EquipRuneToGearSet( iRuneID, iCloneID );
	}
	//UInt iAttachedHeroCount = pGearSet->GetAttachedHeroCount();
	//for ( UInt i = 0; i < iAttachedHeroCount; ++i ) {
	//	HeroID iHeroID = pGearSet->GetAttachedHero( i );
	//	CCGOPFn->AttachGearSetToHero( iCloneID, iHeroID );
	//}

	// Add to Table
	UIGearSetTableModel * pModel = (UIGearSetTableModel*)( pGearSetTable->GetModel() );
	pModel->UpdateAfterGearSetCreation( iCloneID );

	// Set Unsaved Changes Mark
	m_pGUI->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetOptionsLockModel implementation
UIGearSetOptionsLockModel::UIGearSetOptionsLockModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETOPTIONS_LOCK)
{
	m_pGUI = NULL;
}
UIGearSetOptionsLockModel::~UIGearSetOptionsLockModel()
{
	// nothing to do
}

Void UIGearSetOptionsLockModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Lock / Unlock Runes") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetOptionsLockModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,0,0,0);

	return &hLayout;
}

Bool UIGearSetOptionsLockModel::OnClick()
{
	// Retrieve GearSet Table
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();

	// Find all checked elements
	Bool bChanged = false;
	UInt iItemCount = pGearSetTable->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		if ( pGearSetTable->IsItemChecked(i) ) {
			// Retrieve GearSet
			GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(i) );
			const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

			// Toggle Rune Lock
			for ( UInt j = 0; j < RUNE_SLOT_COUNT; ++j ) {
				RuneID iRuneID = pGearSet->GetEquippedRune( j );
				if ( iRuneID == INVALID_OFFSET )
					continue;
				Rune * pRune = CCGOPFn->GetRune( iRuneID );
				if ( pRune->IsLocked() )
					pRune->Unlock();
				else
					pRune->Lock();
			}

			bChanged = true;
		}
	}

	// Update Models
	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
		m_pGUI->GetGearSetExplorer()->GetGearSetSlot(i)->UpdateModels();

	// Set Unsaved Changes Mark
	if ( bChanged )
		m_pGUI->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetOptionsUnequipModel implementation
UIGearSetOptionsUnequipModel::UIGearSetOptionsUnequipModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETOPTIONS_UNEQUIP)
{
	m_pGUI = NULL;
}
UIGearSetOptionsUnequipModel::~UIGearSetOptionsUnequipModel()
{
	// nothing to do
}

Void UIGearSetOptionsUnequipModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Unequip All Runes") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetOptionsUnequipModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,0,0,0);

	return &hLayout;
}

Bool UIGearSetOptionsUnequipModel::OnClick()
{
	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	if ( iSelected == INVALID_OFFSET )
		return true;

	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );

	// Unequip All Runes
	CCGOPFn->UnequipAllRunesFromGearSet( iGearSetID );

	// Update Table
	pGearSetTable->UpdateItem( iSelected );

	// Update Models
	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
		m_pGUI->GetGearSetExplorer()->GetGearSetSlot(i)->UpdateModels();
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->UpdateModels();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetOptionsDeleteModel implementation
UIGearSetOptionsDeleteModel::UIGearSetOptionsDeleteModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETOPTIONS_DELETE)
{
	m_pGUI = NULL;
}
UIGearSetOptionsDeleteModel::~UIGearSetOptionsDeleteModel()
{
	// nothing to do
}

Void UIGearSetOptionsDeleteModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("DELETE !") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetOptionsDeleteModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,0,0,0);

	return &hLayout;
}

Bool UIGearSetOptionsDeleteModel::OnClick()
{
	// Confirmation Message
	WinGUIMessageBoxOptions hOptions;
	hOptions.iType = WINGUI_MESSAGEBOX_OKCANCEL;
	hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_WARNING;
	hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_CANCEL;
	hOptions.bMustAnswer = true;

	WinGUIMessageBoxResponse iResponse = WinGUIFn->SpawnMessageBox(
		TEXT("Confirmation"),
		TEXT("YOU ARE ABOUT TO DELETE ALL CHECKED GEARSETS !!!\nAre you sure you want to continue ?"),
		hOptions
	);

	// Abort
	if ( iResponse != WINGUI_MESSAGEBOX_RESPONSE_OK )
		return true;

	// Retrieve GearSet Table
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();

	// Delete all checked elements
	Bool bChanged = false;
	while( true ) {
		Bool bRemoved = false;

		UInt iItemCount = pGearSetTable->GetItemCount();
		for( UInt i = 0; i < iItemCount; ++i ) {
			if ( pGearSetTable->IsItemChecked(i) ) {
				GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(i) );

				// Remove from GearSetTable
				pGearSetTable->RemoveItem( i );

				// Delete GearSet
				CCGOPFn->DestroyGearSet( iGearSetID );

				bChanged = true;

				// Bail out
				bRemoved = true;
				break;
			}
		}

		// Done
		if ( !bRemoved )
			break;
	}

	// Update Models
	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
		m_pGUI->GetGearSetExplorer()->GetGearSetSlot(i)->UpdateModels();
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->UpdateModels();

	// Set Unsaved Changes Mark
	if ( bChanged )
		m_pGUI->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetOptions implementation
UIGearSetOptions::UIGearSetOptions( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pName = NULL;
	m_pReName = NULL;
	m_pClone = NULL;
	m_pLock = NULL;
	m_pUnequip = NULL;
	m_pDelete = NULL;
}
UIGearSetOptions::~UIGearSetOptions()
{
	// nothing to do
}

Void UIGearSetOptions::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_GEARSET_EXPLORER );

	// Build Rune Options UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroupModel );

	m_hNameModel.Initialize( m_pGUI );
	m_pName = WinGUIFn->CreateTextEdit( m_pRoot, &m_hNameModel );

	m_hReNameModel.Initialize( m_pGUI );
	m_pReName = WinGUIFn->CreateButton( m_pRoot, &m_hReNameModel );

	m_hCloneModel.Initialize( m_pGUI );
	m_pClone = WinGUIFn->CreateButton( m_pRoot, &m_hCloneModel );

	m_hLockModel.Initialize( m_pGUI );
	m_pLock = WinGUIFn->CreateButton( m_pRoot, &m_hLockModel );

	m_hUnequipModel.Initialize( m_pGUI );
	m_pUnequip = WinGUIFn->CreateButton( m_pRoot, &m_hUnequipModel );

	m_hDeleteModel.Initialize( m_pGUI );
	m_pDelete = WinGUIFn->CreateButton( m_pRoot, &m_hDeleteModel );
}
Void UIGearSetOptions::Cleanup()
{
	// nothing to do (for now)
}

