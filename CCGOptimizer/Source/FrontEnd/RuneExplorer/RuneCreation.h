/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneCreation.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI : Rune Creation
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
#ifndef CCGOP_FRONTEND_RUNEEXPLORER_RUNECREATION_H
#define CCGOP_FRONTEND_RUNEEXPLORER_RUNECREATION_H

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
// The UIRuneCreationGroupModel class
class UIRuneCreationGroupModel : public WinGUIGroupBoxModel
{
public:
	UIRuneCreationGroupModel();
	virtual ~UIRuneCreationGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneCreationSlotModel class
class UIRuneCreationSlotModel : public WinGUIComboBoxModel
{
public:
	UIRuneCreationSlotModel();
	virtual ~UIRuneCreationSlotModel();

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
// The UIRuneCreationSetModel class
class UIRuneCreationSetModel : public WinGUIComboBoxModel
{
public:
	UIRuneCreationSetModel();
	virtual ~UIRuneCreationSetModel();

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
// The UIRuneCreationRankModel class
class UIRuneCreationRankModel : public WinGUIComboBoxModel
{
public:
	UIRuneCreationRankModel();
	virtual ~UIRuneCreationRankModel();

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
// The UIRuneCreationQualityModel class
class UIRuneCreationQualityModel : public WinGUIComboBoxModel
{
public:
	UIRuneCreationQualityModel();
	virtual ~UIRuneCreationQualityModel();

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
// The UIRuneCreationLevelModel class
class UIRuneCreationLevelModel : public WinGUIComboBoxModel
{
public:
	UIRuneCreationLevelModel();
	virtual ~UIRuneCreationLevelModel();

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
// The UIRuneCreationMainStatModel class
class UIRuneCreationMainStatModel : public WinGUIComboBoxModel
{
public:
	UIRuneCreationMainStatModel();
	virtual ~UIRuneCreationMainStatModel();

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
// The UIRuneCreationInnateStatModel class
class UIRuneCreationInnateStatModel : public WinGUIComboBoxModel
{
public:
	UIRuneCreationInnateStatModel();
	virtual ~UIRuneCreationInnateStatModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
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

	UInt m_iExcludedStatsCount;
	RuneStat m_arrExcludedStats[2+RUNE_RANDOM_STAT_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// The UIRuneCreationInnateStatValueModel class
class UIRuneCreationInnateStatValueModel : public WinGUITextEditModel
{
public:
	UIRuneCreationInnateStatValueModel();
	virtual ~UIRuneCreationInnateStatValueModel();

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
// The UIRuneCreationRandomStatModel class
class UIRuneCreationRandomStatModel : public WinGUIComboBoxModel
{
public:
	UIRuneCreationRandomStatModel();
	virtual ~UIRuneCreationRandomStatModel();

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
// The UIRuneCreationRandomStatValueModel class
class UIRuneCreationRandomStatValueModel : public WinGUITextEditModel
{
public:
	UIRuneCreationRandomStatValueModel();
	virtual ~UIRuneCreationRandomStatValueModel();

	// Initialization / Update
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
// The UIRuneCreationButtonModel class
class UIRuneCreationButtonModel : public WinGUIButtonModel
{
public:
	UIRuneCreationButtonModel();
	virtual ~UIRuneCreationButtonModel();

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
// The UIRuneCreation class
class UIRuneCreation
{
public:
	UIRuneCreation( CCGOPGUI * pGUI );
	~UIRuneCreation();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Rune Creation
	inline Void GetCreationArea( WinGUIRectangle * outClientArea ) const;

	inline WinGUIComboBox * GetSlot() const;
	inline WinGUIComboBox * GetSet() const;
	inline WinGUIComboBox * GetRank() const;
	inline WinGUIComboBox * GetQuality() const;
	inline WinGUIComboBox * GetLevel() const;
	inline WinGUIComboBox * GetMainStat() const;
	inline WinGUIComboBox * GetInnateStat() const;
	inline WinGUITextEdit * GetInnateStatValue() const;
	inline WinGUIComboBox * GetRandomStat( UInt iIndex ) const;
	inline WinGUITextEdit * GetRandomStatValue( UInt iIndex ) const;

	// Helpers
	Void UpdateAvailableMainStats();
	Void UpdateRandomStatsCount();
	Void ExcludeRuneStats( WinGUIComboBox * pJustSelected );

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Rune Creation UI
	UIRuneCreationGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	UIRuneCreationSlotModel m_hSlotModel;
	WinGUIComboBox * m_pSlot;

	UIRuneCreationSetModel m_hSetModel;
	WinGUIComboBox * m_pSet;

	UIRuneCreationRankModel m_hRankModel;
	WinGUIComboBox * m_pRank;

	UIRuneCreationQualityModel m_hQualityModel;
	WinGUIComboBox * m_pQuality;

	UIRuneCreationLevelModel m_hLevelModel;
	WinGUIComboBox * m_pLevel;

	UIRuneCreationMainStatModel m_hMainStatModel;
	WinGUIComboBox * m_pMainStat;

	UIRuneCreationInnateStatModel m_hInnateStatModel;
	WinGUIComboBox * m_pInnateStat;

	UIRuneCreationInnateStatValueModel m_hInnateStatValueModel;
	WinGUITextEdit * m_pInnateStatValue;

	struct _random_stats {
		UIRuneCreationRandomStatModel hStatModel;
		WinGUIComboBox * pStat;
		UIRuneCreationRandomStatValueModel hValueModel;
		WinGUITextEdit * pValue;
	} m_arrRandomStats[RUNE_RANDOM_STAT_COUNT];

	UIRuneCreationButtonModel m_hButtonModel;
	WinGUIButton * m_pButton;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneCreation.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RUNEEXPLORER_RUNECREATION_H

