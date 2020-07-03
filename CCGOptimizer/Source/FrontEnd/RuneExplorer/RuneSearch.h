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
// The RuneSearchSlotModel class
class RuneSearchSlotModel : public WinGUIComboBoxModel
{
public:
	RuneSearchSlotModel();
	~RuneSearchSlotModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneSearchSetModel class
class RuneSearchSetModel : public WinGUIComboBoxModel
{
public:
	RuneSearchSetModel();
	~RuneSearchSetModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneSearchRankModel class
class RuneSearchRankModel : public WinGUIComboBoxModel
{
public:
	RuneSearchRankModel();
	~RuneSearchRankModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneSearchQualityModel class
class RuneSearchQualityModel : public WinGUIComboBoxModel
{
public:
	RuneSearchQualityModel();
	~RuneSearchQualityModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneSearchLevelModel class
class RuneSearchLevelModel : public WinGUIComboBoxModel
{
public:
	RuneSearchLevelModel();
	~RuneSearchLevelModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneSearchMainStatModel class
class RuneSearchMainStatModel : public WinGUIComboBoxModel
{
public:
	RuneSearchMainStatModel();
	~RuneSearchMainStatModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( UInt iSelectedSlot, RuneStat * arrExcludedStats, UInt iExcludedStatsCount );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	UInt m_iSelectedSlot;
	UInt m_iExcludedStatsCount;
	RuneStat m_arrExcludedStats[2+RUNE_RANDOM_STAT_COUNT];
};

///////////////////////////////////////////////////////////////////////////////////
//// The RuneSearchRandomStatModel class
//class RuneSearchRandomStatModel : public WinGUIComboBoxModel
//{
//public:
//	RuneSearchRandomStatModel();
//	~RuneSearchRandomStatModel();
//
//	// Initialization / Update
//	Void Initialize( CCGOPGUI * pGUI, UInt iIndex );
//	Void Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount );
//
//	// Layout
//	virtual const WinGUILayout * GetLayout() const;
//
//	// Events
//	virtual Bool OnSelectionOK();
//
//	// Item Callback Events
//	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );
//
//private:
//	CCGOPGUI * m_pGUI;
//	UInt m_iIndex;
//
//	UInt m_iExcludedStatsCount;
//	RuneStat m_arrExcludedStats[2+RUNE_RANDOM_STAT_COUNT];
//};
//
///////////////////////////////////////////////////////////////////////////////////
//// The RuneSearchRandomStatValueModel class
//class RuneSearchRandomStatValueModel : public WinGUITextEditModel
//{
//public:
//	RuneSearchRandomStatValueModel();
//	~RuneSearchRandomStatValueModel();
//
//	// Initialization
//	Void Initialize( CCGOPGUI * pGUI, UInt iIndex );
//	Void Update();
//
//	// Layout
//	virtual const WinGUILayout * GetLayout() const;
//
//private:
//	CCGOPGUI * m_pGUI;
//	UInt m_iIndex;
//};

/////////////////////////////////////////////////////////////////////////////////
// The RuneSearchIndicatorModel class
class RuneSearchIndicatorModel : public WinGUIStaticModel
{
public:
	RuneSearchIndicatorModel();
	~RuneSearchIndicatorModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneSearchClearModel class
class RuneSearchClearModel : public WinGUIButtonModel
{
public:
	RuneSearchClearModel();
	~RuneSearchClearModel();

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
// The RuneSearchApplyModel class
class RuneSearchApplyModel : public WinGUIButtonModel
{
public:
	RuneSearchApplyModel();
	~RuneSearchApplyModel();

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
	friend class RuneSearchSlotModel;
	friend class RuneSearchSetModel;
	friend class RuneSearchRankModel;
	friend class RuneSearchQualityModel;
	friend class RuneSearchLevelModel;
	friend class RuneSearchMainStatModel;
	friend class RuneSearchInnateStatModel;
	friend class RuneSearchInnateStatValueModel;
	friend class RuneSearchRandomStatModel;
	friend class RuneSearchRandomStatValueModel;
	friend class RuneSearchIndicatorModel;
	friend class RuneSearchClearModel;
	friend class RuneSearchApplyModel;

	// Helpers
	Void _UpdateAvailableMainStats();

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
	WinGUIComboBox * m_pRank;

	RuneSearchQualityModel m_hQualityModel;
	WinGUIComboBox * m_pQuality;

	RuneSearchLevelModel m_hLevelModel;
	WinGUIComboBox * m_pLevel;

	RuneSearchMainStatModel m_hMainStatModel;
	WinGUIComboBox * m_pMainStat;

	//struct _sub_stats {
	//	RuneSearchRandomStatModel m_hRandomStatModel;
	//	WinGUIComboBox * m_pRandomStat;
	//	RuneSearchRandomStatValueModel m_hRandomStatValueModel;
	//	WinGUITextEdit * m_pRandomStatValue;
	//} m_arrSubStats[RUNE_RANDOM_STAT_COUNT];

	RuneSearchIndicatorModel m_hIndicatorModel;
	WinGUIStatic * m_pIndicator;

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

