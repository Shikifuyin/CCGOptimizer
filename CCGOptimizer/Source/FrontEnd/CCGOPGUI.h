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

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Main Menu Tabs
enum CCGOPMainMenuTabs {
	CCGOP_MAINMENU_IMPORT = 0,
	CCGOP_MAINMENU_HERO_EXPLORER,
	CCGOP_MAINMENU_RUNE_EXPLORER,
	CCGOP_MAINMENU_GEARSET_EXPLORER,
	CCGOP_MAINMENU_OPTIMIZER,
	CCGOP_MAINMENU_COUNT,
};

// Prototypes
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
// The CCGOPFileGroupModel class
class CCGOPFileGroupModel : public WinGUIGroupBoxModel
{
public:
	CCGOPFileGroupModel();
	virtual ~CCGOPFileGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, CCGOPMainMenuTabs iMainMenuTab );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
	CCGOPMainMenuTabs m_iMainMenuTab;
};

/////////////////////////////////////////////////////////////////////////////////
// The CCGOPFileNameModel class
class CCGOPFileNameModel : public WinGUITextEditModel
{
public:
	CCGOPFileNameModel();
	~CCGOPFileNameModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, CCGOPMainMenuTabs iMainMenuTab );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnTextChange();

private:
	CCGOPGUI * m_pGUI;
	CCGOPMainMenuTabs m_iMainMenuTab;
};

/////////////////////////////////////////////////////////////////////////////////
// The CCGOPFileLoadModel class
class CCGOPFileLoadModel : public WinGUIButtonModel
{
public:
	CCGOPFileLoadModel();
	~CCGOPFileLoadModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, CCGOPMainMenuTabs iMainMenuTab );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
	CCGOPMainMenuTabs m_iMainMenuTab;
};

/////////////////////////////////////////////////////////////////////////////////
// The CCGOPFileSaveModel class
class CCGOPFileSaveModel : public WinGUIButtonModel
{
public:
	CCGOPFileSaveModel();
	~CCGOPFileSaveModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, CCGOPMainMenuTabs iMainMenuTab );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
	CCGOPMainMenuTabs m_iMainMenuTab;
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

	// Unsaved Changes Mark
	inline Bool HasUnsavedChangesMark() const;
	Void SetUnsavedChangesMark();
	Void ClearUnsavedChangesMark();

	// Access for delegates
	inline WinGUIContainer * GetRoot( CCGOPMainMenuTabs iTabIndex ) const;

	inline HeroExplorer * GetHeroExplorer();
	inline RuneExplorer * GetRuneExplorer();

private:
	friend class CCGOPWindowModel;
	friend class CCGOPTabsModel;
	friend class CCGOPTabPaneModel;

	friend class CCGOPFileNameModel;
	friend class CCGOPFileLoadModel;
	friend class CCGOPFileSaveModel;

	// Application Instance
	CCGOPApplication * m_pApplication;

	// Main Application Window
	CCGOPWindowModel m_hAppWindowModel;
	WinGUIWindow * m_pAppWindow;

	// Main Tab Menu
	CCGOPTabsModel m_hCCGOPTabsModel;
	WinGUITabs * m_pCCGOPTabs;

	// Main Tab Panes
	CCGOPTabPaneModel m_hTabPaneModelImport;
	CCGOPTabPaneModel m_hTabPaneModelHeroExplorer;
	CCGOPTabPaneModel m_hTabPaneModelRuneExplorer;
	CCGOPTabPaneModel m_hTabPaneModelGearSetExplorer;
	CCGOPTabPaneModel m_hTabPaneModelOptimizer;
	WinGUIContainer * m_arrCCGOPTabPanes[CCGOP_MAINMENU_COUNT];

	// Status Bar
	CCGOPStatusBarModel m_hCCGOPStatusBarModel;
	WinGUIStatusBar * m_pCCGOPStatusBar;

	// Load/Save UI
	struct _tabcopy {
		CCGOPFileGroupModel m_hGroup;
		WinGUIGroupBox * m_pGroup;

		CCGOPFileNameModel m_hFileName;
		WinGUITextEdit * m_pFileName;

		CCGOPFileLoadModel m_hLoad;
		WinGUIButton * m_pLoad;

		CCGOPFileSaveModel m_hSave;
		WinGUIButton * m_pSave;
	} m_arrTabCopies[CCGOP_MAINMENU_COUNT];
	Bool m_bUnsavedChanges;

	// Main Menu Delegates
	HeroExplorer m_hHeroExplorer;
	RuneExplorer m_hRuneExplorer;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "CCGOPGUI.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_CCGOPGUI_H

