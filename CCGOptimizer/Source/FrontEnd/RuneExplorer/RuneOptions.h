/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneOptions.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI : Rune Options
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
#ifndef CCGOP_FRONTEND_RUNEEXPLORER_RUNEOPTIONS_H
#define CCGOP_FRONTEND_RUNEEXPLORER_RUNEOPTIONS_H

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
// The RuneOptionsGroupModel class
class RuneOptionsGroupModel : public WinGUIGroupBoxModel
{
public:
	RuneOptionsGroupModel();
	virtual ~RuneOptionsGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneOptionsLockModel class
class RuneOptionsLockModel : public WinGUIButtonModel
{
public:
	RuneOptionsLockModel();
	~RuneOptionsLockModel();

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
// The RuneOptionsDeleteModel class
class RuneOptionsDeleteModel : public WinGUIButtonModel
{
public:
	RuneOptionsDeleteModel();
	~RuneOptionsDeleteModel();

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
// The RuneOptions class
class RuneOptions
{
public:
	RuneOptions( CCGOPGUI * pGUI );
	~RuneOptions();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

private:
	friend class RuneOptionsLockModel;
	friend class RuneOptionsDeleteModel;

	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Hero Options UI
	RuneOptionsGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	RuneOptionsLockModel m_hLockModel;
	WinGUIButton * m_pLock;

	RuneOptionsDeleteModel m_hDeleteModel;
	WinGUIButton * m_pDelete;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneOptions.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RUNEEXPLORER_RUNEOPTIONS_H
