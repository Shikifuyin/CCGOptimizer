/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer/HeroOptions.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : HeroExplorer GUI : Hero Options
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
#ifndef CCGOP_FRONTEND_HEROEXPLORER_HEROOPTIONS_H
#define CCGOP_FRONTEND_HEROEXPLORER_HEROOPTIONS_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The HeroOptionsGroupModel class
class HeroOptionsGroupModel : public WinGUIGroupBoxModel
{
public:
	HeroOptionsGroupModel();
	virtual ~HeroOptionsGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroOptionsMaxRankModel class
class HeroOptionsMaxRankModel : public WinGUIButtonModel
{
public:
	HeroOptionsMaxRankModel();
	~HeroOptionsMaxRankModel();

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
// The HeroOptionsMaxLevelModel class
class HeroOptionsMaxLevelModel : public WinGUIButtonModel
{
public:
	HeroOptionsMaxLevelModel();
	~HeroOptionsMaxLevelModel();

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
// The HeroOptionsEvolveModel class
class HeroOptionsEvolveModel : public WinGUIButtonModel
{
public:
	HeroOptionsEvolveModel();
	~HeroOptionsEvolveModel();

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
// The HeroOptionsSanctifyChoiceModel class
class HeroOptionsSanctifyChoiceModel : public WinGUIComboBoxModel
{
public:
	HeroOptionsSanctifyChoiceModel();
	~HeroOptionsSanctifyChoiceModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The HeroOptionsSanctifyModel class
class HeroOptionsSanctifyModel : public WinGUIButtonModel
{
public:
	HeroOptionsSanctifyModel();
	~HeroOptionsSanctifyModel();

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
// The HeroOptionsDeleteModel class
class HeroOptionsDeleteModel : public WinGUIButtonModel
{
public:
	HeroOptionsDeleteModel();
	~HeroOptionsDeleteModel();

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
// The HeroOptions class
class HeroOptions
{
public:
	HeroOptions( CCGOPGUI * pGUI );
	~HeroOptions();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

private:
	friend class HeroOptionsMaxRankModel;
	friend class HeroOptionsMaxLevelModel;
	friend class HeroOptionsEvolveModel;
	friend class HeroOptionsSanctifyChoiceModel;
	friend class HeroOptionsSanctifyModel;
	friend class HeroOptionsDeleteModel;

	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Hero Options UI
	HeroOptionsGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;
	HeroOptionsMaxRankModel m_hMaxRankModel;
	WinGUIButton * m_pMaxRank;
	HeroOptionsMaxLevelModel m_hMaxLevelModel;
	WinGUIButton * m_pMaxLevel;
	HeroOptionsEvolveModel m_hEvolveModel;
	WinGUIButton * m_pEvolve;
	HeroOptionsSanctifyChoiceModel m_hSanctifyChoiceModel;
	WinGUIComboBox * m_pSanctifyChoice;
	HeroOptionsSanctifyModel m_hSanctifyModel;
	WinGUIButton * m_pSanctify;
	HeroOptionsDeleteModel m_hDeleteModel;
	WinGUIButton * m_pDelete;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "HeroOptions.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_HEROEXPLORER_HEROOPTIONS_H
