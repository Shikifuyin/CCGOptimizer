/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/ImportExport/LoadSave.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Import / Export GUI : Load & Save from/to XML
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
#include "LoadSave.h"

#include "../CCGOPGUI.h"

/////////////////////////////////////////////////////////////////////////////////
// UIFileGroupModel implementation
UIFileGroupModel::UIFileGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_IMPORTEXPORT_LOADSAVE_GROUP)
{
	m_pGUI = NULL;
}
UIFileGroupModel::~UIFileGroupModel()
{
	// nothing to do
}

Void UIFileGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Load / Save from File :") );
}

const WinGUILayout * UIFileGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,1,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iX, CCGOP_LAYOUT_CLIENT_WIDTH );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iY, CCGOP_LAYOUT_CLIENT_HEIGHT );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIFileNameModel implementation
UIFileNameModel::UIFileNameModel():
	WinGUITextEditModel(CCGOP_RESID_IMPORTEXPORT_LOADSAVE_FILENAME)
{
	m_pGUI = NULL;
}
UIFileNameModel::~UIFileNameModel()
{
	// nothing to do
}

Void UIFileNameModel::Initialize( CCGOPGUI * pGUI )
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
Void UIFileNameModel::Update()
{
	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;

	pController->SetCueText( TEXT("Enter a File Name ..."), false );
}

const WinGUILayout * UIFileNameModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetImportExport()->GetLoadSave()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH * 2 + CCGOP_LAYOUT_SPACING_HORIZ;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Void UIFileNameModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SetText( TEXT("") );
}

/////////////////////////////////////////////////////////////////////////////////
// UIFileLoadModel implementation
UIFileLoadModel::UIFileLoadModel():
	WinGUIButtonModel(CCGOP_RESID_IMPORTEXPORT_LOADSAVE_LOAD)
{
	m_pGUI = NULL;
}
UIFileLoadModel::~UIFileLoadModel()
{
	// nothing to do
}

Void UIFileLoadModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("LOAD") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIFileLoadModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetImportExport()->GetLoadSave()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,0,0);

	return &hLayout;
}

Bool UIFileLoadModel::OnClick()
{
	// Confirmation Message
	WinGUIMessageBoxOptions hOptions;
	hOptions.iType = WINGUI_MESSAGEBOX_OKCANCEL;
	hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_WARNING;
	hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_CANCEL;
	hOptions.bMustAnswer = true;

	WinGUIMessageBoxResponse iResponse = WinGUIFn->SpawnMessageBox(
		TEXT("Confirmation"),
		TEXT("You are about to load data from a file, ANY UNSAVED DATA WILL BE LOST !!!\nAre you sure you want to continue ?"),
		hOptions
	);

	// Abort
	if ( iResponse != WINGUI_MESSAGEBOX_RESPONSE_OK )
		return true;
	
	// Retrieve FileName
	WinGUITextEdit * pFileName = m_pGUI->GetImportExport()->GetLoadSave()->GetFileName();
	GChar strFileName[256];
	pFileName->GetText( strFileName, 255 );

	// Append ".xml"
	UInt iLength = StringFn->Length(strFileName);
	StringFn->NCopy( strFileName + iLength, TEXT(".xml"), 255 - iLength );

	// Try to open the file
	HFile hFile = SystemFn->OpenFile( strFileName, FILE_READ );
	if ( !(hFile.IsValid()) ) {
		hOptions.iType = WINGUI_MESSAGEBOX_OK;
		hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_ERROR;
		hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_OK;
		hOptions.bMustAnswer = true;

		WinGUIFn->SpawnMessageBox(
			TEXT("Error"),
			TEXT("Couldn't open file !"),
			hOptions
		);

		return true;
	}
	hFile.Close();

	// Retrieve All Tables
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();

	// Destroy all existing data
	pGearSetTable->RemoveAllItems();
	pRuneTable->RemoveAllItems();
	pHeroTable->RemoveAllItems();
	CCGOPFn->DestroyAllGearSets();
	CCGOPFn->DestroyAllRunes();
	CCGOPFn->DestroyAllHeroes();

	// Load from XML
	CCGOPFn->ImportFromXML( strFileName );
	
	// Update All Tables
	( (UIHeroTableModel*)(pHeroTable->GetModel()) )->UpdateAfterDataLoad();
	( (UIRuneTableModel*)(pRuneTable->GetModel()) )->UpdateAfterDataLoad();
	( (UIGearSetTableModel*)(pGearSetTable->GetModel()) )->UpdateAfterDataLoad();

	// Clear Unsaved Changes Mark
	m_pGUI->GetImportExport()->GetLoadSave()->ClearUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIFileSaveModel implementation
UIFileSaveModel::UIFileSaveModel():
	WinGUIButtonModel(CCGOP_RESID_IMPORTEXPORT_LOADSAVE_SAVE)
{
	m_pGUI = NULL;
}
UIFileSaveModel::~UIFileSaveModel()
{
	// nothing to do
}

Void UIFileSaveModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("SAVE") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIFileSaveModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetImportExport()->GetLoadSave()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,0,0);

	return &hLayout;
}

Bool UIFileSaveModel::OnClick()
{
	// Retrieve FileName
	WinGUITextEdit * pFileName = m_pGUI->GetImportExport()->GetLoadSave()->GetFileName();
	GChar strFileName[256];
	pFileName->GetText( strFileName, 255 );

	// Append ".xml"
	UInt iLength = StringFn->Length(strFileName);
	StringFn->NCopy( strFileName + iLength, TEXT(".xml"), 255 - iLength );

	// Try to open the file
	HFile hFile = SystemFn->OpenFile( strFileName, FILE_WRITE );
	if ( hFile.IsValid() ) {
		WinGUIMessageBoxOptions hOptions;
		hOptions.iType = WINGUI_MESSAGEBOX_OKCANCEL;
		hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_WARNING;
		hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_CANCEL;
		hOptions.bMustAnswer = true;

		WinGUIMessageBoxResponse iResponse = WinGUIFn->SpawnMessageBox(
			TEXT("Warning"),
			TEXT("File already exists ! Do you want to overwrite ?"),
			hOptions
		);

		// Abort
		if ( iResponse != WINGUI_MESSAGEBOX_RESPONSE_OK )
			return true;

		// Delete the file
		hFile.Close();
		SystemFn->DestroyFile( strFileName );
	}

	// Save to XML
	CCGOPFn->ExportToXML( strFileName );
	
	// Clear Unsaved Changes Mark
	m_pGUI->GetImportExport()->GetLoadSave()->ClearUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UILoadSave implementation
UILoadSave::UILoadSave( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pFileName = NULL;
	m_pLoad = NULL;
	m_pSave = NULL;

	m_bUnsavedChanges = false;
}
UILoadSave::~UILoadSave()
{
	// nothing to do
}

Void UILoadSave::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_IMPORTEXPORT );

	// Build Load / Save UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroupModel );

	m_hFileNameModel.Initialize( m_pGUI );
	m_pFileName = WinGUIFn->CreateTextEdit( m_pRoot, &m_hFileNameModel );

	m_hLoadModel.Initialize( m_pGUI );
	m_pLoad = WinGUIFn->CreateButton( m_pRoot, &m_hLoadModel );

	m_hSaveModel.Initialize( m_pGUI );
	m_pSave = WinGUIFn->CreateButton( m_pRoot, &m_hSaveModel );
}
Void UILoadSave::Cleanup()
{
	// nothing to do
}

Void UILoadSave::SetUnsavedChangesMark()
{
	WinGUIStatusBar * pStatusBar = m_pGUI->GetStatusBar();
	pStatusBar->SetPartText( 1, TEXT("Unsaved Changes are Pending !"), WINGUI_STATUSBAR_DRAW_SINKBORDER );

	m_bUnsavedChanges = true;
}
Void UILoadSave::ClearUnsavedChangesMark()
{
	WinGUIStatusBar * pStatusBar = m_pGUI->GetStatusBar();
	pStatusBar->SetPartText( 1, TEXT("All Changes have been Saved !"), WINGUI_STATUSBAR_DRAW_SINKBORDER );

	m_bUnsavedChanges = false;
}

