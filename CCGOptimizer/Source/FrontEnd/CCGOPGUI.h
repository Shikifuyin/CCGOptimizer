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

#include "HeroExplorer.h"
#include "RuneExplorer.h"
#include "GearSetExplorer.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Main Menu Tabs
enum UIMainMenuTabs {
	UI_MAINMENU_IMPORT = 0,
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
// The UIFileGroupModel class
class UIFileGroupModel : public WinGUIGroupBoxModel
{
public:
	UIFileGroupModel();
	virtual ~UIFileGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iMainMenuTab );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	UIMainMenuTabs m_iMainMenuTab;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIFileNameModel class
class UIFileNameModel : public WinGUITextEditModel
{
public:
	UIFileNameModel();
	virtual ~UIFileNameModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iMainMenuTab );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnTextChange();

private:
	CCGOPGUI * m_pGUI;
	UIMainMenuTabs m_iMainMenuTab;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIFileLoadModel class
class UIFileLoadModel : public WinGUIButtonModel
{
public:
	UIFileLoadModel();
	virtual ~UIFileLoadModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iMainMenuTab );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
	UIMainMenuTabs m_iMainMenuTab;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIFileSaveModel class
class UIFileSaveModel : public WinGUIButtonModel
{
public:
	UIFileSaveModel();
	virtual ~UIFileSaveModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UIMainMenuTabs iMainMenuTab );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
	UIMainMenuTabs m_iMainMenuTab;
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

	// Load / Save UI
	inline Void GetLoadSaveArea( WinGUIRectangle * outClientArea, UIMainMenuTabs iTabIndex ) const;

	inline WinGUITextEdit * GetLoadSaveFileName( UIMainMenuTabs iTabIndex ) const;

	inline Bool HasUnsavedChangesMark() const;
	Void SetUnsavedChangesMark();
	Void ClearUnsavedChangesMark();

	// Delegates
	inline HeroExplorer * GetHeroExplorer();
	inline RuneExplorer * GetRuneExplorer();
	inline GearSetExplorer * GetGearSetExplorer();

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

	// Load/Save UI
	struct _load_save {
		UIFileGroupModel hGroupModel;
		WinGUIGroupBox * pGroup;

		UIFileNameModel hFileNameModel;
		WinGUITextEdit * pFileName;

		UIFileLoadModel hLoadModel;
		WinGUIButton * pLoad;

		UIFileSaveModel hSaveModel;
		WinGUIButton * pSave;
	} m_arrLoadSave[UI_MAINMENU_COUNT];

	Bool m_bUnsavedChanges;

	// Delegates
	HeroExplorer m_hHeroExplorer;
	RuneExplorer m_hRuneExplorer;
	GearSetExplorer m_hGearSetExplorer;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "CCGOPGUI.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_CCGOPGUI_H

