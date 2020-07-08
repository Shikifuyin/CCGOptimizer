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
#include "Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroOptionsGroupModel class
class UIHeroOptionsGroupModel : public WinGUIGroupBoxModel
{
public:
	UIHeroOptionsGroupModel();
	virtual ~UIHeroOptionsGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroOptionsMaxRankModel class
class UIHeroOptionsMaxRankModel : public WinGUIButtonModel
{
public:
	UIHeroOptionsMaxRankModel();
	virtual ~UIHeroOptionsMaxRankModel();

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
// The UIHeroOptionsMaxLevelModel class
class UIHeroOptionsMaxLevelModel : public WinGUIButtonModel
{
public:
	UIHeroOptionsMaxLevelModel();
	virtual ~UIHeroOptionsMaxLevelModel();

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
// The UIHeroOptionsEvolveModel class
class UIHeroOptionsEvolveModel : public WinGUIButtonModel
{
public:
	UIHeroOptionsEvolveModel();
	virtual ~UIHeroOptionsEvolveModel();

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
// The UIHeroOptionsSanctifyChoiceModel class
class UIHeroOptionsSanctifyChoiceModel : public WinGUIComboBoxModel
{
public:
	UIHeroOptionsSanctifyChoiceModel();
	virtual ~UIHeroOptionsSanctifyChoiceModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIHeroOptionsSanctifyModel class
class UIHeroOptionsSanctifyModel : public WinGUIButtonModel
{
public:
	UIHeroOptionsSanctifyModel();
	virtual ~UIHeroOptionsSanctifyModel();

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
// The UIHeroOptionsDeleteModel class
class UIHeroOptionsDeleteModel : public WinGUIButtonModel
{
public:
	UIHeroOptionsDeleteModel();
	virtual ~UIHeroOptionsDeleteModel();

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
// The UIHeroOptions class
class UIHeroOptions
{
public:
	UIHeroOptions( CCGOPGUI * pGUI );
	~UIHeroOptions();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Hero Options
	inline Void GetOptionsArea( WinGUIRectangle * outClientArea ) const;

	inline WinGUIComboBox * GetSanctifyChoice() const;

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Hero Options UI
	UIHeroOptionsGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	UIHeroOptionsMaxRankModel m_hMaxRankModel;
	WinGUIButton * m_pMaxRank;

	UIHeroOptionsMaxLevelModel m_hMaxLevelModel;
	WinGUIButton * m_pMaxLevel;

	UIHeroOptionsEvolveModel m_hEvolveModel;
	WinGUIButton * m_pEvolve;

	UIHeroOptionsSanctifyChoiceModel m_hSanctifyChoiceModel;
	WinGUIComboBox * m_pSanctifyChoice;

	UIHeroOptionsSanctifyModel m_hSanctifyModel;
	WinGUIButton * m_pSanctify;

	UIHeroOptionsDeleteModel m_hDeleteModel;
	WinGUIButton * m_pDelete;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "HeroOptions.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_HEROEXPLORER_HEROOPTIONS_H
