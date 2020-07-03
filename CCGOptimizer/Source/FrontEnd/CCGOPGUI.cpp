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
// CCGOPWindowModel implementation
CCGOPWindowModel::CCGOPWindowModel():
    WinGUIWindowModel(0)
{
    m_pGUI = NULL;
}
CCGOPWindowModel::~CCGOPWindowModel()
{
	// nothing to do
}

Void CCGOPWindowModel::Initialize( CCGOPGUI * pGUI )
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

const WinGUILayout * CCGOPWindowModel::GetLayout() const
{
	// Top-Most Windows don't use layouts
	return NULL;
}

Bool CCGOPWindowModel::OnClose()
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
			TEXT("You are about to leave while there are unsaved changes ! Are you sure you want to quit ?"),
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
// CCGOPTabsModel implementation
const GChar * CCGOPTabsModel::sm_arrMenuNames[CCGOP_MAINMENU_COUNT] = {
	TEXT("Import"),
	TEXT("Hero Explorer"),
	TEXT("Rune Explorer"),
	TEXT("GearSet Explorer"),
	TEXT("Optimizer"),
};

CCGOPTabsModel::CCGOPTabsModel():
	WinGUITabsModel(CCGOP_RESID_MAINMENU_TABS)
{
	m_pGUI = NULL;
}
CCGOPTabsModel::~CCGOPTabsModel()
{
	// nothing to do
}

Void CCGOPTabsModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	m_hCreationParameters.bSingleLine = true;
	m_hCreationParameters.bFixedWidth = true;

	m_hCreationParameters.iTabCount = CCGOP_MAINMENU_COUNT;

	for( UInt i = 0; i < CCGOP_MAINMENU_COUNT; ++i ) {
		StringFn->NCopy( m_hCreationParameters.arrTabs[i].strLabel, sm_arrMenuNames[i], 63 );
		m_hCreationParameters.arrTabs[i].pUserData = NULL;
	}
}

const WinGUILayout * CCGOPTabsModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = true;
	hLayout.ScalingPosition.fX = 0.0f;
	hLayout.ScalingPosition.fY = 0.0f;

	hLayout.UseScalingSize = true;
	hLayout.ScalingSize.fX = 1.0f;
	hLayout.ScalingSize.fY = 1.0f;

	return &hLayout;
}

Bool CCGOPTabsModel::OnSelect()
{
	WinGUITabs * pTabs = (WinGUITabs*)m_pController;
	UInt iSelected = pTabs->GetSelectedTab();

	WinGUIContainer * pTabPane = m_pGUI->m_arrCCGOPTabPanes[iSelected];

	pTabs->SwitchSelectedTabPane( pTabPane );

	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// CCGOPTabPaneModel implementation
CCGOPTabPaneModel::CCGOPTabPaneModel( CCGOPMainMenuTabs iTabIndex ):
	WinGUIContainerModel(CCGOP_RESID_MAINMENU_TABPANES + iTabIndex)
{
	m_pGUI = NULL;	
}
CCGOPTabPaneModel::~CCGOPTabPaneModel()
{
	// nothing to do
}

Void CCGOPTabPaneModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strClassName, TEXT("CCGOP_TabPane") );
	m_hCreationParameters.bAllowResizing = false;
	m_hCreationParameters.bClipChildren = true;
	m_hCreationParameters.bClipSibblings = true;
}

const WinGUILayout * CCGOPTabPaneModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	WinGUIRectangle hRect;
	m_pGUI->m_pCCGOPTabs->GetDisplayArea( &hRect );

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hRect.iLeft;
	hLayout.FixedPosition.iY = hRect.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = hRect.iWidth;
	hLayout.FixedSize.iY = hRect.iHeight;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// CCGOPStatusBarModel implementation
CCGOPStatusBarModel::CCGOPStatusBarModel():
	WinGUIStatusBarModel(CCGOP_RESID_STATUSBAR)
{
	m_pGUI = NULL;
}
CCGOPStatusBarModel::~CCGOPStatusBarModel()
{
	// nothing to do
}

Void CCGOPStatusBarModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	m_hCreationParameters.bHasSizingGrip = false;
	m_hCreationParameters.bEnableToolTips = true;
}

const WinGUILayout * CCGOPStatusBarModel::GetLayout() const
{
	// No layout
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////
// CCGOPFileGroupModel implementation
CCGOPFileGroupModel::CCGOPFileGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_LOADSAVE_GROUP)
{
	m_pGUI = NULL;
	m_iMainMenuTab = CCGOP_MAINMENU_COUNT;
}
CCGOPFileGroupModel::~CCGOPFileGroupModel()
{
	// nothing to do
}

Void CCGOPFileGroupModel::Initialize( CCGOPGUI * pGUI, CCGOPMainMenuTabs iMainMenuTab )
{
	m_pGUI = pGUI;
	m_iMainMenuTab = iMainMenuTab;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Load / Save :") );
}

const WinGUILayout * CCGOPFileGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,1,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ROOM_LEFT + CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_ROOM_WIDTH );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ROOM_TOP + CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iY, CCGOP_LAYOUT_ROOM_HEIGHT );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// CCGOPFileNameModel implementation
CCGOPFileNameModel::CCGOPFileNameModel():
	WinGUITextEditModel(CCGOP_RESID_LOADSAVE_FILENAME)
{
	m_pGUI = NULL;
	m_iMainMenuTab = CCGOP_MAINMENU_COUNT;
}
CCGOPFileNameModel::~CCGOPFileNameModel()
{
	// nothing to do
}

Void CCGOPFileNameModel::Initialize( CCGOPGUI * pGUI, CCGOPMainMenuTabs iMainMenuTab )
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
Void CCGOPFileNameModel::Update()
{
	WinGUITextEdit * pTextEdit = m_pGUI->m_arrTabCopies[m_iMainMenuTab].m_pFileName;

	pTextEdit->SetCueText( TEXT("Enter a File Name ..."), false );
}

const WinGUILayout * CCGOPFileNameModel::GetLayout() const
{
	WinGUIGroupBox * pGroupBox = m_pGUI->m_arrTabCopies[m_iMainMenuTab].m_pGroup;

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

Bool CCGOPFileNameModel::OnTextChange()
{
	static Bool s_bUpdatingTabs = false;

	if ( s_bUpdatingTabs )
		return true; // Prevent infinite loop !
	s_bUpdatingTabs = true;

	// Retrieve Text
	WinGUITextEdit * pTextEdit = m_pGUI->m_arrTabCopies[m_iMainMenuTab].m_pFileName;
	GChar strText[256];
	pTextEdit->GetText( strText, 255 );

	// Copy accross all tabs
	for ( UInt i = 0; i < CCGOP_MAINMENU_COUNT; ++i ) {
		if ( i == m_iMainMenuTab )
			continue;
		pTextEdit = m_pGUI->m_arrTabCopies[i].m_pFileName;
		pTextEdit->SetText( strText );
	}

	s_bUpdatingTabs = false;

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// CCGOPFileLoadModel implementation
CCGOPFileLoadModel::CCGOPFileLoadModel():
	WinGUIButtonModel(CCGOP_RESID_LOADSAVE_LOAD)
{
	m_pGUI = NULL;
	m_iMainMenuTab = CCGOP_MAINMENU_COUNT;
}
CCGOPFileLoadModel::~CCGOPFileLoadModel()
{
	// nothing to do
}

Void CCGOPFileLoadModel::Initialize( CCGOPGUI * pGUI, CCGOPMainMenuTabs iMainMenuTab )
{
	m_pGUI = pGUI;
	m_iMainMenuTab = iMainMenuTab;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("LOAD") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * CCGOPFileLoadModel::GetLayout() const
{
	WinGUIGroupBox * pGroupBox = m_pGUI->m_arrTabCopies[m_iMainMenuTab].m_pGroup;

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

Bool CCGOPFileLoadModel::OnClick()
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
	WinGUITextEdit * pTextEdit = m_pGUI->m_arrTabCopies[m_iMainMenuTab].m_pFileName;
	GChar strFileName[256];
	pTextEdit->GetText( strFileName, 255 );

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
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();
	RuneTable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable();

	// Destroy all existing data
	pHeroTable->m_pHeroTable->RemoveAllItems();
	pRuneTable->m_pRuneTable->RemoveAllItems();
	CCGOPFn->DestroyAllHeroes();
	CCGOPFn->DestroyAllRunes();

	// Load from XML
	CCGOPFn->ImportFromXML( strFileName );
	
	// Update All Tables
	pHeroTable->m_hHeroTableModel.UpdateAfterDataLoad();
	pRuneTable->m_hRuneTableModel.UpdateAfterDataLoad();

	// Clear Unsaved Changes Mark
	m_pGUI->ClearUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// CCGOPFileSaveModel implementation
CCGOPFileSaveModel::CCGOPFileSaveModel():
	WinGUIButtonModel(CCGOP_RESID_LOADSAVE_SAVE)
{
	m_pGUI = NULL;
	m_iMainMenuTab = CCGOP_MAINMENU_COUNT;
}
CCGOPFileSaveModel::~CCGOPFileSaveModel()
{
	// nothing to do
}

Void CCGOPFileSaveModel::Initialize( CCGOPGUI * pGUI, CCGOPMainMenuTabs iMainMenuTab )
{
	m_pGUI = pGUI;
	m_iMainMenuTab = iMainMenuTab;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("SAVE") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * CCGOPFileSaveModel::GetLayout() const
{
	WinGUIGroupBox * pGroupBox = m_pGUI->m_arrTabCopies[m_iMainMenuTab].m_pGroup;

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

Bool CCGOPFileSaveModel::OnClick()
{
	// Retrieve FileName
	WinGUITextEdit * pTextEdit = m_pGUI->m_arrTabCopies[m_iMainMenuTab].m_pFileName;
	GChar strFileName[256];
	pTextEdit->GetText( strFileName, 255 );

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
	m_hTabPaneModelImport(CCGOP_MAINMENU_IMPORT),
	m_hTabPaneModelHeroExplorer(CCGOP_MAINMENU_HERO_EXPLORER),
	m_hTabPaneModelRuneExplorer(CCGOP_MAINMENU_RUNE_EXPLORER),
	m_hTabPaneModelGearSetExplorer(CCGOP_MAINMENU_GEARSET_EXPLORER),
	m_hTabPaneModelOptimizer(CCGOP_MAINMENU_OPTIMIZER),

	m_hHeroExplorer(this),
	m_hRuneExplorer(this)
{
	m_pApplication = pApplication;

	m_pAppWindow = NULL;

	m_pCCGOPTabs = NULL;

	m_arrCCGOPTabPanes[CCGOP_MAINMENU_IMPORT] = NULL;
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_HERO_EXPLORER] = NULL;
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_RUNE_EXPLORER] = NULL;
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_GEARSET_EXPLORER] = NULL;
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_OPTIMIZER] = NULL;

	m_pCCGOPStatusBar = NULL;

	for( UInt i = 0; i < CCGOP_MAINMENU_COUNT; ++i ) {
		m_arrTabCopies[i].m_pGroup = NULL;
		m_arrTabCopies[i].m_pFileName = NULL;
		m_arrTabCopies[i].m_pLoad = NULL;
		m_arrTabCopies[i].m_pSave = NULL;
	}
	m_bUnsavedChanges = false;
}
CCGOPGUI::~CCGOPGUI()
{
	// nothing to do
}

Void CCGOPGUI::Initialize()
{
	// Create App Window
	m_hAppWindowModel.Initialize( this );
	WinGUIFn->CreateAppWindow( &m_hAppWindowModel );
	m_pAppWindow = WinGUIFn->GetAppWindow();

	// Build GUI
	m_hCCGOPTabsModel.Initialize( this );
	m_pCCGOPTabs = WinGUIFn->CreateTabs( m_pAppWindow, &m_hCCGOPTabsModel );

	m_hTabPaneModelImport.Initialize( this );
	m_hTabPaneModelHeroExplorer.Initialize( this );
	m_hTabPaneModelRuneExplorer.Initialize( this );
	m_hTabPaneModelGearSetExplorer.Initialize( this );
	m_hTabPaneModelOptimizer.Initialize( this );
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_IMPORT]           = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelImport );
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_HERO_EXPLORER]    = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelHeroExplorer );
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_RUNE_EXPLORER]    = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelRuneExplorer );
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_GEARSET_EXPLORER] = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelGearSetExplorer );
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_OPTIMIZER]        = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelOptimizer );

	m_hCCGOPStatusBarModel.Initialize( this );
	m_pCCGOPStatusBar = WinGUIFn->CreateStatusBar( m_pAppWindow, &m_hCCGOPStatusBarModel );
	UInt arrEdges[2] = { 800, INVALID_OFFSET };
	m_pCCGOPStatusBar->SetMinHeight( 24 );
	m_pCCGOPStatusBar->SetParts( arrEdges, 2 );
	m_pCCGOPStatusBar->SetPartText( 0, TEXT("Do something interesting ..."), WINGUI_STATUSBAR_DRAW_SINKBORDER );
	m_pCCGOPStatusBar->SetPartTipText( 0, TEXT("Nothing Here !") );
	m_pCCGOPStatusBar->SetPartText( 1, TEXT("No Data has been Loaded Yet !"), WINGUI_STATUSBAR_DRAW_SINKBORDER );
	m_pCCGOPStatusBar->SetPartTipText( 1, TEXT("Not much more Here !") );

	// Build Load/Save
	for( UInt i = 0; i < CCGOP_MAINMENU_COUNT; ++i ) {
		WinGUIContainer * pRoot = m_arrCCGOPTabPanes[i];

		m_arrTabCopies[i].m_hGroup.Initialize( this, (CCGOPMainMenuTabs)i );
		m_arrTabCopies[i].m_pGroup = WinGUIFn->CreateGroupBox( pRoot, &(m_arrTabCopies[i].m_hGroup) );

		m_arrTabCopies[i].m_hFileName.Initialize( this, (CCGOPMainMenuTabs)i );
		m_arrTabCopies[i].m_pFileName = WinGUIFn->CreateTextEdit( pRoot, &(m_arrTabCopies[i].m_hFileName) );
		m_arrTabCopies[i].m_hFileName.Update();

		m_arrTabCopies[i].m_hLoad.Initialize( this, (CCGOPMainMenuTabs)i );
		m_arrTabCopies[i].m_pLoad = WinGUIFn->CreateButton( pRoot, &(m_arrTabCopies[i].m_hLoad) );

		m_arrTabCopies[i].m_hSave.Initialize( this, (CCGOPMainMenuTabs)i );
		m_arrTabCopies[i].m_pSave = WinGUIFn->CreateButton( pRoot, &(m_arrTabCopies[i].m_hSave) );
	}

	// Build Delegates
	m_hHeroExplorer.Initialize();
	m_hRuneExplorer.Initialize();

	// Initial Tab
	m_pCCGOPTabs->SelectTab( CCGOP_MAINMENU_IMPORT );
	m_pCCGOPTabs->SwitchSelectedTabPane( m_arrCCGOPTabPanes[CCGOP_MAINMENU_IMPORT] );

	// Done
	m_pAppWindow->SetVisible( true );
}
Void CCGOPGUI::Cleanup()
{
	// Cleanup Delegates
	m_hRuneExplorer.Cleanup();
	m_hHeroExplorer.Cleanup();
}

Void CCGOPGUI::SetUnsavedChangesMark()
{
	m_pCCGOPStatusBar->SetPartText( 1, TEXT("Unsaved Changes are Pending !"), WINGUI_STATUSBAR_DRAW_SINKBORDER );

	m_bUnsavedChanges = true;
}
Void CCGOPGUI::ClearUnsavedChangesMark()
{
	m_pCCGOPStatusBar->SetPartText( 1, TEXT("All Changes have been Saved !"), WINGUI_STATUSBAR_DRAW_SINKBORDER );

	m_bUnsavedChanges = false;
}

/////////////////////////////////////////////////////////////////////////////////

