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
#include "Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchGroupModel class
class UIRuneSearchGroupModel : public WinGUIGroupBoxModel
{
public:
	UIRuneSearchGroupModel();
	virtual ~UIRuneSearchGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchSlotModel class
class UIRuneSearchSlotModel : public WinGUIComboBoxModel
{
public:
	UIRuneSearchSlotModel();
	virtual ~UIRuneSearchSlotModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchSetModel class
class UIRuneSearchSetModel : public WinGUIComboBoxModel
{
public:
	UIRuneSearchSetModel();
	virtual ~UIRuneSearchSetModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchRankModel class
class UIRuneSearchRankModel : public WinGUIComboBoxModel
{
public:
	UIRuneSearchRankModel();
	virtual ~UIRuneSearchRankModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchQualityModel class
class UIRuneSearchQualityModel : public WinGUIComboBoxModel
{
public:
	UIRuneSearchQualityModel();
	virtual ~UIRuneSearchQualityModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchLevelModel class
class UIRuneSearchLevelModel : public WinGUIComboBoxModel
{
public:
	UIRuneSearchLevelModel();
	virtual ~UIRuneSearchLevelModel();

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
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchMainStatModel class
class UIRuneSearchMainStatModel : public WinGUIComboBoxModel
{
public:
	UIRuneSearchMainStatModel();
	virtual ~UIRuneSearchMainStatModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( UInt iSelectedSlot, RuneStat * arrExcludedStats, UInt iExcludedStatsCount );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	UInt m_iSelectedSlot;
	UInt m_iExcludedStatsCount;
	RuneStat m_arrExcludedStats[2+RUNE_RANDOM_STAT_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchSubStatsModeModel class
class UIRuneSearchSubStatsModeModel : public WinGUICheckBoxModel
{
public:
	UIRuneSearchSubStatsModeModel();
	virtual ~UIRuneSearchSubStatsModeModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchSubStatModel class
class UIRuneSearchSubStatModel : public WinGUIComboBoxModel
{
public:
	UIRuneSearchSubStatModel();
	virtual ~UIRuneSearchSubStatModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UInt iIndex );
	Void Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
	UInt m_iIndex;

	UInt m_iExcludedStatsCount;
	RuneStat m_arrExcludedStats[2+RUNE_RANDOM_STAT_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchSubStatValueModel class
class UIRuneSearchSubStatValueModel : public WinGUITextEditModel
{
public:
	UIRuneSearchSubStatValueModel();
	virtual ~UIRuneSearchSubStatValueModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, UInt iIndex );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

private:
	CCGOPGUI * m_pGUI;
	UInt m_iIndex;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchIndicatorModel class
class UIRuneSearchIndicatorModel : public WinGUIStaticModel
{
public:
	UIRuneSearchIndicatorModel();
	virtual ~UIRuneSearchIndicatorModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneSearchClearModel class
class UIRuneSearchClearModel : public WinGUIButtonModel
{
public:
	UIRuneSearchClearModel();
	virtual ~UIRuneSearchClearModel();

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
// The UIRuneSearchApplyModel class
class UIRuneSearchApplyModel : public WinGUIButtonModel
{
public:
	UIRuneSearchApplyModel();
	virtual ~UIRuneSearchApplyModel();

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
// The UIRuneSearch class
class UIRuneSearch
{
public:
	UIRuneSearch( CCGOPGUI * pGUI );
	~UIRuneSearch();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Rune Search
	inline Void GetSearchArea( WinGUIRectangle * outClientArea ) const;

	inline WinGUIComboBox * GetSlot() const;
	inline WinGUIComboBox * GetSet() const;
	inline WinGUIComboBox * GetRank() const;
	inline WinGUIComboBox * GetQuality() const;
	inline WinGUIComboBox * GetLevel() const;
	inline WinGUIComboBox * GetMainStat() const;
	inline WinGUICheckBox * GetSubStatsMode() const;
	inline WinGUIComboBox * GetSubStat( UInt iIndex ) const;
	inline WinGUITextEdit * GetSubStatValue( UInt iIndex ) const;
	inline WinGUIStatic * GetIndicator() const;

	// Helpers
	Void UpdateAvailableMainStats();
	Void ExcludeRuneStats( WinGUIComboBox * pJustSelected );

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Rune Search UI
	UIRuneSearchGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	UIRuneSearchSlotModel m_hSlotModel;
	WinGUIComboBox * m_pSlot;

	UIRuneSearchSetModel m_hSetModel;
	WinGUIComboBox * m_pSet;

	UIRuneSearchRankModel m_hRankModel;
	WinGUIComboBox * m_pRank;

	UIRuneSearchQualityModel m_hQualityModel;
	WinGUIComboBox * m_pQuality;

	UIRuneSearchLevelModel m_hLevelModel;
	WinGUIComboBox * m_pLevel;

	UIRuneSearchMainStatModel m_hMainStatModel;
	WinGUIComboBox * m_pMainStat;

	UIRuneSearchSubStatsModeModel m_hSubStatsModeModel;
	WinGUICheckBox * m_pSubStatsMode;

	struct _sub_stats {
		UIRuneSearchSubStatModel hStatModel;
		WinGUIComboBox * pStat;
		UIRuneSearchSubStatValueModel hValueModel;
		WinGUITextEdit * pValue;
	} m_arrSubStats[RUNE_RANDOM_STAT_COUNT];

	UIRuneSearchIndicatorModel m_hIndicatorModel;
	WinGUIStatic * m_pIndicator;

	UIRuneSearchClearModel m_hClearModel;
	WinGUIButton * m_pClear;

	UIRuneSearchApplyModel m_hApplyModel;
	WinGUIButton * m_pApply;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneSearch.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RUNEEXPLORER_RUNESEARCH_H

