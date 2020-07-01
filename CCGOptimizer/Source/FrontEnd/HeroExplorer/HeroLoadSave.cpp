/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer/HeroLoadSave.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : HeroExplorer GUI : Load/Save Data
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
#include "HeroLoadSave.h"

#include "../CCGOPGUI.h"

/////////////////////////////////////////////////////////////////////////////////
// HeroLoadSaveGroupModel implementation
HeroLoadSaveGroupModel::HeroLoadSaveGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE_GROUP)
{
	m_pGUI = NULL;
}
HeroLoadSaveGroupModel::~HeroLoadSaveGroupModel()
{
	// nothing to do
}

Void HeroLoadSaveGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Load / Save :") );
}

const WinGUILayout * HeroLoadSaveGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_WINDOW_WIDTH - CCGOP_LAYOUT_SPACING_BORDER - 268;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_WINDOW_HEIGHT - CCGOP_LAYOUT_SPACING_BORDER - 120;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = 268;
	hLayout.FixedSize.iY = 80;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroLoadSaveFileNameModel implementation
HeroLoadSaveFileNameModel::HeroLoadSaveFileNameModel():
	WinGUITextEditModel(CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE_FILENAME)
{
	m_pGUI = NULL;

	StringFn->Copy( m_hCreationParameters.strInitialText, TEXT("Hmm ?!") );
	m_hCreationParameters.iAlign = WINGUI_TEXTEDIT_ALIGN_LEFT;
	m_hCreationParameters.iCase = WINGUI_TEXTEDIT_CASE_BOTH;
	m_hCreationParameters.iMode = WINGUI_TEXTEDIT_MODE_TEXT;
	m_hCreationParameters.bAllowHorizontalScroll = true;
	m_hCreationParameters.bDontHideSelection = false;
	m_hCreationParameters.bReadOnly = false;
	m_hCreationParameters.bEnableTabStop = true;
}
HeroLoadSaveFileNameModel::~HeroLoadSaveFileNameModel()
{
	// nothing to do
}

Void HeroLoadSaveFileNameModel::Initialize( CCGOPGUI * pGUI )
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
Void HeroLoadSaveFileNameModel::Update()
{
	WinGUITextEdit * pTextEdit = m_pGUI->GetHeroExplorer()->GetHeroLoadSave()->m_pFileName;

	pTextEdit->SetCueText( TEXT("Enter a File Name ..."), false );
}

const WinGUILayout * HeroLoadSaveFileNameModel::GetLayout() const
{
	HeroLoadSave * pHeroLoadSave = m_pGUI->GetHeroExplorer()->GetHeroLoadSave();
	WinGUIGroupBox * pGroupBox = pHeroLoadSave->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH * 2 + CCGOP_LAYOUT_SPACING_HORIZ;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroLoadSaveLoadModel implementation
HeroLoadSaveLoadModel::HeroLoadSaveLoadModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE_LOAD)
{
	m_pGUI = NULL;
}
HeroLoadSaveLoadModel::~HeroLoadSaveLoadModel()
{
	// nothing to do
}

Void HeroLoadSaveLoadModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("LOAD") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroLoadSaveLoadModel::GetLayout() const
{
	HeroLoadSave * pHeroLoadSave = m_pGUI->GetHeroExplorer()->GetHeroLoadSave();
	WinGUIGroupBox * pGroupBox = pHeroLoadSave->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,0,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroLoadSaveLoadModel::OnClick()
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
	
	// Retrieve Hero Table
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();

	// Retrieve FileName
	WinGUITextEdit * pTextEdit = m_pGUI->GetHeroExplorer()->GetHeroLoadSave()->m_pFileName;
	GChar strFileName[256];
	pTextEdit->GetText( strFileName, 255 );

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

	// Destroy all existing data
	pHeroTable->m_pHeroTable->RemoveAllItems();
	CCGOPFn->DestroyAllHeroes();

	// Load from XML
	CCGOPFn->ImportFromXML( strFileName );
	
	// Update Hero Table
	pHeroTable->m_hHeroTableModel.UpdateAfterDataLoad();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroLoadSaveSaveModel implementation
HeroLoadSaveSaveModel::HeroLoadSaveSaveModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE_SAVE)
{
	m_pGUI = NULL;
}
HeroLoadSaveSaveModel::~HeroLoadSaveSaveModel()
{
	// nothing to do
}

Void HeroLoadSaveSaveModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("SAVE") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroLoadSaveSaveModel::GetLayout() const
{
	HeroLoadSave * pHeroLoadSave = m_pGUI->GetHeroExplorer()->GetHeroLoadSave();
	WinGUIGroupBox * pGroupBox = pHeroLoadSave->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,0,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroLoadSaveSaveModel::OnClick()
{
	// Retrieve Hero Table
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();

	// Retrieve FileName
	WinGUITextEdit * pTextEdit = m_pGUI->GetHeroExplorer()->GetHeroLoadSave()->m_pFileName;
	GChar strFileName[256];
	pTextEdit->GetText( strFileName, 255 );

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
	
	// Done
	hFile.Close();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroLoadSave implementation
HeroLoadSave::HeroLoadSave( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pFileName = NULL;
	m_pLoad = NULL;
	m_pSave = NULL;
}
HeroLoadSave::~HeroLoadSave()
{
	// nothing to do
}

Void HeroLoadSave::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_HERO_EXPLORER );

	// Build Hero Load/Save UI
	m_hGroup.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroup );

	m_hFileName.Initialize( m_pGUI );
	m_pFileName = WinGUIFn->CreateTextEdit( m_pRoot, &m_hFileName );
	m_hFileName.Update();

	m_hLoad.Initialize( m_pGUI );
	m_pLoad = WinGUIFn->CreateButton( m_pRoot, &m_hLoad );

	m_hSave.Initialize( m_pGUI );
	m_pSave = WinGUIFn->CreateButton( m_pRoot, &m_hSave );
}
Void HeroLoadSave::Cleanup()
{
	// nothing to do (for now)
}


