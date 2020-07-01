/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer/HeroLoadSave.h
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
// Header prelude
#ifndef CCGOP_FRONTEND_HEROEXPLORER_HEROLOADSAVE_H
#define CCGOP_FRONTEND_HEROEXPLORER_HEROLOADSAVE_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"
#include "../Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The HeroLoadSaveGroupModel class
class HeroLoadSaveGroupModel : public WinGUIGroupBoxModel
{
public:
	HeroLoadSaveGroupModel();
	virtual ~HeroLoadSaveGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroLoadSaveFileNameModel class
class HeroLoadSaveFileNameModel : public WinGUITextEditModel
{
public:
	HeroLoadSaveFileNameModel();
	~HeroLoadSaveFileNameModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroLoadSaveLoadModel class
class HeroLoadSaveLoadModel : public WinGUIButtonModel
{
public:
	HeroLoadSaveLoadModel();
	~HeroLoadSaveLoadModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroLoadSaveSaveModel class
class HeroLoadSaveSaveModel : public WinGUIButtonModel
{
public:
	HeroLoadSaveSaveModel();
	~HeroLoadSaveSaveModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroLoadSave class
class HeroLoadSave
{
public:
	HeroLoadSave( CCGOPGUI * pGUI );
	~HeroLoadSave();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

private:
	friend class HeroLoadSaveFileNameModel;
	friend class HeroLoadSaveLoadModel;
	friend class HeroLoadSaveSaveModel;

	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Hero Load/Save UI
	HeroLoadSaveGroupModel m_hGroup;
	WinGUIGroupBox * m_pGroup;
	HeroLoadSaveFileNameModel m_hFileName;
	WinGUITextEdit * m_pFileName;
	HeroLoadSaveLoadModel m_hLoad;
	WinGUIButton * m_pLoad;
	HeroLoadSaveSaveModel m_hSave;
	WinGUIButton * m_pSave;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "HeroLoadSave.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_HEROEXPLORER_HEROLOADSAVE_H

