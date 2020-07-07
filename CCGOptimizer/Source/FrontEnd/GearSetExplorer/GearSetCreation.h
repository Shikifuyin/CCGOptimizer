/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetCreation.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Creation
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
#ifndef CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETCREATION_H
#define CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETCREATION_H

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
// The UIGearSetCreationGroupModel class
class UIGearSetCreationGroupModel : public WinGUIGroupBoxModel
{
public:
	UIGearSetCreationGroupModel();
	virtual ~UIGearSetCreationGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIGearSetCreationNameModel class
class UIGearSetCreationNameModel : public WinGUITextEditModel
{
public:
	UIGearSetCreationNameModel();
	virtual ~UIGearSetCreationNameModel();

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
// The UIGearSetCreationButtonModel class
class UIGearSetCreationButtonModel : public WinGUIButtonModel
{
public:
	UIGearSetCreationButtonModel();
	virtual ~UIGearSetCreationButtonModel();

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
// The UIGearSetCreation class
class UIGearSetCreation
{
public:
	UIGearSetCreation( CCGOPGUI * pGUI );
	~UIGearSetCreation();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Hero Creation
	inline Void GetCreationArea( WinGUIRectangle * outClientArea ) const;

	inline WinGUITextEdit * GetName() const;

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// GearSet Creation UI
	UIGearSetCreationGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	UIGearSetCreationNameModel m_hNameModel;
	WinGUITextEdit * m_pName;

	UIGearSetCreationButtonModel m_hButtonModel;
	WinGUIButton * m_pButton;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "GearSetCreation.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_GEARSETEXPLORER_GEARSETCREATION_H

