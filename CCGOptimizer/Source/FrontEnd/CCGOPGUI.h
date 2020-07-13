/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/CCGOPGUI.h
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
// Header prelude
#ifndef CCGOP_FRONTEND_CCGOPGUI_H
#define CCGOP_FRONTEND_CCGOPGUI_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../BackEnd/CCGOPManager.h"

#include "ResourceIDs.h"
#include "Layout.h"

#include "ImportExport.h"
#include "HeroExplorer.h"
#include "RuneExplorer.h"
#include "GearSetExplorer.h"
#include "Optimizer.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Main Menu Tabs
enum UIMainMenuTabs {
	UI_MAINMENU_IMPORTEXPORT = 0,
	UI_MAINMENU_HERO_EXPLORER,
	UI_MAINMENU_RUNE_EXPLORER,
	UI_MAINMENU_GEARSET_EXPLORER,
	UI_MAINMENU_OPTIMIZER,
	UI_MAINMENU_COUNT,
};

// Prototypes
class CCGOPGUI;

class CCGOPApplication;

/////////////////////////////////////////////////////////////////////////////////
// The UIWindowModel class
class UIWindowModel : public WinGUIWindowModel
{
public:
	UIWindowModel();
	virtual ~UIWindowModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClose();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UITabsModel class
class UITabsModel : public WinGUITabsModel
{
public:
	UITabsModel();
	virtual ~UITabsModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnSelect();

private:
	CCGOPGUI * m_pGUI;
	static const GChar * sm_arrMenuNames[UI_MAINMENU_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// The UITabPaneModel class
class UITabPaneModel : public WinGUIContainerModel
{
public:
	UITabPaneModel();
	virtual ~UITabPaneModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iTabIndex );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	UIMainMenuTabs m_iMainMenuTab;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIStatusBarModel class
class UIStatusBarModel : public WinGUIStatusBarModel
{
public:
	UIStatusBarModel();
	virtual ~UIStatusBarModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The CCGOPGUI class
class CCGOPGUI
{
public:
	CCGOPGUI( CCGOPApplication * pApplication );
	~CCGOPGUI();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Tabs / TabPanes
	inline WinGUITabs * GetTabs() const;
	inline WinGUIContainer * GetTabPane( UIMainMenuTabs iTabIndex ) const;

	// Status Bar
	inline WinGUIStatusBar * GetStatusBar() const;

	// Delegates
	inline ImportExport * GetImportExport();
	inline HeroExplorer * GetHeroExplorer();
	inline RuneExplorer * GetRuneExplorer();
	inline GearSetExplorer * GetGearSetExplorer();
	inline Optimizer * GetOptimizer();

private:
	// Application Instance
	CCGOPApplication * m_pApplication;

	// Main Application Window
	UIWindowModel m_hAppWindowModel;
	WinGUIWindow * m_pAppWindow;

	// Main Tab Menu
	UITabsModel m_hTabsModel;
	WinGUITabs * m_pTabs;

	// Main Tab Panes
	struct _tab_panes {
		UITabPaneModel hTabPaneModel;
		WinGUIContainer * pTabPane;
	} m_arrTabPanes[UI_MAINMENU_COUNT];

	// Status Bar
	UIStatusBarModel m_hStatusBarModel;
	WinGUIStatusBar * m_pStatusBar;

	// Delegates
	ImportExport m_hImportExport;
	HeroExplorer m_hHeroExplorer;
	RuneExplorer m_hRuneExplorer;
	GearSetExplorer m_hGearSetExplorer;
	Optimizer m_hOptimizer;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "CCGOPGUI.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_CCGOPGUI_H

