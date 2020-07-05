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
// The UIRuneOptionsGroupModel class
class UIRuneOptionsGroupModel : public WinGUIGroupBoxModel
{
public:
	UIRuneOptionsGroupModel();
	virtual ~UIRuneOptionsGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneOptionsLockModel class
class UIRuneOptionsLockModel : public WinGUIButtonModel
{
public:
	UIRuneOptionsLockModel();
	virtual ~UIRuneOptionsLockModel();

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
// The UIRuneOptionsDeleteModel class
class UIRuneOptionsDeleteModel : public WinGUIButtonModel
{
public:
	UIRuneOptionsDeleteModel();
	virtual ~UIRuneOptionsDeleteModel();

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
// The UIRuneOptions class
class UIRuneOptions
{
public:
	UIRuneOptions( CCGOPGUI * pGUI );
	~UIRuneOptions();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Rune Options
	inline Void GetOptionsArea( WinGUIRectangle * outClientArea ) const;

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Hero Options UI
	UIRuneOptionsGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	UIRuneOptionsLockModel m_hLockModel;
	WinGUIButton * m_pLock;

	UIRuneOptionsDeleteModel m_hDeleteModel;
	WinGUIButton * m_pDelete;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneOptions.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RUNEEXPLORER_RUNEOPTIONS_H
