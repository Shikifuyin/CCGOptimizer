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
#include "../Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The HeroCreationGroupModel class
class HeroCreationGroupModel : public WinGUIGroupBoxModel
{
public:
	HeroCreationGroupModel();
	virtual ~HeroCreationGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroCreationNameModel class
class HeroCreationNameModel : public WinGUIComboBoxModel
{
public:
	HeroCreationNameModel();
	~HeroCreationNameModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	// Content Data
	Array<const GChar *> m_arrHeroNames;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroCreationRankModel class
class HeroCreationRankModel : public WinGUIComboBoxModel
{
public:
	HeroCreationRankModel();
	~HeroCreationRankModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( HeroRank iFirstAvailableRank );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	HeroRank m_iFirstAvailableRank;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroCreationLevelModel class
class HeroCreationLevelModel : public WinGUIComboBoxModel
{
public:
	HeroCreationLevelModel();
	~HeroCreationLevelModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( UInt iMinLevel, UInt iMaxLevel );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	UInt m_iMinLevel;
	UInt m_iMaxLevel;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroCreationSanctifyModel class
class HeroCreationSanctifyModel : public WinGUIComboBoxModel
{
public:
	HeroCreationSanctifyModel();
	~HeroCreationSanctifyModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( Bool bSanctifyAllowed );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	Bool m_bSanctifyAllowed;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroCreationEvolvedModel class
class HeroCreationEvolvedModel : public WinGUICheckBoxModel
{
public:
	HeroCreationEvolvedModel();
	~HeroCreationEvolvedModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroCreationButtonModel class
class HeroCreationButtonModel : public WinGUIButtonModel
{
public:
	HeroCreationButtonModel();
	~HeroCreationButtonModel();

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
// The HeroCreation class
class HeroCreation
{
public:
	HeroCreation( CCGOPGUI * pGUI );
	~HeroCreation();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

private:
	friend class HeroCreationNameModel;
	friend class HeroCreationRankModel;
	friend class HeroCreationLevelModel;
	friend class HeroCreationSanctifyModel;
	friend class HeroCreationEvolvedModel;
	friend class HeroCreationButtonModel;

	// Helpers
	Void _UpdateAvailableRanks();
	Void _UpdateAvailableLevels();
	Void _UpdateAvailableSanctify();

	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Hero Creation UI
	HeroCreationGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	HeroCreationNameModel m_hNameModel;
	WinGUIComboBox * m_pName;

	HeroCreationRankModel m_hRankModel;
	WinGUIComboBox * m_pRank;

	HeroCreationLevelModel m_hLevelModel;
	WinGUIComboBox * m_pLevel;

	HeroCreationSanctifyModel m_hSanctifyModel;
	WinGUIComboBox * m_pSanctify;

	HeroCreationEvolvedModel m_hEvolvedModel;
	WinGUICheckBox * m_pEvolved;

	HeroCreationButtonModel m_hButtonModel;
	WinGUIButton * m_pButton;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "HeroCreation.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_HEROEXPLORER_HEROCREATION_H

