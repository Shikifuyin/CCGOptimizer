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
CCGOPWindowModel::CCGOPWindowModel( CCGOPGUI * pGUI ):
    WinGUIWindowModel(0)
{
    m_pGUI = pGUI;

    m_hCreationParameters.hClientRect.iLeft = 10;
	m_hCreationParameters.hClientRect.iTop = 10;
	m_hCreationParameters.hClientRect.iWidth = CCGOP_WINDOW_WIDTH;
	m_hCreationParameters.hClientRect.iHeight = CCGOP_WINDOW_HEIGHT;

	StringFn->Copy( m_hCreationParameters.strClassName, TEXT("CCGOP_MainWindow") );
	StringFn->Copy( m_hCreationParameters.strTitle, TEXT("CCG Optimizer") );
	m_hCreationParameters.bHasSystemMenu = true;
	m_hCreationParameters.bHasMinimizeButton = true;
	m_hCreationParameters.bHasMaximizeButton = false;
	m_hCreationParameters.bAllowResizing = false;
	m_hCreationParameters.bClipChildren = false;
	m_hCreationParameters.bClipSibblings = false;
}
CCGOPWindowModel::~CCGOPWindowModel()
{
	// nothing to do
}

const WinGUILayout * CCGOPWindowModel::GetLayout() const
{
	// Top-Most Windows don't use layouts
	return NULL;
}

Bool CCGOPWindowModel::OnClose()
{
	// Destroy App Window
	WinGUIFn->DestroyAppWindow();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// CCGOPTabsModel implementation
const GChar * CCGOPTabsModel::sm_arrMenuNames[CCGOP_MAINMENU_COUNT] = {
	TEXT("Import / Export"),
	TEXT("Hero Explorer"),
	TEXT("Rune Explorer"),
	TEXT("GearSet Explorer"),
	TEXT("Optimizer"),
};

CCGOPTabsModel::CCGOPTabsModel( CCGOPGUI * pGUI ):
	WinGUITabsModel(CCGOP_RESID_TABS_MAINMENU)
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
CCGOPTabsModel::~CCGOPTabsModel()
{
	// nothing to do
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
CCGOPTabPaneModel::CCGOPTabPaneModel( CCGOPGUI * pGUI, CCGOPMainMenuTabs iTabIndex ):
	WinGUIContainerModel(CCGOP_RESID_TABPANES_MAINMENU + iTabIndex)
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strClassName, TEXT("CCGOP_TabPane") );
	m_hCreationParameters.bAllowResizing = false;
	m_hCreationParameters.bClipChildren = true;
	m_hCreationParameters.bClipSibblings = true;
}
CCGOPTabPaneModel::~CCGOPTabPaneModel()
{
	// nothing to do
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
CCGOPStatusBarModel::CCGOPStatusBarModel( CCGOPGUI * pGUI ):
	WinGUIStatusBarModel(CCGOP_RESID_STATUSBAR)
{
	m_pGUI = pGUI;

	m_hCreationParameters.bHasSizingGrip = false;
	m_hCreationParameters.bEnableToolTips = true;
}
CCGOPStatusBarModel::~CCGOPStatusBarModel()
{
	// nothing to do
}

const WinGUILayout * CCGOPStatusBarModel::GetLayout() const
{
	// No layout
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////
// CCGOPGUI implementation
CCGOPGUI::CCGOPGUI( CCGOPApplication * pApplication ):
	m_hAppWindowModel(this),

	m_hCCGOPTabsModel(this),

	m_hTabPaneModelImportExport(this, CCGOP_MAINMENU_IMPORT_EXPORT),
	m_hTabPaneModelHeroExplorer(this, CCGOP_MAINMENU_HERO_EXPLORER),
	m_hTabPaneModelRuneExplorer(this, CCGOP_MAINMENU_RUNE_EXPLORER),
	m_hTabPaneModelGearSetExplorer(this, CCGOP_MAINMENU_GEARSET_EXPLORER),
	m_hTabPaneModelOptimizer(this, CCGOP_MAINMENU_OPTIMIZER),

	m_hCCGOPStatusBarModel(this)
{
	m_pApplication = pApplication;

	m_pAppWindow = NULL;

	m_pCCGOPTabs = NULL;
}
CCGOPGUI::~CCGOPGUI()
{
	// nothing to do
}

Void CCGOPGUI::Initialize()
{
	// Create App Window
	WinGUIFn->CreateAppWindow( &m_hAppWindowModel );
	m_pAppWindow = WinGUIFn->GetAppWindow();

	// Build GUI
	m_pCCGOPTabs = WinGUIFn->CreateTabs( m_pAppWindow, &m_hCCGOPTabsModel );

	m_arrCCGOPTabPanes[CCGOP_MAINMENU_IMPORT_EXPORT]    = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelImportExport );
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_HERO_EXPLORER]    = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelHeroExplorer );
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_RUNE_EXPLORER]    = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelRuneExplorer );
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_GEARSET_EXPLORER] = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelGearSetExplorer );
	m_arrCCGOPTabPanes[CCGOP_MAINMENU_OPTIMIZER]        = WinGUIFn->CreateContainer( m_pAppWindow, &m_hTabPaneModelOptimizer );

	m_pCCGOPStatusBar = WinGUIFn->CreateStatusBar( m_pAppWindow, &m_hCCGOPStatusBarModel );
	UInt arrEdges[2] = { 800, INVALID_OFFSET };
	m_pCCGOPStatusBar->SetMinHeight( 24 );
	m_pCCGOPStatusBar->SetParts( arrEdges, 2 );
	m_pCCGOPStatusBar->SetPartText( 0, TEXT("Do something interesting ..."), WINGUI_STATUSBAR_DRAW_SINKBORDER );
	m_pCCGOPStatusBar->SetPartTipText( 0, TEXT("Nothing Here !") );
	m_pCCGOPStatusBar->SetPartText( 1, TEXT("... with this empty bar !"), WINGUI_STATUSBAR_DRAW_SINKBORDER );
	m_pCCGOPStatusBar->SetPartTipText( 1, TEXT("Not much more Here !") );

	// Initial Tab
	m_pCCGOPTabs->SelectTab( CCGOP_MAINMENU_IMPORT_EXPORT );
	m_pCCGOPTabs->SwitchSelectedTabPane( m_arrCCGOPTabPanes[CCGOP_MAINMENU_IMPORT_EXPORT] );

	// Done
	m_pAppWindow->SetVisible( true );
}
Void CCGOPGUI::Cleanup()
{
	// nothing to do (for now)
}

/////////////////////////////////////////////////////////////////////////////////

