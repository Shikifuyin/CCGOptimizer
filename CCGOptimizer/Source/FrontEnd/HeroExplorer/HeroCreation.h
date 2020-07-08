/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer/HeroCreation.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : HeroExplorer GUI : Hero Creation
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
#ifndef CCGOP_FRONTEND_HEROEXPLORER_HEROCREATION_H
#define CCGOP_FRONTEND_HEROEXPLORER_HEROCREATION_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"
#include "Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroCreationGroupModel class
class UIHeroCreationGroupModel : public WinGUIGroupBoxModel
{
public:
	UIHeroCreationGroupModel();
	virtual ~UIHeroCreationGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroCreationNameModel class
class UIHeroCreationNameModel : public WinGUIComboBoxModel
{
public:
	UIHeroCreationNameModel();
	virtual ~UIHeroCreationNameModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	// Content Data
	Array<const GChar *> m_arrHeroNames;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroCreationRankModel class
class UIHeroCreationRankModel : public WinGUIComboBoxModel
{
public:
	UIHeroCreationRankModel();
	virtual ~UIHeroCreationRankModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( HeroRank iFirstAvailableRank );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	HeroRank m_iFirstAvailableRank;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroCreationLevelModel class
class UIHeroCreationLevelModel : public WinGUIComboBoxModel
{
public:
	UIHeroCreationLevelModel();
	virtual ~UIHeroCreationLevelModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( UInt iMinLevel, UInt iMaxLevel );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	UInt m_iMinLevel;
	UInt m_iMaxLevel;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroCreationSanctifyModel class
class UIHeroCreationSanctifyModel : public WinGUIComboBoxModel
{
public:
	UIHeroCreationSanctifyModel();
	virtual ~UIHeroCreationSanctifyModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( Bool bSanctifyAllowed );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	Bool m_bSanctifyAllowed;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroCreationEvolvedModel class
class UIHeroCreationEvolvedModel : public WinGUICheckBoxModel
{
public:
	UIHeroCreationEvolvedModel();
	virtual ~UIHeroCreationEvolvedModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroCreationButtonModel class
class UIHeroCreationButtonModel : public WinGUIButtonModel
{
public:
	UIHeroCreationButtonModel();
	virtual ~UIHeroCreationButtonModel();

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
// The UIHeroCreation class
class UIHeroCreation
{
public:
	UIHeroCreation( CCGOPGUI * pGUI );
	~UIHeroCreation();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Hero Creation
	inline Void GetArea( WinGUIRectangle * outClientArea ) const;

	inline WinGUIComboBox * GetName() const;
	inline WinGUIComboBox * GetRank() const;
	inline WinGUIComboBox * GetLevel() const;
	inline WinGUIComboBox * GetSanctify() const;
	inline WinGUICheckBox * GetEvolved() const;

	// Helpers
	Void UpdateAvailableRanks();
	Void UpdateAvailableLevels();
	Void UpdateAvailableSanctify();

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Hero Creation UI
	UIHeroCreationGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	UIHeroCreationNameModel m_hNameModel;
	WinGUIComboBox * m_pName;

	UIHeroCreationRankModel m_hRankModel;
	WinGUIComboBox * m_pRank;

	UIHeroCreationLevelModel m_hLevelModel;
	WinGUIComboBox * m_pLevel;

	UIHeroCreationSanctifyModel m_hSanctifyModel;
	WinGUIComboBox * m_pSanctify;

	UIHeroCreationEvolvedModel m_hEvolvedModel;
	WinGUICheckBox * m_pEvolved;

	UIHeroCreationButtonModel m_hButtonModel;
	WinGUIButton * m_pButton;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "HeroCreation.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_HEROEXPLORER_HEROCREATION_H

