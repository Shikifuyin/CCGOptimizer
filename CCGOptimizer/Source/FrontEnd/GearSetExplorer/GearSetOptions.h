/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetOptions.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Options
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
#ifndef CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETOPTIONS_H
#define CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETOPTIONS_H

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
// The UIGearSetOptionsGroupModel class
class UIGearSetOptionsGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetOptionsGroupModel();
	virtual ~UIGearSetOptionsGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetOptionsNameModel class
class UIGearSetOptionsNameModel : public WinGUITextEditModel
{
public:
	UIGearSetOptionsNameModel();
	virtual ~UIGearSetOptionsNameModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetOptionsReNameModel class
class UIGearSetOptionsReNameModel : public WinGUIButtonModel
{
public:
	UIGearSetOptionsReNameModel();
	virtual ~UIGearSetOptionsReNameModel();

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
// The UIGearSetOptionsCloneModel class
class UIGearSetOptionsCloneModel : public WinGUIButtonModel
{
public:
	UIGearSetOptionsCloneModel();
	virtual ~UIGearSetOptionsCloneModel();

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
// The UIGearSetOptionsLockModel class
class UIGearSetOptionsLockModel : public WinGUIButtonModel
{
public:
	UIGearSetOptionsLockModel();
	virtual ~UIGearSetOptionsLockModel();

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
// The UIGearSetOptionsUnequipModel class
class UIGearSetOptionsUnequipModel : public WinGUIButtonModel
{
public:
	UIGearSetOptionsUnequipModel();
	virtual ~UIGearSetOptionsUnequipModel();

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
// The UIGearSetOptionsDeleteModel class
class UIGearSetOptionsDeleteModel : public WinGUIButtonModel
{
public:
	UIGearSetOptionsDeleteModel();
	virtual ~UIGearSetOptionsDeleteModel();

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
// The UIGearSetOptions class
class UIGearSetOptions
{
public:
	UIGearSetOptions( CCGOPGUI * pGUI );
	~UIGearSetOptions();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Rune Options
	inline Void GetOptionsArea( WinGUIRectangle * outClientArea ) const;

	inline WinGUITextEdit * GetName() const;

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// GearSet Options UI
	UIGearSetOptionsGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	UIGearSetOptionsNameModel m_hNameModel;
	WinGUITextEdit * m_pName;

	UIGearSetOptionsReNameModel m_hReNameModel;
	WinGUIButton * m_pReName;

	UIGearSetOptionsCloneModel m_hCloneModel;
	WinGUIButton * m_pClone;

	UIGearSetOptionsLockModel m_hLockModel;
	WinGUIButton * m_pLock;

	UIGearSetOptionsUnequipModel m_hUnequipModel;
	WinGUIButton * m_pUnequip;

	UIGearSetOptionsDeleteModel m_hDeleteModel;
	WinGUIButton * m_pDelete;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetOptions.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETOPTIONS_H
