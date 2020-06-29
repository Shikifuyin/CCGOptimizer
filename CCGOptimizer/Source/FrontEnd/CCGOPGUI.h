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
#include "HeroExplorer.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Main Application Window
#define CCGOP_WINDOW_WIDTH  1600
#define CCGOP_WINDOW_HEIGHT 960

// Main Menu Tabs
enum CCGOPMainMenuTabs {
	CCGOP_MAINMENU_IMPORT_EXPORT = 0,
	CCGOP_MAINMENU_HERO_EXPLORER,
	CCGOP_MAINMENU_RUNE_EXPLORER,
	CCGOP_MAINMENU_GEARSET_EXPLORER,
	CCGOP_MAINMENU_OPTIMIZER,
	CCGOP_MAINMENU_COUNT,
};

// Prototypes
class CCGOPWindowModel;
class CCGOPTabsModel;
class CCGOPTabPaneModel;
class CCGOPGUI;

class CCGOPApplication;

/////////////////////////////////////////////////////////////////////////////////
// The CCGOPWindowModel class
class CCGOPWindowModel : public WinGUIWindowModel
{
public:
	CCGOPWindowModel();
	virtual ~CCGOPWindowModel();

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
// The CCGOPTabsModel class
class CCGOPTabsModel : public WinGUITabsModel
{
public:
	CCGOPTabsModel();
	virtual ~CCGOPTabsModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnSelect();

private:
	CCGOPGUI * m_pGUI;
	static const GChar * sm_arrMenuNames[CCGOP_MAINMENU_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// The CCGOPTabPaneModel class
class CCGOPTabPaneModel : public WinGUIContainerModel
{
public:
	CCGOPTabPaneModel( CCGOPMainMenuTabs iTabIndex );
	virtual ~CCGOPTabPaneModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The CCGOPStatusBarModel class
class CCGOPStatusBarModel : public WinGUIStatusBarModel
{
public:
	CCGOPStatusBarModel();
	virtual ~CCGOPStatusBarModel();

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

	// Access for delegates
	inline WinGUIContainer * GetRoot( CCGOPMainMenuTabs iTabIndex ) const;

	inline HeroExplorer * GetHeroExplorer();

private:
	friend class CCGOPWindowModel;
	friend class CCGOPTabsModel;
	friend class CCGOPTabPaneModel;

	// Application Instance
	CCGOPApplication * m_pApplication;

	// Main Application Window
	CCGOPWindowModel m_hAppWindowModel;
	WinGUIWindow * m_pAppWindow;

	// Main Tab Menu
	CCGOPTabsModel m_hCCGOPTabsModel;
	WinGUITabs * m_pCCGOPTabs;

	// Main Tab Panes
	CCGOPTabPaneModel m_hTabPaneModelImportExport;
	CCGOPTabPaneModel m_hTabPaneModelHeroExplorer;
	CCGOPTabPaneModel m_hTabPaneModelRuneExplorer;
	CCGOPTabPaneModel m_hTabPaneModelGearSetExplorer;
	CCGOPTabPaneModel m_hTabPaneModelOptimizer;
	WinGUIContainer * m_arrCCGOPTabPanes[CCGOP_MAINMENU_COUNT];

	// Status Bar
	CCGOPStatusBarModel m_hCCGOPStatusBarModel;
	WinGUIStatusBar * m_pCCGOPStatusBar;

	// Main Menu Delegates
	HeroExplorer m_hHeroExplorer;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "CCGOPGUI.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_CCGOPGUI_H

