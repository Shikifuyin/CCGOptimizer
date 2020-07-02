/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneSearch.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI : Rune Search
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
#ifndef CCGOP_FRONTEND_RUNEEXPLORER_RUNESEARCH_H
#define CCGOP_FRONTEND_RUNEEXPLORER_RUNESEARCH_H

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
// The RuneSearchGroupModel class
class RuneSearchGroupModel : public WinGUIGroupBoxModel
{
public:
	RuneSearchGroupModel();
	virtual ~RuneSearchGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneSearch class
class RuneSearch
{
public:
	RuneSearch( CCGOPGUI * pGUI );
	~RuneSearch();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

private:
	// Helpers

	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Rune Search UI
	RuneSearchGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	RuneSearchSlotModel m_hSlotModel;
	WinGUIComboBox * m_pSlot;

	RuneSearchSetModel m_hSetModel;
	WinGUIComboBox * m_pSet;

	RuneSearchRankModel m_hRankModel;
	WinGUISliderBar * m_pRank;

	RuneSearchQualityModel m_hQualityModel;
	WinGUISliderBar * m_pQuality;

	RuneSearchLevelModel m_hLevelModel;
	WinGUISliderBar * m_pLevel;

	RuneSearchMainStatModel m_hMainStatModel;
	WinGUIComboBox * m_pMainStat;

	RuneSearchInnateStatModel m_hInnateStatModel;
	WinGUIComboBox * m_pInnateStat;

	struct _random_stats {
		RuneSearchRandomStatModel m_hRandomStatModel;
		WinGUIComboBox * m_pRandomStat;
	} m_arrRandomStats[RUNE_RANDOM_STAT_COUNT];

	RuneSearchClearModel m_hClearModel;
	WinGUIButton * m_pClear;

	RuneSearchApplyModel m_hApplyModel;
	WinGUIButton * m_pApply;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneSearch.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RUNEEXPLORER_RUNESEARCH_H

