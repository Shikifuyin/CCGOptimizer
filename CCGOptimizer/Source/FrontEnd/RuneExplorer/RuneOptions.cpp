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
// UIRuneOptionsGroupModel implementation
UIRuneOptionsGroupModel::UIRuneOptionsGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNEOPTIONS_GROUP)
{
	m_pGUI = NULL;
}
UIRuneOptionsGroupModel::~UIRuneOptionsGroupModel()
{
	// nothing to do
}

Void UIRuneOptionsGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Rune Options :") );
}

const WinGUILayout * UIRuneOptionsGroupModel::GetLayout() const
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
// UIRuneOptionsLockModel implementation
UIRuneOptionsLockModel::UIRuneOptionsLockModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNEOPTIONS_LOCK)
{
	m_pGUI = NULL;
}
UIRuneOptionsLockModel::~UIRuneOptionsLockModel()
{
	// nothing to do
}

Void UIRuneOptionsLockModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Lock / Unlock") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneOptionsLockModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIRuneOptionsLockModel::OnClick()
{
	// Retrieve Rune Table
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();

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
// UIRuneOptionsDeleteModel implementation
UIRuneOptionsDeleteModel::UIRuneOptionsDeleteModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNEOPTIONS_DELETE)
{
	m_pGUI = NULL;
}
UIRuneOptionsDeleteModel::~UIRuneOptionsDeleteModel()
{
	// nothing to do
}

Void UIRuneOptionsDeleteModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("DELETE !") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneOptionsDeleteModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIRuneOptionsDeleteModel::OnClick()
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
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();

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
// UIRuneOptions implementation
UIRuneOptions::UIRuneOptions( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pDelete = NULL;
}
UIRuneOptions::~UIRuneOptions()
{
	// nothing to do
}

Void UIRuneOptions::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_RUNE_EXPLORER );

	// Build Rune Options UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &(m_hGroupModel) );

	m_hLockModel.Initialize( m_pGUI );
	m_pLock = WinGUIFn->CreateButton( m_pRoot, &(m_hLockModel) );

	m_hDeleteModel.Initialize( m_pGUI );
	m_pDelete = WinGUIFn->CreateButton( m_pRoot, &(m_hDeleteModel) );
}
Void UIRuneOptions::Cleanup()
{
	// nothing to do (for now)
}


