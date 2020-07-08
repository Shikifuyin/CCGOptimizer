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
	if ( m_pGUI->GetImportExport()->GetLoadSave()->HasUnsavedChangesMark() ) {
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
	TEXT("Import / Export"),
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
// CCGOPGUI implementation
CCGOPGUI::CCGOPGUI( CCGOPApplication * pApplication ):
	m_hImportExport(this),
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

	// Build Delegates
	m_hImportExport.Initialize();
	m_hHeroExplorer.Initialize();
	m_hRuneExplorer.Initialize();
	m_hGearSetExplorer.Initialize();

	// Initial Tab
	m_pTabs->SelectTab( UI_MAINMENU_IMPORTEXPORT );
	m_pTabs->SwitchSelectedTabPane( m_arrTabPanes[UI_MAINMENU_IMPORTEXPORT].pTabPane );

	// Done
	m_pAppWindow->SetVisible( true );
}
Void CCGOPGUI::Cleanup()
{
	// Cleanup Delegates
	m_hGearSetExplorer.Cleanup();
	m_hRuneExplorer.Cleanup();
	m_hHeroExplorer.Cleanup();
	m_hImportExport.Cleanup();
}



