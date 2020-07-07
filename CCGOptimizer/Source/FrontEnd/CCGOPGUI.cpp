/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/CCGOPGUI.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOP GUI
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
#include "CCGOPGUI.h"

#include "../Main.h"

/////////////////////////////////////////////////////////////////////////////////
// UIWindowModel implementation
UIWindowModel::UIWindowModel():
    WinGUIWindowModel(0)
{
    m_pGUI = NULL;
}
UIWindowModel::~UIWindowModel()
{
	// nothing to do
}

Void UIWindowModel::Initialize( CCGOPGUI * pGUI )
{
    m_pGUI = pGUI;

	m_hCreationParameters.hClientRect.iLeft = 10;
	m_hCreationParameters.hClientRect.iTop = 10;
	m_hCreationParameters.hClientRect.iWidth = CCGOP_LAYOUT_WINDOW_WIDTH;
	m_hCreationParameters.hClientRect.iHeight = CCGOP_LAYOUT_WINDOW_HEIGHT;

	StringFn->Copy( m_hCreationParameters.strClassName, TEXT("CCGOP_MainWindow") );
	StringFn->Copy( m_hCreationParameters.strTitle, TEXT("CCG Optimizer") );
	m_hCreationParameters.bHasSystemMenu = true;
	m_hCreationParameters.bHasMinimizeButton = true;
	m_hCreationParameters.bHasMaximizeButton = false;
	m_hCreationParameters.bAllowResizing = false;
	m_hCreationParameters.bClipChildren = false;
	m_hCreationParameters.bClipSibblings = false;
}

const WinGUILayout * UIWindowModel::GetLayout() const
{
	// Top-Most Windows don't use layouts
	return NULL;
}

Bool UIWindowModel::OnClose()
{
	// Check for Unsaved Changes
	if ( m_pGUI->HasUnsavedChangesMark() ) {
		WinGUIMessageBoxOptions hOptions;
		hOptions.iType = WINGUI_MESSAGEBOX_YESNO;
		hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_WARNING;
		hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_NO;
		hOptions.bMustAnswer = true;

		WinGUIMessageBoxResponse iResponse = WinGUIFn->SpawnMessageBox(
			TEXT("Warning !"),
			TEXT("You are about to leave while there are unsaved changes !\nAre you sure you want to quit ?"),
			hOptions
		);

		if ( iResponse != WINGUI_MESSAGEBOX_RESPONSE_YES )
			return true;
	}

	// Destroy App Window
	WinGUIFn->DestroyAppWindow();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UITabsModel implementation
const GChar * UITabsModel::sm_arrMenuNames[UI_MAINMENU_COUNT] = {
	TEXT("Import"),
	TEXT("Hero Explorer"),
	TEXT("Rune Explorer"),
	TEXT("GearSet Explorer"),
	TEXT("Optimizer"),
};

UITabsModel::UITabsModel():
	WinGUITabsModel(CCGOP_RESID_MAINMENU_TABS)
{
	m_pGUI = NULL;
}
UITabsModel::~UITabsModel()
{
	// nothing to do
}

Void UITabsModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	m_hCreationParameters.bSingleLine = true;
	m_hCreationParameters.bFixedWidth = true;

	m_hCreationParameters.iTabCount = UI_MAINMENU_COUNT;

	for( UInt i = 0; i < UI_MAINMENU_COUNT; ++i ) {
		StringFn->NCopy( m_hCreationParameters.arrTabs[i].strLabel, sm_arrMenuNames[i], 63 );
		m_hCreationParameters.arrTabs[i].pUserData = NULL;
	}
}

const WinGUILayout * UITabsModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = true;
	hLayout.ScalingSize.fX = 1.0f;
	hLayout.ScalingSize.fY = 1.0f;

	hLayout.UseScalingPosition = true;
	hLayout.ScalingPosition.fX = 0.0f;
	hLayout.ScalingPosition.fY = 0.0f;

	return &hLayout;
}

Bool UITabsModel::OnSelect()
{
	WinGUITabs * pController = (WinGUITabs*)m_pController;
	UInt iSelected = pController->GetSelectedTab();

	WinGUIContainer * pTabPane = m_pGUI->GetTabPane( (UIMainMenuTabs)iSelected );

	pController->SwitchSelectedTabPane( pTabPane );

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UITabPaneModel implementation
UITabPaneModel::UITabPaneModel():
	WinGUIContainerModel(CCGOP_RESID_MAINMENU_TABPANES)
{
	m_pGUI = NULL;
	m_iMainMenuTab = UI_MAINMENU_COUNT;
}
UITabPaneModel::~UITabPaneModel()
{
	// nothing to do
}

Void UITabPaneModel::Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iTabIndex )
{
	m_pGUI = pGUI;
	m_iMainMenuTab = iTabIndex;

	StringFn->Copy( m_hCreationParameters.strClassName, TEXT("CCGOP_TabPane") );
	m_hCreationParameters.bAllowResizing = false;
	m_hCreationParameters.bClipChildren = true;
	m_hCreationParameters.bClipSibblings = true;
}

const WinGUILayout * UITabPaneModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	WinGUIRectangle hRect;
	m_pGUI->GetTabs()->GetDisplayArea( &hRect );

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = hRect.iWidth;
	hLayout.FixedSize.iY = hRect.iHeight;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hRect.iLeft;
	hLayout.FixedPosition.iY = hRect.iTop;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIStatusBarModel implementation
UIStatusBarModel::UIStatusBarModel():
	WinGUIStatusBarModel(CCGOP_RESID_STATUSBAR)
{
	m_pGUI = NULL;
}
UIStatusBarModel::~UIStatusBarModel()
{
	// nothing to do
}

Void UIStatusBarModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	m_hCreationParameters.bHasSizingGrip = false;
	m_hCreationParameters.bEnableToolTips = true;
}

const WinGUILayout * UIStatusBarModel::GetLayout() const
{
	// No layout
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////
// UIFileGroupModel implementation
UIFileGroupModel::UIFileGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_LOADSAVE_GROUP)
{
	m_pGUI = NULL;
	m_iMainMenuTab = UI_MAINMENU_COUNT;
}
UIFileGroupModel::~UIFileGroupModel()
{
	// nothing to do
}

Void UIFileGroupModel::Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iMainMenuTab )
{
	m_pGUI = pGUI;
	m_iMainMenuTab = iMainMenuTab;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Load / Save :") );
}

const WinGUILayout * UIFileGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,1,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_CLIENT_WIDTH );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iY, CCGOP_LAYOUT_CLIENT_HEIGHT );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIFileNameModel implementation
UIFileNameModel::UIFileNameModel():
	WinGUITextEditModel(CCGOP_RESID_LOADSAVE_FILENAME)
{
	m_pGUI = NULL;
	m_iMainMenuTab = UI_MAINMENU_COUNT;
}
UIFileNameModel::~UIFileNameModel()
{
	// nothing to do
}

Void UIFileNameModel::Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iMainMenuTab )
{
	m_pGUI = pGUI;
	m_iMainMenuTab = iMainMenuTab;

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
	m_pGUI->GetLoadSaveArea( &hClientArea, m_iMainMenuTab );

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

Bool UIFileNameModel::OnTextChange()
{
	static Bool s_bUpdatingTabs = false;

	if ( s_bUpdatingTabs )
		return true; // Prevent infinite loop !
	s_bUpdatingTabs = true;

	// Retrieve Text
	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;
	GChar strText[256];
	pController->GetText( strText, 255 );

	// Copy accross all tabs
	for( UInt i = 0; i < UI_MAINMENU_COUNT; ++i ) {
		if ( i == m_iMainMenuTab )
			continue;

		WinGUITextEdit * pFileName = m_pGUI->GetLoadSaveFileName( (UIMainMenuTabs)i );
		pFileName->SetText( strText );
	}

	s_bUpdatingTabs = false;

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIFileLoadModel implementation
UIFileLoadModel::UIFileLoadModel():
	WinGUIButtonModel(CCGOP_RESID_LOADSAVE_LOAD)
{
	m_pGUI = NULL;
	m_iMainMenuTab = UI_MAINMENU_COUNT;
}
UIFileLoadModel::~UIFileLoadModel()
{
	// nothing to do
}

Void UIFileLoadModel::Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iMainMenuTab )
{
	m_pGUI = pGUI;
	m_iMainMenuTab = iMainMenuTab;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("LOAD") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIFileLoadModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetLoadSaveArea( &hClientArea, m_iMainMenuTab );

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
	WinGUITextEdit * pFileName = m_pGUI->GetLoadSaveFileName( m_iMainMenuTab );
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
	m_pGUI->ClearUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIFileSaveModel implementation
UIFileSaveModel::UIFileSaveModel():
	WinGUIButtonModel(CCGOP_RESID_LOADSAVE_SAVE)
{
	m_pGUI = NULL;
	m_iMainMenuTab = UI_MAINMENU_COUNT;
}
UIFileSaveModel::~UIFileSaveModel()
{
	// nothing to do
}

Void UIFileSaveModel::Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iMainMenuTab )
{
	m_pGUI = pGUI;
	m_iMainMenuTab = iMainMenuTab;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("SAVE") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIFileSaveModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetLoadSaveArea( &hClientArea, m_iMainMenuTab );

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
	WinGUITextEdit * pFileName = m_pGUI->GetLoadSaveFileName( m_iMainMenuTab );
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
	m_pGUI->ClearUnsavedChangesMark();

	// Done
	hFile.Close();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// CCGOPGUI implementation
CCGOPGUI::CCGOPGUI( CCGOPApplication * pApplication ):
	m_hHeroExplorer(this),
	m_hRuneExplorer(this),
	m_hGearSetExplorer(this)
{
	UInt i;

	m_pApplication = pApplication;

	m_pAppWindow = NULL;

	m_pTabs = NULL;
	for( i = 0; i < UI_MAINMENU_COUNT; ++i )
		m_arrTabPanes[i].pTabPane = NULL;

	m_pStatusBar = NULL;

	for( i = 0; i < UI_MAINMENU_COUNT; ++i ) {
		m_arrLoadSave[i].pGroup = NULL;
		m_arrLoadSave[i].pFileName = NULL;
		m_arrLoadSave[i].pLoad = NULL;
		m_arrLoadSave[i].pSave = NULL;
	}
	m_bUnsavedChanges = false;
}
CCGOPGUI::~CCGOPGUI()
{
	// nothing to do
}

Void CCGOPGUI::Initialize()
{
	UInt i;

	// Create App Window
	m_hAppWindowModel.Initialize( this );
	WinGUIFn->CreateAppWindow( &m_hAppWindowModel );
	m_pAppWindow = WinGUIFn->GetAppWindow();

	// Build Tabs
	m_hTabsModel.Initialize( this );
	m_pTabs = WinGUIFn->CreateTabs( m_pAppWindow, &m_hTabsModel );

	// Build Tab Panes
	for( i = 0; i < UI_MAINMENU_COUNT; ++i ) {
		m_arrTabPanes[i].hTabPaneModel.Initialize( this, (UIMainMenuTabs)i );
		m_arrTabPanes[i].pTabPane = WinGUIFn->CreateContainer( m_pAppWindow, &(m_arrTabPanes[i].hTabPaneModel) );
	}

	// Build Status Bar
	m_hStatusBarModel.Initialize( this );
	m_pStatusBar = WinGUIFn->CreateStatusBar( m_pAppWindow, &m_hStatusBarModel );
	UInt arrEdges[2] = { CCGOP_LAYOUT_WINDOW_WIDTH >> 1, INVALID_OFFSET };
	m_pStatusBar->SetMinHeight( 24 );
	m_pStatusBar->SetParts( arrEdges, 2 );
	m_pStatusBar->SetPartText( 0, TEXT("Do something interesting ..."), WINGUI_STATUSBAR_DRAW_SINKBORDER );
	m_pStatusBar->SetPartTipText( 0, TEXT("Nothing Here !") );
	m_pStatusBar->SetPartText( 1, TEXT("No Data has been Loaded Yet !"), WINGUI_STATUSBAR_DRAW_SINKBORDER );
	m_pStatusBar->SetPartTipText( 1, TEXT("Not much more Here !") );

	// Build Load/Save
	for( i = 0; i < UI_MAINMENU_COUNT; ++i ) {
		WinGUIContainer * pRoot = m_arrTabPanes[i].pTabPane;

		m_arrLoadSave[i].hGroupModel.Initialize( this, (UIMainMenuTabs)i );
		m_arrLoadSave[i].pGroup = WinGUIFn->CreateGroupBox( pRoot, &(m_arrLoadSave[i].hGroupModel) );

		m_arrLoadSave[i].hFileNameModel.Initialize( this, (UIMainMenuTabs)i );
		m_arrLoadSave[i].pFileName = WinGUIFn->CreateTextEdit( pRoot, &(m_arrLoadSave[i].hFileNameModel) );
		m_arrLoadSave[i].hFileNameModel.Update();

		m_arrLoadSave[i].hLoadModel.Initialize( this, (UIMainMenuTabs)i );
		m_arrLoadSave[i].pLoad = WinGUIFn->CreateButton( pRoot, &(m_arrLoadSave[i].hLoadModel) );

		m_arrLoadSave[i].hSaveModel.Initialize( this, (UIMainMenuTabs)i );
		m_arrLoadSave[i].pSave = WinGUIFn->CreateButton( pRoot, &(m_arrLoadSave[i].hSaveModel) );
	}

	// Build Delegates
	m_hHeroExplorer.Initialize();
	m_hRuneExplorer.Initialize();
	m_hGearSetExplorer.Initialize();

	// Initial Tab
	m_pTabs->SelectTab( UI_MAINMENU_IMPORT );
	m_pTabs->SwitchSelectedTabPane( m_arrTabPanes[UI_MAINMENU_IMPORT].pTabPane );

	// Done
	m_pAppWindow->SetVisible( true );
}
Void CCGOPGUI::Cleanup()
{
	// Cleanup Delegates
	m_hGearSetExplorer.Cleanup();
	m_hRuneExplorer.Cleanup();
	m_hHeroExplorer.Cleanup();
}

Void CCGOPGUI::SetUnsavedChangesMark()
{
	m_pStatusBar->SetPartText( 1, TEXT("Unsaved Changes are Pending !"), WINGUI_STATUSBAR_DRAW_SINKBORDER );

	m_bUnsavedChanges = true;
}
Void CCGOPGUI::ClearUnsavedChangesMark()
{
	m_pStatusBar->SetPartText( 1, TEXT("All Changes have been Saved !"), WINGUI_STATUSBAR_DRAW_SINKBORDER );

	m_bUnsavedChanges = false;
}


