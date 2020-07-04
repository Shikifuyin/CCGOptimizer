/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneOptions.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI : Rune Options
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
#include "RuneOptions.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// RuneOptionsGroupModel implementation
RuneOptionsGroupModel::RuneOptionsGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNEOPTIONS_GROUP)
{
	m_pGUI = NULL;
}
RuneOptionsGroupModel::~RuneOptionsGroupModel()
{
	// nothing to do
}

Void RuneOptionsGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Rune Options :") );
}

const WinGUILayout * RuneOptionsGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ROOM_LEFT;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ROOM_TOP;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneOptionsLockModel implementation
RuneOptionsLockModel::RuneOptionsLockModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNEOPTIONS_LOCK)
{
	m_pGUI = NULL;
}
RuneOptionsLockModel::~RuneOptionsLockModel()
{
	// nothing to do
}

Void RuneOptionsLockModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Lock / Unlock") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * RuneOptionsLockModel::GetLayout() const
{
	RuneOptions * pRuneOptions = m_pGUI->GetRuneExplorer()->GetRuneOptions();
	WinGUIGroupBox * pGroupBox = pRuneOptions->m_pGroup;

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

Bool RuneOptionsLockModel::OnClick()
{
	// Retrieve Rune Table
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->m_pRuneTable;

	// Find all checked elements
	Bool bChanged = false;
	UInt iItemCount = pRuneTable->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		if ( pRuneTable->IsItemChecked(i) ) {
			// Toggle Rune Lock
			RuneID iRuneID = (RuneID)(UIntPtr)( pRuneTable->GetItemData(i) );
			Rune * pRune = CCGOPFn->GetRune( iRuneID );
			if ( pRune->IsLocked() )
				pRune->Unlock();
			else
				pRune->Lock();

			// Update HeroTable
			pRuneTable->UpdateItem( i );

			bChanged = true;
		}
	}
	
	// Set Unsaved Changes Mark
	if ( bChanged )
		m_pGUI->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneOptionsDeleteModel implementation
RuneOptionsDeleteModel::RuneOptionsDeleteModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNEOPTIONS_DELETE)
{
	m_pGUI = NULL;
}
RuneOptionsDeleteModel::~RuneOptionsDeleteModel()
{
	// nothing to do
}

Void RuneOptionsDeleteModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("DELETE !") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * RuneOptionsDeleteModel::GetLayout() const
{
	RuneOptions * pRuneOptions = m_pGUI->GetRuneExplorer()->GetRuneOptions();
	WinGUIGroupBox * pGroupBox = pRuneOptions->m_pGroup;

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

Bool RuneOptionsDeleteModel::OnClick()
{
	// Confirmation Message
	WinGUIMessageBoxOptions hOptions;
	hOptions.iType = WINGUI_MESSAGEBOX_OKCANCEL;
	hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_WARNING;
	hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_CANCEL;
	hOptions.bMustAnswer = true;

	WinGUIMessageBoxResponse iResponse = WinGUIFn->SpawnMessageBox(
		TEXT("Confirmation"),
		TEXT("YOU ARE ABOUT TO DELETE ALL CHECKED RUNES !!!\nAre you sure you want to continue ?"),
		hOptions
	);

	// Abort
	if ( iResponse != WINGUI_MESSAGEBOX_RESPONSE_OK )
		return true;

	// Retrieve Rune Table
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->m_pRuneTable;

	// Delete all checked elements
	Bool bChanged = false;
	while( true ) {
		Bool bRemoved = false;

		UInt iItemCount = pRuneTable->GetItemCount();
		for( UInt i = 0; i < iItemCount; ++i ) {
			if ( pRuneTable->IsItemChecked(i) ) {
				RuneID iRuneID = (RuneID)(UIntPtr)( pRuneTable->GetItemData(i) );

				// Remove from HeroTable
				pRuneTable->RemoveItem( i );

				// Delete Hero
				CCGOPFn->DestroyRune( iRuneID );

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

	// Set Unsaved Changes Mark
	if ( bChanged )
		m_pGUI->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneOptions implementation
RuneOptions::RuneOptions( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pDelete = NULL;
}
RuneOptions::~RuneOptions()
{
	// nothing to do
}

Void RuneOptions::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_RUNE_EXPLORER );

	// Build Rune Options UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &(m_hGroupModel) );

	m_hLockModel.Initialize( m_pGUI );
	m_pLock = WinGUIFn->CreateButton( m_pRoot, &(m_hLockModel) );

	m_hDeleteModel.Initialize( m_pGUI );
	m_pDelete = WinGUIFn->CreateButton( m_pRoot, &(m_hDeleteModel) );
}
Void RuneOptions::Cleanup()
{
	// nothing to do (for now)
}


